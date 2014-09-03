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
CCC=i686-w64-mingw32-gcc-4.8.0
CXX=i686-w64-mingw32-gcc-4.8.0
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=nb_gcc_rl_WIN32
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/217049176/extnetintf.o \
	${OBJECTDIR}/_ext/217049176/gui_executor.o \
	${OBJECTDIR}/_ext/217049176/localnetintf.o \
	${OBJECTDIR}/_ext/217049176/netintf.o \
	${OBJECTDIR}/_ext/217049176/netsession.o \
	${OBJECTDIR}/_ext/217049176/remotenetintf.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../lib/${CND_CONF}/libcustom.a

../../lib/${CND_CONF}/libcustom.a: ${OBJECTFILES}
	${MKDIR} -p ../../lib/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libcustom.a
	${AR} -rv ../../lib/${CND_CONF}/libcustom.a ${OBJECTFILES} 
	$(RANLIB) ../../lib/${CND_CONF}/libcustom.a

${OBJECTDIR}/_ext/217049176/extnetintf.o: ../../include/custom/extnetintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/217049176
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I../../include -I${BOOST_DIR} -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/217049176/extnetintf.o ../../include/custom/extnetintf.cpp

${OBJECTDIR}/_ext/217049176/gui_executor.o: ../../include/custom/gui_executor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/217049176
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I../../include -I${BOOST_DIR} -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/217049176/gui_executor.o ../../include/custom/gui_executor.cpp

${OBJECTDIR}/_ext/217049176/localnetintf.o: ../../include/custom/localnetintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/217049176
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I../../include -I${BOOST_DIR} -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/217049176/localnetintf.o ../../include/custom/localnetintf.cpp

${OBJECTDIR}/_ext/217049176/netintf.o: ../../include/custom/netintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/217049176
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I../../include -I${BOOST_DIR} -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/217049176/netintf.o ../../include/custom/netintf.cpp

${OBJECTDIR}/_ext/217049176/netsession.o: ../../include/custom/netsession.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/217049176
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I../../include -I${BOOST_DIR} -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/217049176/netsession.o ../../include/custom/netsession.cpp

${OBJECTDIR}/_ext/217049176/remotenetintf.o: ../../include/custom/remotenetintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/217049176
	${RM} $@.d
	$(COMPILE.cc) -g -D_WIN32_WINNT=0x0501 -I../../include -I${BOOST_DIR} -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/217049176/remotenetintf.o ../../include/custom/remotenetintf.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libcustom.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
