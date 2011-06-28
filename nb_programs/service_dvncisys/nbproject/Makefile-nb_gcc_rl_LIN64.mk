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
	${OBJECTDIR}/_ext/513515479/main.o \
	${OBJECTDIR}/_ext/513515479/expr_executor.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-fno-strict-aliasing
CXXFLAGS=-fno-strict-aliasing

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../lib/boost/${CND_CONF} -L../../lib/${CND_CONF} -lnskernel -lboost_thread -ldbaccess -lsoci -lboost_date_time -lboost_filesystem -lboost_program_options -lboost_regex -lboost_serialization -lboost_signals -lboost_system -lboost_test_exec_monitor -lboost_unit_test_framework -lboost_wserialization -lnskernel -lrt -ldl

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../bin/${CND_CONF}/service_dvncisys

../../bin/${CND_CONF}/service_dvncisys: ${OBJECTFILES}
	${MKDIR} -p ../../bin/${CND_CONF}
	${LINK.cc} -o ../../bin/${CND_CONF}/service_dvncisys ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/513515479/main.o: ../../include_program/service_dvncisys/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513515479
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DDVNCI_DEDUG -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/513515479/main.o ../../include_program/service_dvncisys/main.cpp

${OBJECTDIR}/_ext/513515479/expr_executor.o: ../../include_program/service_dvncisys/expr_executor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513515479
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DDVNCI_DEDUG -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/513515479/expr_executor.o ../../include_program/service_dvncisys/expr_executor.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../bin/${CND_CONF}/service_dvncisys

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
