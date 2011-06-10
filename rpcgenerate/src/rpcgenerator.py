#!/usr/bin/env python
#
# Copyright (c) 2005 Niels Provos <provos@citi.umich.edu>
# All rights reserved.
#
# Generates marshaling code based on libevent.

# TODO:
# 1) use optparse to allow the strategy shell to parse options, and
#    to allow the instantiated factory (for the specific output language)
#    to parse remaining options
# 2) move the globals into a class that manages execution (including the
#    progress outputs that space stderr at the moment)
# 3) emit other languages

import sys
import re

_NAME = "rpcgenerator.py"


line_count = 0
opernum_gl = 16
white = re.compile(r'\s+')
cppcomment = re.compile(r'\/\/.*$')
nonident = re.compile(r'[^a-zA-Z0-9_]')
structref = re.compile(r'([a-zA-Z_][a-zA-Z0-9_]*)$')
structdef = re.compile(r'^struct +[a-zA-Z_][a-zA-Z0-9_]* *{$')
systype = ('byte','_num64','_unum64')
convtype = {'bytes' : 'char', 'string' : 'std::string', '_num64' : '_num64'}

headerdirect = []
cppdirect = []

def ConvtoType(nativtp):
    if nativtp in convtype.keys():
        return convtype[nativtp]
    return nativtp

def TranslateList(mylist, mydict):
    return map(lambda x: x % mydict, mylist)

# Exception class for parse errors
class RpcGenError(Exception):
        def __init__(self, why):
                self.why = why
        def __str__(self):
                return str(self.why)

# Holds everything that makes a struct
class Struct:
    def __init__(self, name):
        self._name = name
        self._entries = []
        self._tags = {}
        print >>sys.stderr, '  Created struct: %s' % name

    def AddEntry(self, entry):
        if self._tags.has_key(entry.Tag()):
            raise RpcGenError(
                'Entry "%s" duplicates tag number %d from "%s" '
                'around line %d' % (entry.Name(), entry.Tag(),
                                    self._tags[entry.Tag()], line_count))
        self._entries.append(entry)
        self._tags[entry.Tag()] = entry.Name()
        print >>sys.stderr, '    Added entry: %s' % entry.Name()

    def Name(self):
        return self._name



class StructCCode(Struct):
    """ Knows how to generate C code for a struct """

    def __init__(self, name):
        Struct.__init__(self, name)

    def PrintTags(self, file):
        """Prints the member definitions for a structure."""
#        print >>file, '/* Struct definition for %s */' % self._name
        print >>file, 'struct %s {' % self._name
        for entry in self._entries:

            if entry._array:
                if entry._type in systype:
                    print >>file, 'std::vector<%s >  %s;' % (ConvtoType(entry._type), entry._name)
                else:
                    print >>file, 'vect_%s  %s;' % (entry._type, entry._name)
            elif (entry._length!=-1) and entry._length:
#                if entry._type in systype:
                    print >>file, '%s  %s[%s];' % (ConvtoType(entry._type), entry._name,entry._length)

            else:
                print >>file, '%s  %s;' % (ConvtoType(entry._type), entry._name)
        print >>file, '};\n'


    def PrintArchives(self, file):
        """Prints the member definitions for a structure."""
        print >>file, '   template<class Archive>'
        print >>file, '   void serialize(Archive& ar, %s& g, const unsigned int version) {' % self._name
        for entry in self._entries:
            print >>file, '        ar & g.%s;' % entry._name


        print >>file, '   };\n'

    def PrintOperation(self, file, opernum):
        
        """Prints the member definitions for a structure."""
        print >>file, 'const short RPC_OPERATION_%s=0x%X;' % (self._name.upper() , opernum)
        opernum=opernum+1;


    def PrintForwardDeclaration(self, file):
        print >>file, 'struct %s;' % self._name

    def PrintForwardVectorDeclaration(self, file):
        print >>file, 'typedef std::vector<%s > vect_%s;' % (self._name, self._name)

   

