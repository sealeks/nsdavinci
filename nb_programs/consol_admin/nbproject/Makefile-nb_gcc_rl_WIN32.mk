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
	${OBJECTDIR}/_ext/148756256/main.o \
	${OBJECTDIR}/_ext/148756256/adminconsol.o


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
LDLIBSOPTIONS=-L../../lib/boost/${CND_CONF} -L../../lib/${CND_CONF} -lnsadmin -lmeta -lnskernel -lnsadmin -lboost_thread -lboost_wserialization -lboost_system -lboost_serialization -lboost_regex -lboost_program_options -lboost_iostreams -lboost_filesystem -lboost_date_time -lws2_32 -lwsock32 -luuid -lole32 -loleaut32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../bin/${CND_CONF}/consol_admin.exe

../../bin/${CND_CONF}/consol_admin.exe: ${OBJECTFILES}
	${MKDIR} -p ../../bin/${CND_CONF}
	${LINK.cc} -o ../../bin/${CND_CONF}/consol_admin ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/148756256/main.o: ../../include_program/consol_admin/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/148756256
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/148756256/main.o ../../include_program/consol_admin/main.cpp

${OBJECTDIR}/_ext/148756256/adminconsol.o: ../../include_program/consol_admin/adminconsol.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/148756256
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/148756256/adminconsol.o ../../include_program/consol_admin/adminconsol.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../bin/${CND_CONF}/consol_admin.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
