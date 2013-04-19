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
	${OBJECTDIR}/_ext/1445513634/blob.o \
	${OBJECTDIR}/_ext/1445513634/common.o \
	${OBJECTDIR}/_ext/1445513634/factory.o \
	${OBJECTDIR}/_ext/1445513634/row-id.o \
	${OBJECTDIR}/_ext/1445513634/session.o \
	${OBJECTDIR}/_ext/1445513634/standard-into-type.o \
	${OBJECTDIR}/_ext/1445513634/standard-use-type.o \
	${OBJECTDIR}/_ext/1445513634/statement.o \
	${OBJECTDIR}/_ext/1445513634/vector-into-type.o \
	${OBJECTDIR}/_ext/1445513634/vector-use-type.o


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
LDLIBSOPTIONS=-L../../lib/boost/${CND_CONF} -L../../lib/${CND_CONF} -lsoci ../../lib/database/pgql8_3_win32/libpgport.lib ../../lib/database/pgql8_3_win32/libpq.lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../bin/${CND_CONF}/libsoci_postgresql.dll

../../bin/${CND_CONF}/libsoci_postgresql.dll: ../../lib/database/pgql8_3_win32/libpgport.lib

../../bin/${CND_CONF}/libsoci_postgresql.dll: ../../lib/database/pgql8_3_win32/libpq.lib

../../bin/${CND_CONF}/libsoci_postgresql.dll: ${OBJECTFILES}
	${MKDIR} -p ../../bin/${CND_CONF}
	g++ -o ../../bin/${CND_CONF}/libsoci_postgresql.dll ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/_ext/1445513634/blob.o: ../../include/soci/backends/postgresql/blob.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445513634
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -I/C/Program\ Files\ \(x86\)/PostgreSQL/8.3/include -I../../include -I../../include/soci -mthreads -fno-strict-aliasing -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445513634/blob.o ../../include/soci/backends/postgresql/blob.cpp

${OBJECTDIR}/_ext/1445513634/common.o: ../../include/soci/backends/postgresql/common.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445513634
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -I/C/Program\ Files\ \(x86\)/PostgreSQL/8.3/include -I../../include -I../../include/soci -mthreads -fno-strict-aliasing -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445513634/common.o ../../include/soci/backends/postgresql/common.cpp

${OBJECTDIR}/_ext/1445513634/factory.o: ../../include/soci/backends/postgresql/factory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445513634
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -I/C/Program\ Files\ \(x86\)/PostgreSQL/8.3/include -I../../include -I../../include/soci -mthreads -fno-strict-aliasing -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445513634/factory.o ../../include/soci/backends/postgresql/factory.cpp

${OBJECTDIR}/_ext/1445513634/row-id.o: ../../include/soci/backends/postgresql/row-id.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445513634
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -I/C/Program\ Files\ \(x86\)/PostgreSQL/8.3/include -I../../include -I../../include/soci -mthreads -fno-strict-aliasing -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445513634/row-id.o ../../include/soci/backends/postgresql/row-id.cpp

${OBJECTDIR}/_ext/1445513634/session.o: ../../include/soci/backends/postgresql/session.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445513634
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -I/C/Program\ Files\ \(x86\)/PostgreSQL/8.3/include -I../../include -I../../include/soci -mthreads -fno-strict-aliasing -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445513634/session.o ../../include/soci/backends/postgresql/session.cpp

${OBJECTDIR}/_ext/1445513634/standard-into-type.o: ../../include/soci/backends/postgresql/standard-into-type.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445513634
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -I/C/Program\ Files\ \(x86\)/PostgreSQL/8.3/include -I../../include -I../../include/soci -mthreads -fno-strict-aliasing -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445513634/standard-into-type.o ../../include/soci/backends/postgresql/standard-into-type.cpp

${OBJECTDIR}/_ext/1445513634/standard-use-type.o: ../../include/soci/backends/postgresql/standard-use-type.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445513634
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -I/C/Program\ Files\ \(x86\)/PostgreSQL/8.3/include -I../../include -I../../include/soci -mthreads -fno-strict-aliasing -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445513634/standard-use-type.o ../../include/soci/backends/postgresql/standard-use-type.cpp

${OBJECTDIR}/_ext/1445513634/statement.o: ../../include/soci/backends/postgresql/statement.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445513634
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -I/C/Program\ Files\ \(x86\)/PostgreSQL/8.3/include -I../../include -I../../include/soci -mthreads -fno-strict-aliasing -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445513634/statement.o ../../include/soci/backends/postgresql/statement.cpp

${OBJECTDIR}/_ext/1445513634/vector-into-type.o: ../../include/soci/backends/postgresql/vector-into-type.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445513634
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -I/C/Program\ Files\ \(x86\)/PostgreSQL/8.3/include -I../../include -I../../include/soci -mthreads -fno-strict-aliasing -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445513634/vector-into-type.o ../../include/soci/backends/postgresql/vector-into-type.cpp

${OBJECTDIR}/_ext/1445513634/vector-use-type.o: ../../include/soci/backends/postgresql/vector-use-type.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1445513634
	${RM} $@.d
	$(COMPILE.cc) -O2 -D_WIN32_WINNT=0x0501 -I/C/Program\ Files\ \(x86\)/PostgreSQL/8.3/include -I../../include -I../../include/soci -mthreads -fno-strict-aliasing -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1445513634/vector-use-type.o ../../include/soci/backends/postgresql/vector-use-type.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../bin/${CND_CONF}/libsoci_postgresql.dll

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
