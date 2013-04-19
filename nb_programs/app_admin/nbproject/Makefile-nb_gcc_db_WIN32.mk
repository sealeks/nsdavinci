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
QMAKE=qmake

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
OBJECTFILES=


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
LDLIBSOPTIONS=../../lib/nb_gcc_db_WIN32/libnsadmin.a ../../lib/nb_gcc_db_WIN32/libnskernel.a ../../lib/nb_gcc_db_WIN32/libnsadmin.a ../../lib/nb_gcc_db_WIN32/libmeta.a ../../lib/boost/nb_gcc_db_WIN32/libboost_date_time.a ../../lib/boost/nb_gcc_db_WIN32/libboost_filesystem.a ../../lib/boost/nb_gcc_db_WIN32/libboost_iostreams.a ../../lib/boost/nb_gcc_db_WIN32/libboost_program_options.a ../../lib/boost/nb_gcc_db_WIN32/libboost_random.a ../../lib/boost/nb_gcc_db_WIN32/libboost_regex.a ../../lib/boost/nb_gcc_db_WIN32/libboost_serialization.a ../../lib/boost/nb_gcc_db_WIN32/libboost_signals.a ../../lib/boost/nb_gcc_db_WIN32/libboost_system.a ../../lib/boost/nb_gcc_db_WIN32/libboost_thread.a ../../lib/boost/nb_gcc_db_WIN32/libboost_chrono.a ../../lib/boost/nb_gcc_db_WIN32/libboost_wserialization.a -lws2_32 -lwsock32 -lole32 -loleaut32

nbproject/qt-${CND_CONF}.mk: nbproject/qt-${CND_CONF}.pro FORCE
	${QMAKE} VPATH=. -o qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.pro
	mv -f qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.mk

FORCE:

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} nbproject/qt-${CND_CONF}.mk
	"${MAKE}" -f nbproject/qt-${CND_CONF}.mk ../../bin/${CND_CONF}/app_admin

${CND_BUILDDIR}/nb_gcc_db_WIN32/%.o: nbproject/qt-${CND_CONF}.mk
	${MAKE} -f nbproject/qt-${CND_CONF}.mk "$@"

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS} nbproject/qt-${CND_CONF}.mk
	${MAKE} -f nbproject/qt-${CND_CONF}.mk distclean

# Subprojects
.clean-subprojects:
