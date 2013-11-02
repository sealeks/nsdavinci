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
CND_CONF=nb_gcc_rl_WIN32
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
LDLIBSOPTIONS=F\:/Project/davinci/nb_programs/libnsadmin/../../lib/nb_gcc_rl_WIN32/libnsadmin.a F\:/Project/davinci/nb_programs/libnskernel/../../lib/nb_gcc_rl_WIN32/libnskernel.a F\:/Project/davinci/nb_programs/libmeta/../../lib/nb_gcc_rl_WIN32/libmeta.a -lole32 -lwsock32 -loleaut32 -lws2_32 /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_atomic.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_chrono.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_coroutine.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_date_time.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_exception.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_filesystem.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_iostreams.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_locale.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_log.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_log_setup.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_prg_exec_monitor.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_program_options.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_random.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_regex.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_serialization.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_signals.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_system.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_test_exec_monitor.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_thread.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_timer.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_unit_test_framework.a /F/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_wserialization.a

nbproject/qt-${CND_CONF}.mk: nbproject/qt-${CND_CONF}.pro FORCE
	${QMAKE} VPATH=. -spec win32-g++ -o qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.pro
	mv -f qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.mk
	@sed -e 's/\/qt\/bin/\/qt\/bin\//g' nbproject/qt-${CND_CONF}.mk >nbproject/qt-${CND_CONF}.tmp
	@mv -f nbproject/qt-${CND_CONF}.tmp nbproject/qt-${CND_CONF}.mk

FORCE:

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} nbproject/qt-${CND_CONF}.mk
	"${MAKE}" -f nbproject/qt-${CND_CONF}.mk ../../bin/${CND_CONF}/app_admin.exe

${CND_BUILDDIR}/nb_gcc_rl_WIN32/%.o: nbproject/qt-${CND_CONF}.mk
	${MAKE} -f nbproject/qt-${CND_CONF}.mk "$@"

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS} nbproject/qt-${CND_CONF}.mk
	${MAKE} -f nbproject/qt-${CND_CONF}.mk distclean

# Subprojects
.clean-subprojects:
