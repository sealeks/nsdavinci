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
CND_CONF=nb_gcc_db_WIN32
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/513515479/expr_executor.o \
	${OBJECTDIR}/_ext/513515479/main.o


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
LDLIBSOPTIONS=-L../../lib/boost/${CND_CONF} -L../../lib/${CND_CONF} -lnskernel -lboost_thread -lboost_chrono -ldbaccess -lsoci -lboost_date_time -lboost_filesystem -lboost_iostreams -lboost_program_options -lboost_regex -lboost_serialization -lboost_signals -lboost_system -lboost_wserialization -lnskernel -loleaut32 -lole32 -lws2_32 -lwsock32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../bin/${CND_CONF}/service_dvncisys_db

../../bin/${CND_CONF}/service_dvncisys_db: ${OBJECTFILES}
	${MKDIR} -p ../../bin/${CND_CONF}
	${LINK.cc} -o ../../bin/${CND_CONF}/service_dvncisys_db ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/513515479/expr_executor.o: ../../include_program/service_dvncisys/expr_executor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513515479
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -DDVNCI_DEDUG -I../../include -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/513515479/expr_executor.o ../../include_program/service_dvncisys/expr_executor.cpp

${OBJECTDIR}/_ext/513515479/main.o: ../../include_program/service_dvncisys/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/513515479
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -DDVNCI_DEDUG -I../../include -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/513515479/main.o ../../include_program/service_dvncisys/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../bin/${CND_CONF}/service_dvncisys_db

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
