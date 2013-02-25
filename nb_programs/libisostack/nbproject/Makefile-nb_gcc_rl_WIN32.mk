#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++
CXX=g++
FC=gfortran
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=nb_gcc_rl_WIN32
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1901903102/iso.o \
	${OBJECTDIR}/_ext/894376469/asnbase.o \
	${OBJECTDIR}/_ext/894376469/itu_X690.o \
	${OBJECTDIR}/_ext/1901903102/iso8327.o \
	${OBJECTDIR}/_ext/1901903102/iso8823.o \
	${OBJECTDIR}/_ext/894376469/utf8.o \
	${OBJECTDIR}/_ext/1901903102/archive_stream.o \
	${OBJECTDIR}/_ext/1901903102/rfc1006.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-mthreads -fno-strict-aliasing
CXXFLAGS=-mthreads -fno-strict-aliasing

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../lib/${CND_CONF}/libisostack.a

../../lib/${CND_CONF}/libisostack.a: ${OBJECTFILES}
	${MKDIR} -p ../../lib/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libisostack.a
	${AR} -rv ../../lib/${CND_CONF}/libisostack.a ${OBJECTFILES} 
	$(RANLIB) ../../lib/${CND_CONF}/libisostack.a

${OBJECTDIR}/_ext/1901903102/iso.o: ../../include/iso/iso.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1901903102
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1901903102/iso.o ../../include/iso/iso.cpp

${OBJECTDIR}/_ext/894376469/asnbase.o: ../../include/iso/asn/asnbase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/894376469
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/894376469/asnbase.o ../../include/iso/asn/asnbase.cpp

${OBJECTDIR}/_ext/894376469/itu_X690.o: ../../include/iso/asn/itu_X690.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/894376469
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/894376469/itu_X690.o ../../include/iso/asn/itu_X690.cpp

${OBJECTDIR}/_ext/1901903102/iso8327.o: ../../include/iso/iso8327.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1901903102
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1901903102/iso8327.o ../../include/iso/iso8327.cpp

${OBJECTDIR}/_ext/1901903102/iso8823.o: ../../include/iso/iso8823.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1901903102
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1901903102/iso8823.o ../../include/iso/iso8823.cpp

${OBJECTDIR}/_ext/894376469/utf8.o: ../../include/iso/asn/utf8.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/894376469
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/894376469/utf8.o ../../include/iso/asn/utf8.cpp

${OBJECTDIR}/_ext/1901903102/archive_stream.o: ../../include/iso/archive_stream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1901903102
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1901903102/archive_stream.o ../../include/iso/archive_stream.cpp

${OBJECTDIR}/_ext/1901903102/rfc1006.o: ../../include/iso/rfc1006.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1901903102
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1901903102/rfc1006.o ../../include/iso/rfc1006.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libisostack.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
