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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
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
LDLIBSOPTIONS=-LLib Lib/linux_x64/libeasystreamclient.a Lib/linux_x64/libavfilter.a Lib/linux_x64/libavformat.a Lib/linux_x64/libavdevice.a Lib/linux_x64/libavcodec.a Lib/linux_x64/libavutil.a Lib/linux_x64/libpostproc.a Lib/linux_x64/libswresample.a Lib/linux_x64/libswscale.a Lib/linux_x64/libssl.a Lib/linux_x64/libcrypto.a Lib/linux_x64/libeasyaacencoder.a Lib/linux_x64/libz.a Lib/linux_x64/libx264.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_CONF}/easystreamclient

${CND_CONF}/easystreamclient: Lib/linux_x64/libeasystreamclient.a

${CND_CONF}/easystreamclient: Lib/linux_x64/libavfilter.a

${CND_CONF}/easystreamclient: Lib/linux_x64/libavformat.a

${CND_CONF}/easystreamclient: Lib/linux_x64/libavdevice.a

${CND_CONF}/easystreamclient: Lib/linux_x64/libavcodec.a

${CND_CONF}/easystreamclient: Lib/linux_x64/libavutil.a

${CND_CONF}/easystreamclient: Lib/linux_x64/libpostproc.a

${CND_CONF}/easystreamclient: Lib/linux_x64/libswresample.a

${CND_CONF}/easystreamclient: Lib/linux_x64/libswscale.a

${CND_CONF}/easystreamclient: Lib/linux_x64/libssl.a

${CND_CONF}/easystreamclient: Lib/linux_x64/libcrypto.a

${CND_CONF}/easystreamclient: Lib/linux_x64/libeasyaacencoder.a

${CND_CONF}/easystreamclient: Lib/linux_x64/libz.a

${CND_CONF}/easystreamclient: Lib/linux_x64/libx264.a

${CND_CONF}/easystreamclient: ${OBJECTFILES}
	${MKDIR} -p ${CND_CONF}
	${LINK.cc} -o ${CND_CONF}/easystreamclient ${OBJECTFILES} ${LDLIBSOPTIONS} -lpthread -ldl

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -IInclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
