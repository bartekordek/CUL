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
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/511e4115/ConsoleUtilities.o \
	${OBJECTDIR}/_ext/511e4115/Degree.o \
	${OBJECTDIR}/_ext/511e4115/FS.o \
	${OBJECTDIR}/_ext/511e4115/FileCompileTest.o \
	${OBJECTDIR}/_ext/511e4115/FileRegularImpl.o \
	${OBJECTDIR}/_ext/511e4115/Frustum.o \
	${OBJECTDIR}/_ext/511e4115/IAngle.o \
	${OBJECTDIR}/_ext/511e4115/IFile.o \
	${OBJECTDIR}/_ext/511e4115/IPivot.o \
	${OBJECTDIR}/_ext/511e4115/ITime.o \
	${OBJECTDIR}/_ext/511e4115/ITimer.o \
	${OBJECTDIR}/_ext/511e4115/Line.o \
	${OBJECTDIR}/_ext/511e4115/MultiPointFactory.o \
	${OBJECTDIR}/_ext/511e4115/MyString.o \
	${OBJECTDIR}/_ext/511e4115/Named.o \
	${OBJECTDIR}/_ext/511e4115/Path.o \
	${OBJECTDIR}/_ext/511e4115/Quaternion.o \
	${OBJECTDIR}/_ext/511e4115/Rectangle.o \
	${OBJECTDIR}/_ext/511e4115/TimeConcrete.o \
	${OBJECTDIR}/_ext/511e4115/TimerChrono.o


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
LDLIBSOPTIONS=../../deps/boost_1_64_0/Build-Cygwin/libboost_system-mt.a ../../deps/boost_1_64_0/Build-Cygwin/libboost_filesystem-mt.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../build/${CND_PLATFORM}-${CND_CONF}/libcul.${CND_DLIB_EXT}

../../build/${CND_PLATFORM}-${CND_CONF}/libcul.${CND_DLIB_EXT}: ../../deps/boost_1_64_0/Build-Cygwin/libboost_system-mt.a

../../build/${CND_PLATFORM}-${CND_CONF}/libcul.${CND_DLIB_EXT}: ../../deps/boost_1_64_0/Build-Cygwin/libboost_filesystem-mt.a

../../build/${CND_PLATFORM}-${CND_CONF}/libcul.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ../../build/${CND_PLATFORM}-${CND_CONF}
	${LINK.cc} -o ../../build/${CND_PLATFORM}-${CND_CONF}/libcul.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -Wl,--out-implib,../../build/${CND_PLATFORM}-${CND_CONF}/libcul.a -shared

${OBJECTDIR}/_ext/511e4115/ConsoleUtilities.o: ../src/ConsoleUtilities.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/ConsoleUtilities.o ../src/ConsoleUtilities.cpp

${OBJECTDIR}/_ext/511e4115/Degree.o: ../src/Degree.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/Degree.o ../src/Degree.cpp

${OBJECTDIR}/_ext/511e4115/FS.o: ../src/FS.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/FS.o ../src/FS.cpp

${OBJECTDIR}/_ext/511e4115/FileCompileTest.o: ../src/FileCompileTest.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/FileCompileTest.o ../src/FileCompileTest.cpp

${OBJECTDIR}/_ext/511e4115/FileRegularImpl.o: ../src/FileRegularImpl.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/FileRegularImpl.o ../src/FileRegularImpl.cpp

${OBJECTDIR}/_ext/511e4115/Frustum.o: ../src/Frustum.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/Frustum.o ../src/Frustum.cpp

${OBJECTDIR}/_ext/511e4115/IAngle.o: ../src/IAngle.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/IAngle.o ../src/IAngle.cpp

${OBJECTDIR}/_ext/511e4115/IFile.o: ../src/IFile.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/IFile.o ../src/IFile.cpp

${OBJECTDIR}/_ext/511e4115/IPivot.o: ../src/IPivot.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/IPivot.o ../src/IPivot.cpp

${OBJECTDIR}/_ext/511e4115/ITime.o: ../src/ITime.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/ITime.o ../src/ITime.cpp

${OBJECTDIR}/_ext/511e4115/ITimer.o: ../src/ITimer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/ITimer.o ../src/ITimer.cpp

${OBJECTDIR}/_ext/511e4115/Line.o: ../src/Line.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/Line.o ../src/Line.cpp

${OBJECTDIR}/_ext/511e4115/MultiPointFactory.o: ../src/MultiPointFactory.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/MultiPointFactory.o ../src/MultiPointFactory.cpp

${OBJECTDIR}/_ext/511e4115/MyString.o: ../src/MyString.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/MyString.o ../src/MyString.cpp

${OBJECTDIR}/_ext/511e4115/Named.o: ../src/Named.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/Named.o ../src/Named.cpp

${OBJECTDIR}/_ext/511e4115/Path.o: ../src/Path.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/Path.o ../src/Path.cpp

${OBJECTDIR}/_ext/511e4115/Quaternion.o: ../src/Quaternion.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/Quaternion.o ../src/Quaternion.cpp

${OBJECTDIR}/_ext/511e4115/Rectangle.o: ../src/Rectangle.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/Rectangle.o ../src/Rectangle.cpp

${OBJECTDIR}/_ext/511e4115/TimeConcrete.o: ../src/TimeConcrete.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/TimeConcrete.o ../src/TimeConcrete.cpp

${OBJECTDIR}/_ext/511e4115/TimerChrono.o: ../src/TimerChrono.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DCULLib_EXPORT -DCUL_DYNAMIC -I../inc -I../src -I../../deps/boost_1_64_0 -std=c++14  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/TimerChrono.o ../src/TimerChrono.cpp

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
