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
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=nb_gcc_db_WIN32
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1261136976/main.o \
	${OBJECTDIR}/_ext/1261136976/koyo_detail.o \
	${OBJECTDIR}/_ext/1232915786/directnet_protocol.o \
	${OBJECTDIR}/_ext/1232915786/modbus_protocol.o


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
LDLIBSOPTIONS=-L../../lib/boost/${CND_CONF} -L../../lib/${CND_CONF} -lnskernel -lboost_date_time -lboost_filesystem -lboost_program_options -lboost_random -lboost_regex -lboost_serialization -lboost_signals -lboost_system -lboost_thread -lboost_wserialization -lole32 -loleaut32 -luuid -lws2_32 -lwsock32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../bin/${CND_CONF}/service_dvncikoyo_db.exe

../../bin/${CND_CONF}/service_dvncikoyo_db.exe: ${OBJECTFILES}
	${MKDIR} -p ../../bin/${CND_CONF}
	${LINK.cc} -mthreads -o ../../bin/${CND_CONF}/service_dvncikoyo_db ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1261136976/main.o: ../../include_program/service_dvncikoyo/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1261136976
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -DDVNCI_DEDUG -DBOOST_ASIO_ENABLE_CANCELIO -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1261136976/main.o ../../include_program/service_dvncikoyo/main.cpp

${OBJECTDIR}/_ext/1261136976/koyo_detail.o: ../../include_program/service_dvncikoyo/koyo_detail.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1261136976
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -DDVNCI_DEDUG -DBOOST_ASIO_ENABLE_CANCELIO -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1261136976/koyo_detail.o ../../include_program/service_dvncikoyo/koyo_detail.cpp

${OBJECTDIR}/_ext/1232915786/directnet_protocol.o: ../../include/driverspec/directnet_protocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1232915786
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -DDVNCI_DEDUG -DBOOST_ASIO_ENABLE_CANCELIO -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1232915786/directnet_protocol.o ../../include/driverspec/directnet_protocol.cpp

${OBJECTDIR}/_ext/1232915786/modbus_protocol.o: ../../include/driverspec/modbus_protocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1232915786
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -DDVNCI_DEDUG -DBOOST_ASIO_ENABLE_CANCELIO -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1232915786/modbus_protocol.o ../../include/driverspec/modbus_protocol.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../bin/${CND_CONF}/service_dvncikoyo_db.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
