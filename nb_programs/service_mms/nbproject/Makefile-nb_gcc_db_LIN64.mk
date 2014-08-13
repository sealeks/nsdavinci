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
	${OBJECTDIR}/_ext/692605831/extmmsintf.o \
	${OBJECTDIR}/_ext/692605831/main.o \
	${OBJECTDIR}/_ext/692605831/mmsintf.o \
	${OBJECTDIR}/_ext/692605831/mmsioclient.o \
	${OBJECTDIR}/_ext/692605831/mmsserver.o


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
LDLIBSOPTIONS=-L../../lib/boost/${CND_CONF} -L../../lib/${CND_CONF} -lcustom -lnskernel -ldbaccess -lsoci -lboost_date_time -lboost_filesystem -lboost_program_options -lboost_random -lboost_regex -lboost_serialization -lboost_signals -lboost_system -lboost_thread -lboost_chrono -lboost_wserialization -lrt

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../bin/${CND_CONF}/service_mms_db.exe

../../bin/${CND_CONF}/service_mms_db.exe: ${OBJECTFILES}
	${MKDIR} -p ../../bin/${CND_CONF}
	${LINK.cc} -o ../../bin/${CND_CONF}/service_mms_db ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/692605831/extmmsintf.o: ../../include_program/service_mms/extmmsintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/692605831
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DDVNCI_DEDUG -I../../include -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/692605831/extmmsintf.o ../../include_program/service_mms/extmmsintf.cpp

${OBJECTDIR}/_ext/692605831/main.o: ../../include_program/service_mms/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/692605831
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DDVNCI_DEDUG -I../../include -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/692605831/main.o ../../include_program/service_mms/main.cpp

${OBJECTDIR}/_ext/692605831/mmsintf.o: ../../include_program/service_mms/mmsintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/692605831
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DDVNCI_DEDUG -I../../include -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/692605831/mmsintf.o ../../include_program/service_mms/mmsintf.cpp

${OBJECTDIR}/_ext/692605831/mmsioclient.o: ../../include_program/service_mms/mmsioclient.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/692605831
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DDVNCI_DEDUG -I../../include -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/692605831/mmsioclient.o ../../include_program/service_mms/mmsioclient.cpp

${OBJECTDIR}/_ext/692605831/mmsserver.o: ../../include_program/service_mms/mmsserver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/692605831
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -DDVNCI_DEDUG -I../../include -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/692605831/mmsserver.o ../../include_program/service_mms/mmsserver.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../bin/${CND_CONF}/service_mms_db.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