class Entry:
    def __init__(self, type, name, tag):
        self._type = type
        self._name = name
        self._tag = int(tag)
        self._ctype = type
        self._can_be_array = 0
        self._array = 0
        self._line_count = -1
        self._struct = None
        self._refname = None
        self._length=-1;
        self._optpointer = True
        self._optaddarg = True

    def GetInitializer(self):
        assert 0, "Entry does not provide initializer"

    def SetStruct(self, struct):
        self._struct = struct

    def LineCount(self):
        assert self._line_count != -1
        return self._line_count

    def SetLineCount(self, number):
        self._line_count = number

    def Array(self):
        return self._array

    def Optional(self):
        return self._optional

    def Tag(self):
        return self._tag

    def Name(self):
        return self._name

    def Type(self):
        return self._type

    def MakeArray(self, yes=1):
        self._array = yes

    def MakeOptional(self):
        self._optional = 1

    def Verify(self):
        if self.Array() and not self._can_be_array:
            raise RpcGenError(
                'Entry "%s" cannot be created as an array '
                'around line %d' % (self._name, self.LineCount()))
        if not self._struct:
            raise RpcGenError(
                'Entry "%s" does not know which struct it belongs to '
                'around line %d' % (self._name, self.LineCount()))
        

    def GetTranslation(self, extradict = {}):
        mapping = {
            "parent_name" : self._struct.Name(),
            "name" : self._name,
            "ctype" : self._ctype,
            "refname" : self._refname,
            "optpointer" : self._optpointer and "*" or "",
            "optreference" : self._optpointer and "&" or "",
            "optaddarg" :
            self._optaddarg and ", const %s value" % self._ctype or ""
            }
        for (k, v) in extradict.items():
            mapping[k] = v

        return mapping

class EntryBytes(Entry):
    def __init__(self, type, name, tag, length):
        # Init base class
        Entry.__init__(self, type, name, tag)

        self._length = length
     

class EntryInt(Entry):
    def __init__(self, type, name, tag, bits=32):
        # Init base class
        Entry.__init__(self, type, name, tag)

class EntryString(Entry):
    def __init__(self, type, name, tag, length):
        # Init base class
        Entry.__init__(self, type, name, tag)
        self._length = length
        self._can_be_array = 1
        self._ctype = 'char *'

class EntryStruct(Entry):
    def __init__(self, type, name, tag, refname):
        # Init base class
        Entry.__init__(self, type, name, tag)

        self._optpointer = False
        self._can_be_array = 1
        self._refname = refname
        self._ctype = 'struct %s*' % refname
        self._optaddarg = False

class EntryArray(Entry):
    def __init__(self, entry):
        # Init base class
        Entry.__init__(self, entry._type, entry._name, entry._tag)

        self._entry = entry
        self._refname = entry._refname
        self._ctype = self._entry._ctype
        self._optional = True
        self._optpointer = self._entry._optpointer
        self._optaddarg = self._entry._optaddarg


def NormalizeLine(line):
    global white
    global cppcomment

    line = cppcomment.sub('', line)
    line = line.strip()
    line = white.sub(' ', line)

    return line

def ProcessOneEntry(factory, newstruct, entry):
    optional = 0
    array = 0
    entry_type = ''
    name = ''
    tag = ''
    tag_set = None
    separator = ''
    fixed_length = ''

    tokens = entry.split(' ')
    while tokens:
        token = tokens[0]
        tokens = tokens[1:]

        if not entry_type:
            
            if not array and token == 'array':
                array = 1
                continue

        if not entry_type:
            entry_type = token
            continue

        if not name:
            res = re.match(r'^([^\[\]]+)(\[.*\])?$', token)
            if not res:
                 raise RpcGenError(
                     'Cannot parse name: \"%s\" '
                     'around line %d' % (entry, line_count))
            name = res.group(1)
            fixed_length = res.group(2)
            if fixed_length:
                fixed_length = fixed_length[1:-1]
            continue

        if not separator:
            separator = token
            if separator != '=':
                 raise RpcGenError('Expected "=" after name \"%s\" got %s'
                                   % (name, token))
            continue

        if not tag_set:
            tag_set = 1
            if not re.match(r'^(0x)?[0-9]+$', token):
                raise RpcGenError('Expected tag number: \"%s\"' % entry)
            tag = int(token, 0)
            continue

        raise RpcGenError('Cannot parse \"%s\"' % entry)

