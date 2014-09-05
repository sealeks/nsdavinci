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
CND_CONF=nb_gcc_db_WIN32
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
CCFLAGS=-mthreads -fno-strict-aliasing -static
CXXFLAGS=-mthreads -fno-strict-aliasing -static

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../lib/boost/${CND_CONF} -L../../lib/${CND_CONF} -lnskernel -lwsock32 -lws2_32 -lole32 -loleaut32 -lboost_date_time -lboost_filesystem -lboost_iostreams -lboost_program_options -lboost_random -lboost_regex -lboost_serialization -lboost_signals -lboost_system -lboost_thread -lboost_chrono -lboost_wserialization -lstdc++

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../bin/${CND_CONF}/service_iec60870_db.exe

../../bin/${CND_CONF}/service_iec60870_db.exe: ${OBJECTFILES}
	${MKDIR} -p ../../bin/${CND_CONF}
	${LINK.cc} -o ../../bin/${CND_CONF}/service_iec60870_db ${OBJECTFILES} ${LDLIBSOPTIONS} -mthreads

${OBJECTDIR}/_ext/1923264132/extiec60870intf.o: ../../include_program/service_iec60870/extiec60870intf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1923264132
	${RM} $@.d
	$(COMPILE.cc) -g -s -DBOOST_ASIO_ENABLE_CANCELIO -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -static -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1923264132/extiec60870intf.o ../../include_program/service_iec60870/extiec60870intf.cpp

${OBJECTDIR}/_ext/1923264132/iec60870_104PM.o: ../../include_program/service_iec60870/iec60870_104PM.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1923264132
	${RM} $@.d
	$(COMPILE.cc) -g -s -DBOOST_ASIO_ENABLE_CANCELIO -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -static -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1923264132/iec60870_104PM.o ../../include_program/service_iec60870/iec60870_104PM.cpp

${OBJECTDIR}/_ext/1923264132/iec60870_PM.o: ../../include_program/service_iec60870/iec60870_PM.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1923264132
	${RM} $@.d
	$(COMPILE.cc) -g -s -DBOOST_ASIO_ENABLE_CANCELIO -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -static -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1923264132/iec60870_PM.o ../../include_program/service_iec60870/iec60870_PM.cpp

${OBJECTDIR}/_ext/1923264132/iec60870_protocol.o: ../../include_program/service_iec60870/iec60870_protocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1923264132
	${RM} $@.d
	$(COMPILE.cc) -g -s -DBOOST_ASIO_ENABLE_CANCELIO -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -static -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1923264132/iec60870_protocol.o ../../include_program/service_iec60870/iec60870_protocol.cpp

${OBJECTDIR}/_ext/1923264132/main.o: ../../include_program/service_iec60870/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1923264132
	${RM} $@.d
	$(COMPILE.cc) -g -s -DBOOST_ASIO_ENABLE_CANCELIO -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -static -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1923264132/main.o ../../include_program/service_iec60870/main.cpp

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
