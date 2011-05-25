#!/bin/bash -x

#
# Generated - do not edit!
#

# Macros
TOP=`pwd`
CND_PLATFORM=MinGW-Windows
CND_CONF=nb_gcc_rl_WIN32
CND_DISTDIR=dist
CND_BUILDDIR=build
NBTMPDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tmp-packaging
TMPDIRNAME=tmp-packaging
OUTPUT_PATH=../../bin/${CND_CONF}/service_dvnciadmin
OUTPUT_BASENAME=service_dvnciadmin
PACKAGE_TOP_DIR=servnsadminserver/

# Functions
function checkReturnCode
{
    rc=$?
    if [ $rc != 0 ]
    then
        exit $rc
    fi
}
function makeDirectory
# $1 directory path
# $2 permission (optional)
{
    mkdir -p "$1"
    checkReturnCode
    if [ "$2" != "" ]
    then
      chmod $2 "$1"
      checkReturnCode
    fi
}
function copyFileToTmpDir
# $1 from-file path
# $2 to-file path
# $3 permission
{
    cp "$1" "$2"
    checkReturnCode
    if [ "$3" != "" ]
    then
        chmod $3 "$2"
        checkReturnCode
    fi
}

# Setup
cd "${TOP}"
mkdir -p ../../pkg/${CND_CONF}
rm -rf ${NBTMPDIR}
mkdir -p ${NBTMPDIR}

# Copy files and create directories and links
cd "${TOP}"
makeDirectory "${NBTMPDIR}/servnsadminserver/bin"
copyFileToTmpDir "${OUTPUT_PATH}.exe" "${NBTMPDIR}/${PACKAGE_TOP_DIR}bin/${OUTPUT_BASENAME}.exe" 0755


# Generate tar file
cd "${TOP}"
rm -f ../../pkg/${CND_CONF}/servnsadminserver.tar
cd ${NBTMPDIR}
tar -vcf ../../../../../../pkg/${CND_CONF}/servnsadminserver.tar *
checkReturnCode

# Cleanup
cd "${TOP}"
rm -rf ${NBTMPDIR}
