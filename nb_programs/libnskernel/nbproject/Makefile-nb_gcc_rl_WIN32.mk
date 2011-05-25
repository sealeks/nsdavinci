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
CND_CONF=nb_gcc_rl_WIN32
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/431270180/appath_lin.o \
	${OBJECTDIR}/_ext/431270180/rpcioclient.o \
	${OBJECTDIR}/_ext/431270180/stringvalue_base.o \
	${OBJECTDIR}/_ext/431270180/serviceapp.o \
	${OBJECTDIR}/_ext/431270180/basis_iostream.o \
	${OBJECTDIR}/_ext/431270180/systemutil.o \
	${OBJECTDIR}/_ext/431270180/utils.o \
	${OBJECTDIR}/_ext/431270180/short_value.o \
	${OBJECTDIR}/_ext/431270180/constdef.o \
	${OBJECTDIR}/_ext/431270180/service.o \
	${OBJECTDIR}/_ext/431270180/appath.o \
	${OBJECTDIR}/_ext/431270180/interface_proccesstmpl.o \
	${OBJECTDIR}/_ext/431270180/appath_win.o \
	${OBJECTDIR}/_ext/431270180/expression.o \
	${OBJECTDIR}/_ext/431270180/driver_blockgenerator.o \
	${OBJECTDIR}/_ext/431270180/driver_detail.o \
	${OBJECTDIR}/_ext/431270180/string_base.o \
	${OBJECTDIR}/_ext/431270180/proccesstmpl.o \
	${OBJECTDIR}/_ext/431270180/memfile.o \
	${OBJECTDIR}/_ext/431270180/serviceapp_lin.o \
	${OBJECTDIR}/_ext/431270180/serviceapp_win.o \
	${OBJECTDIR}/_ext/431270180/index_base.o \
	${OBJECTDIR}/_ext/431270180/mainstruct.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../lib/${CND_CONF}/libnskernel.a

../../lib/${CND_CONF}/libnskernel.a: ${OBJECTFILES}
	${MKDIR} -p ../../lib/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libnskernel.a
	${AR} -rv ../../lib/${CND_CONF}/libnskernel.a ${OBJECTFILES} 
	$(RANLIB) ../../lib/${CND_CONF}/libnskernel.a

${OBJECTDIR}/_ext/431270180/appath_lin.o: ../../include/kernel/appath_lin.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/appath_lin.o ../../include/kernel/appath_lin.cpp

${OBJECTDIR}/_ext/431270180/rpcioclient.o: ../../include/kernel/rpcioclient.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/rpcioclient.o ../../include/kernel/rpcioclient.cpp

${OBJECTDIR}/_ext/431270180/stringvalue_base.o: ../../include/kernel/stringvalue_base.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/stringvalue_base.o ../../include/kernel/stringvalue_base.cpp

${OBJECTDIR}/_ext/431270180/serviceapp.o: ../../include/kernel/serviceapp.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/serviceapp.o ../../include/kernel/serviceapp.cpp

${OBJECTDIR}/_ext/431270180/basis_iostream.o: ../../include/kernel/basis_iostream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/basis_iostream.o ../../include/kernel/basis_iostream.cpp

${OBJECTDIR}/_ext/431270180/systemutil.o: ../../include/kernel/systemutil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/systemutil.o ../../include/kernel/systemutil.cpp

${OBJECTDIR}/_ext/431270180/utils.o: ../../include/kernel/utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/utils.o ../../include/kernel/utils.cpp

${OBJECTDIR}/_ext/431270180/short_value.o: ../../include/kernel/short_value.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/short_value.o ../../include/kernel/short_value.cpp

${OBJECTDIR}/_ext/431270180/constdef.o: ../../include/kernel/constdef.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/constdef.o ../../include/kernel/constdef.cpp

${OBJECTDIR}/_ext/431270180/service.o: ../../include/kernel/service.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/service.o ../../include/kernel/service.cpp

${OBJECTDIR}/_ext/431270180/appath.o: ../../include/kernel/appath.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/appath.o ../../include/kernel/appath.cpp

${OBJECTDIR}/_ext/431270180/interface_proccesstmpl.o: ../../include/kernel/interface_proccesstmpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/interface_proccesstmpl.o ../../include/kernel/interface_proccesstmpl.cpp

${OBJECTDIR}/_ext/431270180/appath_win.o: ../../include/kernel/appath_win.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/appath_win.o ../../include/kernel/appath_win.cpp

${OBJECTDIR}/_ext/431270180/expression.o: ../../include/kernel/expression.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/expression.o ../../include/kernel/expression.cpp

${OBJECTDIR}/_ext/431270180/driver_blockgenerator.o: ../../include/kernel/driver_blockgenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/driver_blockgenerator.o ../../include/kernel/driver_blockgenerator.cpp

${OBJECTDIR}/_ext/431270180/driver_detail.o: ../../include/kernel/driver_detail.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/driver_detail.o ../../include/kernel/driver_detail.cpp

${OBJECTDIR}/_ext/431270180/string_base.o: ../../include/kernel/string_base.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/string_base.o ../../include/kernel/string_base.cpp

${OBJECTDIR}/_ext/431270180/proccesstmpl.o: ../../include/kernel/proccesstmpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/proccesstmpl.o ../../include/kernel/proccesstmpl.cpp

${OBJECTDIR}/_ext/431270180/memfile.o: ../../include/kernel/memfile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/memfile.o ../../include/kernel/memfile.cpp

${OBJECTDIR}/_ext/431270180/serviceapp_lin.o: ../../include/kernel/serviceapp_lin.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/serviceapp_lin.o ../../include/kernel/serviceapp_lin.cpp

${OBJECTDIR}/_ext/431270180/serviceapp_win.o: ../../include/kernel/serviceapp_win.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/serviceapp_win.o ../../include/kernel/serviceapp_win.cpp

${OBJECTDIR}/_ext/431270180/index_base.o: ../../include/kernel/index_base.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/index_base.o ../../include/kernel/index_base.cpp

${OBJECTDIR}/_ext/431270180/mainstruct.o: ../../include/kernel/mainstruct.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/431270180
	$(COMPILE.cc) -O2 -Wall -D_WIN32_WINNT=0x0501 -I../../include -o ${OBJECTDIR}/_ext/431270180/mainstruct.o ../../include/kernel/mainstruct.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../lib/${CND_CONF}/libnskernel.a

# Subprojects
.clean-subprojects:
