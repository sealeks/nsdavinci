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
FC=
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=WIN32
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=../../lib/WIN32/lib_nskernel.a ../../lib/WIN32/plagixml.a /E/Project/davinci/lib/WIN32/boost/debug/libboost_date_time-mgw44-mt-d-1_42.lib /E/Project/davinci/lib/WIN32/boost/debug/libboost_filesystem-mgw44-mt-d-1_42.lib /E/Project/davinci/lib/WIN32/boost/debug/libboost_iostreams-mgw44-mt-d-1_42.lib /E/Project/davinci/lib/WIN32/boost/debug/libboost_program_options-mgw44-mt-d-1_42.lib /E/Project/davinci/lib/WIN32/boost/debug/libboost_regex-mgw44-mt-d-1_42.lib /E/Project/davinci/lib/WIN32/boost/debug/libboost_serialization-mgw44-mt-d-1_42.lib /E/Project/davinci/lib/WIN32/boost/debug/libboost_system-mgw44-mt-d-1_42.lib /E/Project/davinci/lib/WIN32/boost/debug/libboost_thread-mgw44-mt-d-1_42.lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-WIN32.mk ../../bin/WIN32/testapp.exe

../../bin/WIN32/testapp.exe: ../../lib/WIN32/lib_nskernel.a

../../bin/WIN32/testapp.exe: ../../lib/WIN32/plagixml.a

../../bin/WIN32/testapp.exe: /E/Project/davinci/lib/WIN32/boost/debug/libboost_date_time-mgw44-mt-d-1_42.lib

../../bin/WIN32/testapp.exe: /E/Project/davinci/lib/WIN32/boost/debug/libboost_filesystem-mgw44-mt-d-1_42.lib

../../bin/WIN32/testapp.exe: /E/Project/davinci/lib/WIN32/boost/debug/libboost_iostreams-mgw44-mt-d-1_42.lib

../../bin/WIN32/testapp.exe: /E/Project/davinci/lib/WIN32/boost/debug/libboost_program_options-mgw44-mt-d-1_42.lib

../../bin/WIN32/testapp.exe: /E/Project/davinci/lib/WIN32/boost/debug/libboost_regex-mgw44-mt-d-1_42.lib

../../bin/WIN32/testapp.exe: /E/Project/davinci/lib/WIN32/boost/debug/libboost_serialization-mgw44-mt-d-1_42.lib

../../bin/WIN32/testapp.exe: /E/Project/davinci/lib/WIN32/boost/debug/libboost_system-mgw44-mt-d-1_42.lib

../../bin/WIN32/testapp.exe: /E/Project/davinci/lib/WIN32/boost/debug/libboost_thread-mgw44-mt-d-1_42.lib

../../bin/WIN32/testapp.exe: ${OBJECTFILES}
	${MKDIR} -p ../../bin/WIN32
	${LINK.cc} -o ../../bin/${CND_CONF}/testapp ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../../include -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/WIN32
	${RM} ../../bin/WIN32/testapp.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
