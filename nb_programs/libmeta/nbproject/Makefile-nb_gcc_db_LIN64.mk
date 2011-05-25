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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=nb_gcc_db_LIN64
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1170440020/meta.o \
	${OBJECTDIR}/_ext/1170440020/pugixml.o \
	${OBJECTDIR}/_ext/1170440020/pugixpath.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -fno-strict-aliasing
CXXFLAGS=-m64 -fno-strict-aliasing

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../lib/${CND_CONF}/libmeta.a

../../lib/${CND_CONF}/libmeta.a: ${OBJECTFILES}
	${MKDIR} -p ../../lib/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libmeta.a
	${AR} -rv ../../lib/${CND_CONF}/libmeta.a ${OBJECTFILES} 
	$(RANLIB) ../../lib/${CND_CONF}/libmeta.a

${OBJECTDIR}/_ext/1170440020/meta.o: ../../include/meta/meta.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170440020
	${RM} $@.d
	$(COMPILE.cc) -g -DDVNCI_DEDUG -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170440020/meta.o ../../include/meta/meta.cpp

${OBJECTDIR}/_ext/1170440020/pugixml.o: ../../include/meta/pugixml.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170440020
	${RM} $@.d
	$(COMPILE.cc) -g -DDVNCI_DEDUG -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170440020/pugixml.o ../../include/meta/pugixml.cpp

${OBJECTDIR}/_ext/1170440020/pugixpath.o: ../../include/meta/pugixpath.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170440020
	${RM} $@.d
	$(COMPILE.cc) -g -DDVNCI_DEDUG -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170440020/pugixpath.o ../../include/meta/pugixpath.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libmeta.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
