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
CND_CONF=nb_gcc_rl_LIN64
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1170252183/backend-loader.o \
	${OBJECTDIR}/_ext/1170252183/blob.o \
	${OBJECTDIR}/_ext/1170252183/connection-pool.o \
	${OBJECTDIR}/_ext/1170252183/error.o \
	${OBJECTDIR}/_ext/1170252183/into-type.o \
	${OBJECTDIR}/_ext/1170252183/once-temp-type.o \
	${OBJECTDIR}/_ext/1170252183/prepare-temp-type.o \
	${OBJECTDIR}/_ext/1170252183/procedure.o \
	${OBJECTDIR}/_ext/1170252183/ref-counted-prepare-info.o \
	${OBJECTDIR}/_ext/1170252183/ref-counted-statement.o \
	${OBJECTDIR}/_ext/1170252183/row.o \
	${OBJECTDIR}/_ext/1170252183/rowid.o \
	${OBJECTDIR}/_ext/1170252183/session.o \
	${OBJECTDIR}/_ext/1170252183/statement.o \
	${OBJECTDIR}/_ext/1170252183/transaction.o \
	${OBJECTDIR}/_ext/1170252183/use-type.o \
	${OBJECTDIR}/_ext/1170252183/values.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -fno-strict-aliasing -fPIC
CXXFLAGS=-m64 -fno-strict-aliasing -fPIC

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../lib/${CND_CONF}/libsoci.a

../../lib/${CND_CONF}/libsoci.a: ${OBJECTFILES}
	${MKDIR} -p ../../lib/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libsoci.a
	${AR} -rv ../../lib/${CND_CONF}/libsoci.a ${OBJECTFILES} 
	$(RANLIB) ../../lib/${CND_CONF}/libsoci.a

${OBJECTDIR}/_ext/1170252183/backend-loader.o: ../../include/soci/backend-loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/backend-loader.o ../../include/soci/backend-loader.cpp

${OBJECTDIR}/_ext/1170252183/blob.o: ../../include/soci/blob.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/blob.o ../../include/soci/blob.cpp

${OBJECTDIR}/_ext/1170252183/connection-pool.o: ../../include/soci/connection-pool.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/connection-pool.o ../../include/soci/connection-pool.cpp

${OBJECTDIR}/_ext/1170252183/error.o: ../../include/soci/error.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/error.o ../../include/soci/error.cpp

${OBJECTDIR}/_ext/1170252183/into-type.o: ../../include/soci/into-type.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/into-type.o ../../include/soci/into-type.cpp

${OBJECTDIR}/_ext/1170252183/once-temp-type.o: ../../include/soci/once-temp-type.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/once-temp-type.o ../../include/soci/once-temp-type.cpp

${OBJECTDIR}/_ext/1170252183/prepare-temp-type.o: ../../include/soci/prepare-temp-type.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/prepare-temp-type.o ../../include/soci/prepare-temp-type.cpp

${OBJECTDIR}/_ext/1170252183/procedure.o: ../../include/soci/procedure.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/procedure.o ../../include/soci/procedure.cpp

${OBJECTDIR}/_ext/1170252183/ref-counted-prepare-info.o: ../../include/soci/ref-counted-prepare-info.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/ref-counted-prepare-info.o ../../include/soci/ref-counted-prepare-info.cpp

${OBJECTDIR}/_ext/1170252183/ref-counted-statement.o: ../../include/soci/ref-counted-statement.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/ref-counted-statement.o ../../include/soci/ref-counted-statement.cpp

${OBJECTDIR}/_ext/1170252183/row.o: ../../include/soci/row.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/row.o ../../include/soci/row.cpp

${OBJECTDIR}/_ext/1170252183/rowid.o: ../../include/soci/rowid.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/rowid.o ../../include/soci/rowid.cpp

${OBJECTDIR}/_ext/1170252183/session.o: ../../include/soci/session.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/session.o ../../include/soci/session.cpp

${OBJECTDIR}/_ext/1170252183/statement.o: ../../include/soci/statement.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/statement.o ../../include/soci/statement.cpp

${OBJECTDIR}/_ext/1170252183/transaction.o: ../../include/soci/transaction.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/transaction.o ../../include/soci/transaction.cpp

${OBJECTDIR}/_ext/1170252183/use-type.o: ../../include/soci/use-type.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/use-type.o ../../include/soci/use-type.cpp

${OBJECTDIR}/_ext/1170252183/values.o: ../../include/soci/values.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1170252183
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include/soci -I../../include -fno-strict-aliasing -fPIC -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1170252183/values.o ../../include/soci/values.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libsoci.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
