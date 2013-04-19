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
CND_PLATFORM=MinGW-Linux-x86
CND_DLIB_EXT=so
CND_CONF=nb_gcc_rl_WIN32
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1232915786/iek1177_protocol.o \
	${OBJECTDIR}/_ext/1232915786/spbmg_protocol.o \
	${OBJECTDIR}/_ext/513508186/lgk_detail.o \
	${OBJECTDIR}/_ext/513508186/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../lib/boost/${CND_CONF} -L../../lib/${CND_CONF} -lnskernel -lboost_date_time -lboost_filesystem -lboost_program_options -lboost_random -lboost_regex -lboost_serialization -lboost_signals -lboost_system -lboost_thread -lboost_chrono -lboost_wserialization -lole32 -loleaut32 -luuid -lws2_32 -lwsock32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../bin/${CND_CONF}/service_dvncilgk

../../bin/${CND_CONF}/service_dvncilgk: ${OBJECTFILES}
	${MKDIR} -p ../../bin/${CND_CONF}
	${LINK.cc} -o ../../bin/${CND_CONF}/service_dvncilgk ${OBJECTFILES} ${LDLIBSOPTIONS} -mthreads -fno-strict-aliasing

${OBJECTDIR}/_ext/1232915786/iek1177_protocol.o: ../../include/driverspec/iek1177_protocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1232915786
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -DBOOST_ASIO_ENABLE_CANCELIO -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1232915786/iek1177_protocol.o ../../include/driverspec/iek1177_protocol.cpp

${OBJECTDIR}/_ext/1232915786/spbmg_protocol.o: ../../include/driverspec/spbmg_protocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1232915786
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -DBOOST_ASIO_ENABLE_CANCELIO -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1232915786/spbmg_protocol.o ../../include/driverspec/spbmg_protocol.cpp

${OBJECTDIR}/_ext/513508186/lgk_detail.o: ../../include_program/service_dvncilgk/lgk_detail.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513508186
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -DBOOST_ASIO_ENABLE_CANCELIO -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/513508186/lgk_detail.o ../../include_program/service_dvncilgk/lgk_detail.cpp

${OBJECTDIR}/_ext/513508186/main.o: ../../include_program/service_dvncilgk/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513508186
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -DBOOST_ASIO_ENABLE_CANCELIO -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/513508186/main.o ../../include_program/service_dvncilgk/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../bin/${CND_CONF}/service_dvncilgk

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
