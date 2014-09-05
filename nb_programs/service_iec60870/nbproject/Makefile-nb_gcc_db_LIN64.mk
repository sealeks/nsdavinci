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
CND_CONF=nb_gcc_db_LIN64
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1923264132/extiec60870intf.o \
	${OBJECTDIR}/_ext/1923264132/iec60870_104PM.o \
	${OBJECTDIR}/_ext/1923264132/iec60870_PM.o \
	${OBJECTDIR}/_ext/1923264132/iec60870_protocol.o \
	${OBJECTDIR}/_ext/1923264132/main.o


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
LDLIBSOPTIONS=-L../../lib/boost/${CND_CONF} -L../../lib/${CND_CONF} -lnskernel -lboost_date_time -lboost_filesystem -lboost_program_options -lboost_random -lboost_regex -lboost_serialization -lboost_signals -lboost_system -lboost_thread -lboost_chrono -lboost_wserialization -lrt

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../bin/${CND_CONF}/service_iec60870_db.exe

../../bin/${CND_CONF}/service_iec60870_db.exe: ${OBJECTFILES}
	${MKDIR} -p ../../bin/${CND_CONF}
	${LINK.cc} -o ../../bin/${CND_CONF}/service_iec60870_db ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1923264132/extiec60870intf.o: ../../include_program/service_iec60870/extiec60870intf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1923264132
	${RM} $@.d
	$(COMPILE.cc) -g -s -DDVNCI_DEDUG -I../../include -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1923264132/extiec60870intf.o ../../include_program/service_iec60870/extiec60870intf.cpp

${OBJECTDIR}/_ext/1923264132/iec60870_104PM.o: ../../include_program/service_iec60870/iec60870_104PM.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1923264132
	${RM} $@.d
	$(COMPILE.cc) -g -s -DDVNCI_DEDUG -I../../include -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1923264132/iec60870_104PM.o ../../include_program/service_iec60870/iec60870_104PM.cpp

${OBJECTDIR}/_ext/1923264132/iec60870_PM.o: ../../include_program/service_iec60870/iec60870_PM.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1923264132
	${RM} $@.d
	$(COMPILE.cc) -g -s -DDVNCI_DEDUG -I../../include -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1923264132/iec60870_PM.o ../../include_program/service_iec60870/iec60870_PM.cpp

${OBJECTDIR}/_ext/1923264132/iec60870_protocol.o: ../../include_program/service_iec60870/iec60870_protocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1923264132
	${RM} $@.d
	$(COMPILE.cc) -g -s -DDVNCI_DEDUG -I../../include -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1923264132/iec60870_protocol.o ../../include_program/service_iec60870/iec60870_protocol.cpp

${OBJECTDIR}/_ext/1923264132/main.o: ../../include_program/service_iec60870/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1923264132
	${RM} $@.d
	$(COMPILE.cc) -g -s -DDVNCI_DEDUG -I../../include -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1923264132/main.o ../../include_program/service_iec60870/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../bin/${CND_CONF}/service_iec60870_db.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
