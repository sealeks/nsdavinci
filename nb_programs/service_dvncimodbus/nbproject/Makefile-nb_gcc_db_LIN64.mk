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
CND_DLIB_EXT=so
CND_CONF=nb_gcc_db_LIN64
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1232915786/modbus_protocol.o \
	${OBJECTDIR}/_ext/715232524/main.o \
	${OBJECTDIR}/_ext/715232524/modbus_detail.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../bin/${CND_CONF}/service_dvncimodbus_db

../../bin/${CND_CONF}/service_dvncimodbus_db: ${OBJECTFILES}
	${MKDIR} -p ../../bin/${CND_CONF}
	${LINK.cc} -o ../../bin/${CND_CONF}/service_dvncimodbus_db ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1232915786/modbus_protocol.o: ../../include/driverspec/modbus_protocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1232915786
	${RM} $@.d
	$(COMPILE.cc) -g -s -DDVNCI_DEDUG -I../../include -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1232915786/modbus_protocol.o ../../include/driverspec/modbus_protocol.cpp

${OBJECTDIR}/_ext/715232524/main.o: ../../include_program/service_dvncimodbus/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/715232524
	${RM} $@.d
	$(COMPILE.cc) -g -s -DDVNCI_DEDUG -I../../include -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/715232524/main.o ../../include_program/service_dvncimodbus/main.cpp

${OBJECTDIR}/_ext/715232524/modbus_detail.o: ../../include_program/service_dvncimodbus/modbus_detail.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/715232524
	${RM} $@.d
	$(COMPILE.cc) -g -s -DDVNCI_DEDUG -I../../include -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/715232524/modbus_detail.o ../../include_program/service_dvncimodbus/modbus_detail.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../bin/${CND_CONF}/service_dvncimodbus_db

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
