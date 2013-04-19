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
CND_CONF=nb_gcc_rl_WIN32
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/340415863/db_task_executor.o \
	${OBJECTDIR}/_ext/340415863/dbconnectionfactory.o \
	${OBJECTDIR}/_ext/340415863/dbdriver.o \
	${OBJECTDIR}/_ext/340415863/dbpsgrdriver.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../lib/${CND_CONF}/libdbaccess.a

../../lib/${CND_CONF}/libdbaccess.a: ${OBJECTFILES}
	${MKDIR} -p ../../lib/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libdbaccess.a
	${AR} -rv ../../lib/${CND_CONF}/libdbaccess.a ${OBJECTFILES} 
	$(RANLIB) ../../lib/${CND_CONF}/libdbaccess.a

${OBJECTDIR}/_ext/340415863/db_task_executor.o: ../../include/dbaccess/db_task_executor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/340415863
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -I../../include/soci -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/340415863/db_task_executor.o ../../include/dbaccess/db_task_executor.cpp

${OBJECTDIR}/_ext/340415863/dbconnectionfactory.o: ../../include/dbaccess/dbconnectionfactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/340415863
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -I../../include/soci -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/340415863/dbconnectionfactory.o ../../include/dbaccess/dbconnectionfactory.cpp

${OBJECTDIR}/_ext/340415863/dbdriver.o: ../../include/dbaccess/dbdriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/340415863
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -I../../include/soci -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/340415863/dbdriver.o ../../include/dbaccess/dbdriver.cpp

${OBJECTDIR}/_ext/340415863/dbpsgrdriver.o: ../../include/dbaccess/dbpsgrdriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/340415863
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -I../../include/soci -mthreads -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/340415863/dbpsgrdriver.o ../../include/dbaccess/dbpsgrdriver.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libdbaccess.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
