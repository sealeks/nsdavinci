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
	${OBJECTDIR}/_ext/1834619689/iec60870_104PM.o \
	${OBJECTDIR}/_ext/1834619689/iec60870_PM.o \
	${OBJECTDIR}/_ext/1834619689/iec60870_detail.o \
	${OBJECTDIR}/_ext/1834619689/iec60870_factory.o \
	${OBJECTDIR}/_ext/1834619689/iec60870_protocol.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../lib/${CND_CONF}//libiec60870.a

../../lib/${CND_CONF}//libiec60870.a: ${OBJECTFILES}
	${MKDIR} -p ../../lib/${CND_CONF}/
	${RM} ../../lib/${CND_CONF}//libiec60870.a
	${AR} -rv ../../lib/${CND_CONF}//libiec60870.a ${OBJECTFILES} 
	$(RANLIB) ../../lib/${CND_CONF}//libiec60870.a

${OBJECTDIR}/_ext/1834619689/iec60870_104PM.o: ../../include/iec60870/iec60870_104PM.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1834619689
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -DITUX200_DEBUG -I../../include -I${BOOST_DIR} -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1834619689/iec60870_104PM.o ../../include/iec60870/iec60870_104PM.cpp

${OBJECTDIR}/_ext/1834619689/iec60870_PM.o: ../../include/iec60870/iec60870_PM.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1834619689
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -DITUX200_DEBUG -I../../include -I${BOOST_DIR} -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1834619689/iec60870_PM.o ../../include/iec60870/iec60870_PM.cpp

${OBJECTDIR}/_ext/1834619689/iec60870_detail.o: ../../include/iec60870/iec60870_detail.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1834619689
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -DITUX200_DEBUG -I../../include -I${BOOST_DIR} -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1834619689/iec60870_detail.o ../../include/iec60870/iec60870_detail.cpp

${OBJECTDIR}/_ext/1834619689/iec60870_factory.o: ../../include/iec60870/iec60870_factory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1834619689
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -DITUX200_DEBUG -I../../include -I${BOOST_DIR} -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1834619689/iec60870_factory.o ../../include/iec60870/iec60870_factory.cpp

${OBJECTDIR}/_ext/1834619689/iec60870_protocol.o: ../../include/iec60870/iec60870_protocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1834619689
	${RM} $@.d
	$(COMPILE.cc) -g -DDEBUG -DITUX200_DEBUG -I../../include -I${BOOST_DIR} -fno-strict-aliasing -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1834619689/iec60870_protocol.o ../../include/iec60870/iec60870_protocol.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../lib/${CND_CONF}//libiec60870.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