#  //  if not tag_set:
#        raise RpcGenError('Need tag number: \"%s\"' % entry)

    # Create the right entry
    if entry_type == 'bytes':
        if fixed_length:
            newentry = factory.EntryBytes(entry_type, name, tag, fixed_length)
        else:
            newentry = factory.EntryVarBytes(entry_type, name, tag)
    elif entry_type == 'int':
        newentry = factory.EntryInt(entry_type, name, tag)
    elif entry_type == 'int64':
        newentry = factory.EntryInt(entry_type, name, tag, bits=64)
    elif entry_type == 'string':
        if fixed_length:
            newentry = factory.EntryString(entry_type, name, tag, fixed_length)
        else:
            newentry = factory.EntryString(entry_type, name, tag, fixed_length)
    elif entry_type == '_num64':
        newentry = factory.EntryString(entry_type, name, tag, fixed_length)
    else:
        res = structref.match(entry_type)
        if res:
            # References another struct defined in our file
            newentry = factory.EntryStruct(entry_type, name, tag, res.group(1))
        else:
            raise RpcGenError('Bad type: "%s" in "%s"' % (entry_type, entry))

    structs = []

    if optional:
        newentry.MakeOptional()
    if array:
        newentry.MakeArray()

    newentry.SetStruct(newstruct)
    newentry.SetLineCount(line_count)
    newentry.Verify()

    if array:
        # We need to encapsulate this entry into a struct
        newname = newentry.Name()+ '_array'

        # Now borgify the new entry.
        newentry = factory.EntryArray(newentry)
        newentry.SetStruct(newstruct)
        newentry.SetLineCount(line_count)
        newentry.MakeArray()

    newstruct.AddEntry(newentry)

    return structs

def ProcessStruct(factory, data):
    tokens = data.split(' ')

    # First three tokens are: 'struct' 'name' '{'
    newstruct = factory.Struct(tokens[1])

    inside = ' '.join(tokens[3:-1])

    tokens = inside.split(';')

    structs = []

    for entry in tokens:
        entry = NormalizeLine(entry)
        if not entry:
            continue

        # It's possible that new structs get defined in here
        structs.extend(ProcessOneEntry(factory, newstruct, entry))

    structs.append(newstruct)
    return structs

def GetNextStruct(file):
    global line_count
    global cppdirect

    got_struct = 0

    processed_lines = []

    have_c_comment = 0
    data = ''
    while 1:
        line = file.readline()
        if not line:
            break

        line_count += 1
        line = line[:-1]

        if not have_c_comment and re.search(r'/\*', line):
            if re.search(r'/\*.*?\*/', line):
                line = re.sub(r'/\*.*?\*/', '', line)
            else:
                line = re.sub(r'/\*.*$', '', line)
                have_c_comment = 1

        if have_c_comment:
            if not re.search(r'\*/', line):
                continue
            have_c_comment = 0
            line = re.sub(r'^.*\*/', '', line)

        line = NormalizeLine(line)

        if not line:
            continue

        if not got_struct:
            if re.match(r'#include ["<].*[>"]', line):
                cppdirect.append(line)
                continue

            if re.match(r'^#(if( |def)|endif)', line):
                cppdirect.append(line)
                continue

            if re.match(r'^#define', line):
                headerdirect.append(line)
                continue

            if not structdef.match(line):
                raise RpcGenError('Missing struct on line %d: %s'
                                  % (line_count, line))
            else:
                got_struct = 1
                data += line
            continue

        # We are inside the struct
        tokens = line.split('}')
        if len(tokens) == 1:
            data += ' ' + line
            continue

        if len(tokens[1]):
            raise RpcGenError('Trailing garbage after struct on line %d'
                              % line_count)

        # We found the end of the struct
        data += ' %s}' % tokens[0]
        break

    # Remove any comments, that might be in there
    data = re.sub(r'/\*.*\*/', '', data)

    return data


def Parse(factory, file):
    """
    Parses the input file and returns C code and corresponding header file.
    """

    entities = []

    while 1:
        # Just gets the whole struct nicely formatted
        data = GetNextStruct(file)

        if not data:
            break

        entities.extend(ProcessStruct(factory, data))

    return entities

