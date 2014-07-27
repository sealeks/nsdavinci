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
CND_PLATFORM=GNU-Windows
CND_DLIB_EXT=dll
CND_CONF=nb_gcc_rl_LIN64
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/863468359/writebase.o


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
LDLIBSOPTIONS=-Wl,-rpath,../../lib/boost/${CND_CONF} -Wl,-rpath,../../lib/${CND_CONF} -lnskernel -ldbaccess -lsoci -lsocipg -lboost_date_time -lboost_filesystem -lboost_prg_exec_monitor -lboost_program_options -lboost_random -lboost_regex -lboost_serialization -lboost_signals -lboost_system -lboost_test_exec_monitor -lboost_thread -lboost_chrono -lboost_unit_test_framework -lboost_wserialization -lpg -lpgport -lrt

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../bin/${CND_CONF}/app_writetrenddef.exe

../../bin/${CND_CONF}/app_writetrenddef.exe: ${OBJECTFILES}
	${MKDIR} -p ../../bin/${CND_CONF}
	${LINK.cc} -o ../../bin/${CND_CONF}/app_writetrenddef ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/863468359/writebase.o: ../../include_program/app_writetrenddef/writebase.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/863468359
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/863468359/writebase.o ../../include_program/app_writetrenddef/writebase.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../bin/${CND_CONF}/app_writetrenddef.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
