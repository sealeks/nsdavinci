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
	${OBJECTDIR}/_ext/217049176/netintf.o \
	${OBJECTDIR}/_ext/217049176/remotenetintf.o \
	${OBJECTDIR}/_ext/217049176/netsession.o \
	${OBJECTDIR}/_ext/217049176/localnetintf.o


# C Compiler Flags
CFLAGS=-mthreads -fno-strict-aliasing

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../lib/${CND_CONF}/libnsadmin.a

../../lib/${CND_CONF}/libnsadmin.a: ${OBJECTFILES}
	${MKDIR} -p ../../lib/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libnsadmin.a
	${AR} -rv ../../lib/${CND_CONF}/libnsadmin.a ${OBJECTFILES} 
	$(RANLIB) ../../lib/${CND_CONF}/libnsadmin.a

${OBJECTDIR}/_ext/217049176/netintf.o: ../../include/custom/netintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/217049176
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -DDVNCI_DEDUG -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/217049176/netintf.o ../../include/custom/netintf.cpp

${OBJECTDIR}/_ext/217049176/remotenetintf.o: ../../include/custom/remotenetintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/217049176
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -DDVNCI_DEDUG -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/217049176/remotenetintf.o ../../include/custom/remotenetintf.cpp

${OBJECTDIR}/_ext/217049176/netsession.o: ../../include/custom/netsession.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/217049176
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -DDVNCI_DEDUG -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/217049176/netsession.o ../../include/custom/netsession.cpp

${OBJECTDIR}/_ext/217049176/localnetintf.o: ../../include/custom/localnetintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/217049176
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -DDVNCI_DEDUG -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/217049176/localnetintf.o ../../include/custom/localnetintf.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libnsadmin.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
