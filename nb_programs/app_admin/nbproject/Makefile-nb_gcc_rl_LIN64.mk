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
CCC=i686-w64-mingw32-gcc-4.8.0
CXX=i686-w64-mingw32-gcc-4.8.0
FC=gfortran
AS=as
QMAKE=qmake

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=nb_gcc_rl_LIN64
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
LDLIBSOPTIONS=../../lib/nb_gcc_db_LIN64/libnsadmin.a ../../lib/nb_gcc_db_LIN64/libnskernel.a ../../lib/nb_gcc_db_LIN64/libmeta.a ../../lib/boost/nb_gcc_db_LIN64/libboost_date_time.a ../../lib/boost/nb_gcc_db_LIN64/libboost_filesystem.a ../../lib/boost/nb_gcc_db_LIN64/libboost_prg_exec_monitor.a ../../lib/boost/nb_gcc_db_LIN64/libboost_program_options.a ../../lib/boost/nb_gcc_db_LIN64/libboost_random.a ../../lib/boost/nb_gcc_db_LIN64/libboost_regex.a ../../lib/boost/nb_gcc_db_LIN64/libboost_serialization.a ../../lib/boost/nb_gcc_db_LIN64/libboost_signals.a ../../lib/boost/nb_gcc_db_LIN64/libboost_system.a ../../lib/boost/nb_gcc_db_LIN64/libboost_test_exec_monitor.a ../../lib/boost/nb_gcc_db_LIN64/libboost_thread.a ../../lib/boost/nb_gcc_db_LIN64/libboost_chrono.a ../../lib/boost/nb_gcc_db_LIN64/libboost_unit_test_framework.a ../../lib/boost/nb_gcc_db_LIN64/libboost_wserialization.a -lrt

nbproject/qt-${CND_CONF}.mk: nbproject/qt-${CND_CONF}.pro FORCE
	${QMAKE} VPATH=. -spec win32-g++ -o qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.pro
	mv -f qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.mk
	@sed -e 's/\/qt\/bin/\/qt\/bin\//g' nbproject/qt-${CND_CONF}.mk >nbproject/qt-${CND_CONF}.tmp
	@mv -f nbproject/qt-${CND_CONF}.tmp nbproject/qt-${CND_CONF}.mk

FORCE:

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} nbproject/qt-${CND_CONF}.mk
	"${MAKE}" -f nbproject/qt-${CND_CONF}.mk ../../bin/${CND_CONF}/app_admin.exe

${CND_BUILDDIR}/nb_gcc_rl_LIN64/%.o: nbproject/qt-${CND_CONF}.mk
	${MAKE} -f nbproject/qt-${CND_CONF}.mk "$@"

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS} nbproject/qt-${CND_CONF}.mk
	${MAKE} -f nbproject/qt-${CND_CONF}.mk distclean

# Subprojects
.clean-subprojects:
