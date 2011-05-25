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
CND_CONF=nb_gcc_rl_LIN64
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/513508186/mg_protocol.o \
	${OBJECTDIR}/_ext/513508186/iek1177_protocol.o \
	${OBJECTDIR}/_ext/513508186/lgk_detail.o \
	${OBJECTDIR}/_ext/513508186/main.o


# C Compiler Flags
CFLAGS=-mthreads -fno-strict-aliasing

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../lib/boost/${CND_CONF} -L../../lib/${CND_CONF} -lnskernel -lboost_date_time -lboost_filesystem -lboost_program_options -lboost_random -lboost_regex -lboost_serialization -lboost_signals -lboost_system -lboost_thread -lboost_wserialization -lrt

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../bin/${CND_CONF}/service_dvncilgk_db

../../bin/${CND_CONF}/service_dvncilgk_db: ${OBJECTFILES}
	${MKDIR} -p ../../bin/${CND_CONF}
	${LINK.cc} -o ../../bin/${CND_CONF}/service_dvncilgk_db ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/513508186/mg_protocol.o: ../../include_program/service_dvncilgk/mg_protocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513508186
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/513508186/mg_protocol.o ../../include_program/service_dvncilgk/mg_protocol.cpp

${OBJECTDIR}/_ext/513508186/iek1177_protocol.o: ../../include_program/service_dvncilgk/iek1177_protocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513508186
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/513508186/iek1177_protocol.o ../../include_program/service_dvncilgk/iek1177_protocol.cpp

${OBJECTDIR}/_ext/513508186/lgk_detail.o: ../../include_program/service_dvncilgk/lgk_detail.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513508186
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/513508186/lgk_detail.o ../../include_program/service_dvncilgk/lgk_detail.cpp

${OBJECTDIR}/_ext/513508186/main.o: ../../include_program/service_dvncilgk/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513508186
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/513508186/main.o ../../include_program/service_dvncilgk/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../bin/${CND_CONF}/service_dvncilgk_db

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
