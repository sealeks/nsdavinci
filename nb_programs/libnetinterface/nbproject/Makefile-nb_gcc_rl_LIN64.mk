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
CND_CONF=nb_gcc_rl_LIN64
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1955588125/localnetintf.o \
	${OBJECTDIR}/_ext/1955588125/dvnci_net_subsciptor.o \
	${OBJECTDIR}/_ext/1955588125/netintf.o \
	${OBJECTDIR}/_ext/1955588125/netsession.o \
	${OBJECTDIR}/_ext/1955588125/remotenetintf.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -mthreads -fno-strict-aliasing
CXXFLAGS=-m64 -mthreads -fno-strict-aliasing

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../lib/${CND_CONF}/libnetinterface.a

../../lib/${CND_CONF}/libnetinterface.a: ${OBJECTFILES}
	${MKDIR} -p ../../lib/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libnetinterface.a
	${AR} -rv ../../lib/${CND_CONF}/libnetinterface.a ${OBJECTFILES} 
	$(RANLIB) ../../lib/${CND_CONF}/libnetinterface.a

${OBJECTDIR}/_ext/1955588125/localnetintf.o: ../../include/netinterface/localnetintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1955588125
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1955588125/localnetintf.o ../../include/netinterface/localnetintf.cpp

${OBJECTDIR}/_ext/1955588125/dvnci_net_subsciptor.o: ../../include/netinterface/dvnci_net_subsciptor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1955588125
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1955588125/dvnci_net_subsciptor.o ../../include/netinterface/dvnci_net_subsciptor.cpp

${OBJECTDIR}/_ext/1955588125/netintf.o: ../../include/netinterface/netintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1955588125
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1955588125/netintf.o ../../include/netinterface/netintf.cpp

${OBJECTDIR}/_ext/1955588125/netsession.o: ../../include/netinterface/netsession.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1955588125
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1955588125/netsession.o ../../include/netinterface/netsession.cpp

${OBJECTDIR}/_ext/1955588125/remotenetintf.o: ../../include/netinterface/remotenetintf.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1955588125
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1955588125/remotenetintf.o ../../include/netinterface/remotenetintf.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libnetinterface.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
