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
	${OBJECTDIR}/_ext/1935020664/adminintf.o \
	${OBJECTDIR}/_ext/1935020664/adminsession.o \
	${OBJECTDIR}/_ext/1935020664/entitywraper.o \
	${OBJECTDIR}/_ext/1935020664/importutil.o \
	${OBJECTDIR}/_ext/1935020664/koyo_entitywraper.o \
	${OBJECTDIR}/_ext/1935020664/lgk_entitywraper.o \
	${OBJECTDIR}/_ext/1935020664/localadminintf.o \
	${OBJECTDIR}/_ext/1935020664/mdb_entitywraper.o \
	${OBJECTDIR}/_ext/1935020664/metawraper.o \
	${OBJECTDIR}/_ext/1935020664/properties.o \
	${OBJECTDIR}/_ext/1935020664/propertymanager.o \
	${OBJECTDIR}/_ext/1935020664/remoteadminintf.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../lib/${CND_CONF}/libnsadmin.a

../../lib/${CND_CONF}/libnsadmin.a: ${OBJECTFILES}
	${MKDIR} -p ../../lib/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libnsadmin.a
	${AR} -rv ../../lib/${CND_CONF}/libnsadmin.a ${OBJECTFILES} 
	$(RANLIB) ../../lib/${CND_CONF}/libnsadmin.a

${OBJECTDIR}/_ext/1935020664/adminintf.o: ../../include/admin/adminintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1935020664
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1935020664/adminintf.o ../../include/admin/adminintf.cpp

${OBJECTDIR}/_ext/1935020664/adminsession.o: ../../include/admin/adminsession.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1935020664
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1935020664/adminsession.o ../../include/admin/adminsession.cpp

${OBJECTDIR}/_ext/1935020664/entitywraper.o: ../../include/admin/entitywraper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1935020664
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1935020664/entitywraper.o ../../include/admin/entitywraper.cpp

${OBJECTDIR}/_ext/1935020664/importutil.o: ../../include/admin/importutil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1935020664
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1935020664/importutil.o ../../include/admin/importutil.cpp

${OBJECTDIR}/_ext/1935020664/koyo_entitywraper.o: ../../include/admin/koyo_entitywraper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1935020664
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1935020664/koyo_entitywraper.o ../../include/admin/koyo_entitywraper.cpp

${OBJECTDIR}/_ext/1935020664/lgk_entitywraper.o: ../../include/admin/lgk_entitywraper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1935020664
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1935020664/lgk_entitywraper.o ../../include/admin/lgk_entitywraper.cpp

${OBJECTDIR}/_ext/1935020664/localadminintf.o: ../../include/admin/localadminintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1935020664
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1935020664/localadminintf.o ../../include/admin/localadminintf.cpp

${OBJECTDIR}/_ext/1935020664/mdb_entitywraper.o: ../../include/admin/mdb_entitywraper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1935020664
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1935020664/mdb_entitywraper.o ../../include/admin/mdb_entitywraper.cpp

${OBJECTDIR}/_ext/1935020664/metawraper.o: ../../include/admin/metawraper.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1935020664
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1935020664/metawraper.o ../../include/admin/metawraper.cpp

${OBJECTDIR}/_ext/1935020664/properties.o: ../../include/admin/properties.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1935020664
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1935020664/properties.o ../../include/admin/properties.cpp

${OBJECTDIR}/_ext/1935020664/propertymanager.o: ../../include/admin/propertymanager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1935020664
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1935020664/propertymanager.o ../../include/admin/propertymanager.cpp

${OBJECTDIR}/_ext/1935020664/remoteadminintf.o: ../../include/admin/remoteadminintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1935020664
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDVNCI_DEDUG -D_WIN32_WINNT=0x0501 -I../../include -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1935020664/remoteadminintf.o ../../include/admin/remoteadminintf.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libnsadmin.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
