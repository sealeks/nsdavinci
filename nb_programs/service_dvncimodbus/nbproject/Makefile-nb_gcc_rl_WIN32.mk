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
CND_CONF=nb_gcc_rl_WIN32
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/715232524/modbus_detail.o \
	${OBJECTDIR}/_ext/715232524/main.o \
	${OBJECTDIR}/_ext/1232915786/modbus_protocol.o


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
LDLIBSOPTIONS=-L../../lib/boost/${CND_CONF} -L../../lib/${CND_CONF} -lnskernel -lwsock32 -lws2_32 -lole32 -loleaut32 -lboost_date_time -lboost_filesystem -lboost_iostreams -lboost_program_options -lboost_random -lboost_regex -lboost_serialization -lboost_signals -lboost_system -lboost_thread -lboost_chrono -lboost_wserialization

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../bin/${CND_CONF}/service_dvncimodbus.exe

../../bin/${CND_CONF}/service_dvncimodbus.exe: ${OBJECTFILES}
	${MKDIR} -p ../../bin/${CND_CONF}
	${LINK.cc} -mthreads -fno-strict-aliasing -o ../../bin/${CND_CONF}/service_dvncimodbus ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/715232524/modbus_detail.o: ../../include_program/service_dvncimodbus/modbus_detail.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/715232524
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -DBOOST_ASIO_ENABLE_CANCELIO -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/715232524/modbus_detail.o ../../include_program/service_dvncimodbus/modbus_detail.cpp

${OBJECTDIR}/_ext/715232524/main.o: ../../include_program/service_dvncimodbus/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/715232524
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -DBOOST_ASIO_ENABLE_CANCELIO -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/715232524/main.o ../../include_program/service_dvncimodbus/main.cpp

${OBJECTDIR}/_ext/1232915786/modbus_protocol.o: ../../include/driverspec/modbus_protocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1232915786
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -DBOOST_ASIO_ENABLE_CANCELIO -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1232915786/modbus_protocol.o ../../include/driverspec/modbus_protocol.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../bin/${CND_CONF}/service_dvncimodbus.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
