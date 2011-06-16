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
CCC=g++
CXX=g++
FC=gfortran
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=lib_gcc_db_WIN32
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/all_programs.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/all_programs.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/all_programs ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../libmeta && ${MAKE}  -f Makefile CONF=nb_gcc_db_WIN32
	cd ../libsoci && ${MAKE}  -f Makefile CONF=nb_gcc_db_WIN32
	cd ../lisocipg && ${MAKE}  -f Makefile CONF=nb_gcc_db_WIN32
	cd ../libnskernel && ${MAKE}  -f Makefile CONF=nb_gcc_db_WIN32
	cd ../libdbaccess && ${MAKE}  -f Makefile CONF=nb_gcc_db_WIN32
	cd ../libnsadmin && ${MAKE}  -f Makefile CONF=nb_gcc_db_WIN32
	cd ../libcustom && ${MAKE}  -f Makefile CONF=nb_gcc_db_WIN32

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/all_programs.exe

# Subprojects
.clean-subprojects:
	cd ../libmeta && ${MAKE}  -f Makefile CONF=nb_gcc_db_WIN32 clean
	cd ../libsoci && ${MAKE}  -f Makefile CONF=nb_gcc_db_WIN32 clean
	cd ../lisocipg && ${MAKE}  -f Makefile CONF=nb_gcc_db_WIN32 clean
	cd ../libnskernel && ${MAKE}  -f Makefile CONF=nb_gcc_db_WIN32 clean
	cd ../libdbaccess && ${MAKE}  -f Makefile CONF=nb_gcc_db_WIN32 clean
	cd ../libnsadmin && ${MAKE}  -f Makefile CONF=nb_gcc_db_WIN32 clean
	cd ../libcustom && ${MAKE}  -f Makefile CONF=nb_gcc_db_WIN32 clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