class CCodeGenerator:
    def __init__(self):
        pass

    def GuardName(self, name):
        # Use the complete provided path to the input file, with all
        # non-identifier characters replaced with underscores, to
        # reduce the chance of a collision between guard macros.
        return '_' + nonident.sub('_', name).upper() + '_'

    def HeaderPreamble(self, name):
        guard = self.GuardName(name)
        pre = (
            '/*\n'
            ' * Automatically generated from %s\n'
            ' */\n\n'
            '#ifndef %s\n'
            '#define %s\n\n' ) % (
            name, guard, guard)

        for statement in headerdirect:
            pre += '%s\n' % statement
        if headerdirect:
            pre += '\n'

        pre += (
            '#include <string>\n'
            '#include <vector>\n'
            '#include "kernel/constdef.h"\n'
            '#include <boost/archive/binary_iarchive.hpp>\n'
            '#include <boost/archive/basic_binary_oprimitive.hpp>\n'
            '#include <boost/archive/binary_oarchive.hpp>\n'
            '#include <boost/serialization/list.hpp>\n'
            '#include <boost/serialization/vector.hpp>\n'
            '#include <boost/serialization/string.hpp>\n'
            '#include <boost/serialization/version.hpp>\n'
        )

        return pre

    def HeaderPostamble(self, name):
        guard = self.GuardName(name)
        return '#endif  /* %s */' % guard

    def ArchiveNMStart(self):

        pre = (
            '\n'
            'namespace boost {\n'
            'namespace serialization {\n'
             '\n')


        return pre

    def ArchiveNMStop(self):

        pre = (
            '}\n'
            '}\n'
             '\n')


        return pre

  

    def HeaderFilename(self, filename):
        return '.'.join(filename.split('.')[:-1]) + '.h'

    def CodeFilename(self, filename):
        return '.'.join(filename.split('.')[:-1]) + '.c'

    def Struct(self, name):
        return StructCCode(name)

    def EntryBytes(self, entry_type, name, tag, fixed_length):
        return EntryBytes(entry_type, name, tag, fixed_length)

    def EntryVarBytes(self, entry_type, name, tag):
        return EntryVarBytes(entry_type, name, tag)

    def EntryInt(self, entry_type, name, tag, bits=32):
        return EntryInt(entry_type, name, tag, bits)

    def EntryString(self, entry_type, name, tag, fixed_length):
        return EntryString(entry_type, name, tag, fixed_length)
    
#    def EntryString(self, entry_type, name, tag, fixed_length):
#        return EntryString(entry_type, name, tag, fixed_length)


    def EntryStruct(self, entry_type, name, tag, struct_name):
        return EntryStruct(entry_type, name, tag, struct_name)

    def EntryArray(self, entry):
        return EntryArray(entry)

class Usage(RpcGenError):
    def __init__(self, argv0):
        RpcGenError.__init__("usage: %s input.rpc [[output.h] output.c]"
                             % argv0)

class CommandLine:
    def __init__(self, argv):
        self.filename = None
        self.header_file = None
        self.impl_file = None
        self.factory = CCodeGenerator()

        if len(argv) < 2 or len(argv) > 4:
            raise Usage(argv[0])

        self.filename = argv[1].replace('\\', '/')
        if len(argv) == 3:
            self.impl_file = argv[2].replace('\\', '/')
        if len(argv) == 4:
            self.header_file = argv[2].replace('\\', '/')
            self.impl_file = argv[3].replace('\\', '/')

        if not self.filename:
            raise Usage(argv[0])

        if not self.impl_file:
            self.impl_file = self.factory.CodeFilename(self.filename)

        if not self.header_file:
            self.header_file = self.factory.HeaderFilename(self.impl_file)

        if not self.impl_file.endswith('.c'):
            raise RpcGenError("can only generate C implementation files")
        if not self.header_file.endswith('.h'):
            raise RpcGenError("can only generate C header files")

    def run(self):
        filename = self.filename
        header_file = self.header_file
        impl_file = self.impl_file
        factory = self.factory

        print >>sys.stderr, 'Reading \"%s\"' % filename

        fp = open(filename, 'r')
        entities = Parse(factory, fp)
        fp.close()

        print >>sys.stderr, '... creating "%s"' % header_file
        header_fp = open(header_file, 'w')
        print >>header_fp, factory.HeaderPreamble(filename)

        # Create forward declarations: allows other structs to reference
        # each other
        for entry in entities:
            entry.PrintForwardDeclaration(header_fp)
        print >>header_fp, ''


        opernum = opernum_gl;
        for entry in entities:
            entry.PrintOperation(header_fp, opernum )
            opernum=opernum+1;
        print >>header_fp, ''

        for entry in entities:
            entry.PrintForwardVectorDeclaration(header_fp)
        print >>header_fp, ''

        for entry in entities:
            entry.PrintTags(header_fp)

        print >>header_fp, factory.ArchiveNMStart()
        for entry in entities:
            entry.PrintArchives(header_fp)

        print >>header_fp, factory.ArchiveNMStop()
        print >>header_fp, factory.HeaderPostamble(filename)

        header_fp.close()



if __name__ == '__main__':
    try:
        CommandLine(sys.argv).run()
        sys.exit(0)

    except RpcGenError, e:
        print >>sys.stderr, e
        sys.exit(1)

    except EnvironmentError, e:
        if e.filename and e.strerror:
            print >>sys.stderr, "%s: %s" % (e.filename, e.strerror)
            sys.exit(1)
        elif e.strerror:
            print >> sys.stderr, e.strerror
            sys.exit(1)
        else:
            raise
