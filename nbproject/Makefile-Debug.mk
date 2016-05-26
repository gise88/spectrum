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
CC=clang
CCC=clang++
CXX=clang++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=CLang-Linux
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
	${OBJECTDIR}/ACacheManager.o \
	${OBJECTDIR}/GoogleAPIClient.o \
	${OBJECTDIR}/Log.o \
	${OBJECTDIR}/ProjectionMapper.o \
	${OBJECTDIR}/Request.o \
	${OBJECTDIR}/SpectrumChannelsDiskCache.o \
	${OBJECTDIR}/SpectrumChannelsRAMCache.o \
	${OBJECTDIR}/SpectrumManager.o \
	${OBJECTDIR}/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/Test.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-ggdb -Wall -pedantic -fsanitize=address -fno-omit-frame-pointer
CXXFLAGS=-ggdb -Wall -pedantic -fsanitize=address -fno-omit-frame-pointer

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/spectrum

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/spectrum: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/spectrum ${OBJECTFILES} ${LDLIBSOPTIONS} -lm -lcurl -lproj -fsanitize=address

${OBJECTDIR}/ACacheManager.o: ACacheManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ACacheManager.o ACacheManager.cpp

${OBJECTDIR}/GoogleAPIClient.o: GoogleAPIClient.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GoogleAPIClient.o GoogleAPIClient.cpp

${OBJECTDIR}/Log.o: Log.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Log.o Log.cpp

${OBJECTDIR}/ProjectionMapper.o: ProjectionMapper.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ProjectionMapper.o ProjectionMapper.cpp

${OBJECTDIR}/Request.o: Request.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Request.o Request.cpp

${OBJECTDIR}/SpectrumChannelsDiskCache.o: SpectrumChannelsDiskCache.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SpectrumChannelsDiskCache.o SpectrumChannelsDiskCache.cpp

${OBJECTDIR}/SpectrumChannelsRAMCache.o: SpectrumChannelsRAMCache.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SpectrumChannelsRAMCache.o SpectrumChannelsRAMCache.cpp

${OBJECTDIR}/SpectrumManager.o: SpectrumManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SpectrumManager.o SpectrumManager.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:
	cd ../googletest && ${MAKE} -j 8 -f Makefile CONF=Release

${TESTDIR}/TestFiles/f1: ${TESTDIR}/Test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}  -lcurl -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} ../googletest/dist/Release/GNU-Linux/libgoogletest.a 


${TESTDIR}/Test.o: Test.cpp 
	${MKDIR} -p ${TESTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DDEBUG -I. -I../googletest/googletest-1.7 -I../googletest/googletest-1.7/include -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/Test.o Test.cpp


${OBJECTDIR}/ACacheManager_nomain.o: ${OBJECTDIR}/ACacheManager.o ACacheManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ACacheManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ACacheManager_nomain.o ACacheManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ACacheManager.o ${OBJECTDIR}/ACacheManager_nomain.o;\
	fi

${OBJECTDIR}/GoogleAPIClient_nomain.o: ${OBJECTDIR}/GoogleAPIClient.o GoogleAPIClient.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/GoogleAPIClient.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GoogleAPIClient_nomain.o GoogleAPIClient.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/GoogleAPIClient.o ${OBJECTDIR}/GoogleAPIClient_nomain.o;\
	fi

${OBJECTDIR}/Log_nomain.o: ${OBJECTDIR}/Log.o Log.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Log.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Log_nomain.o Log.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Log.o ${OBJECTDIR}/Log_nomain.o;\
	fi

${OBJECTDIR}/ProjectionMapper_nomain.o: ${OBJECTDIR}/ProjectionMapper.o ProjectionMapper.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ProjectionMapper.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ProjectionMapper_nomain.o ProjectionMapper.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ProjectionMapper.o ${OBJECTDIR}/ProjectionMapper_nomain.o;\
	fi

${OBJECTDIR}/Request_nomain.o: ${OBJECTDIR}/Request.o Request.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Request.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Request_nomain.o Request.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Request.o ${OBJECTDIR}/Request_nomain.o;\
	fi

${OBJECTDIR}/SpectrumChannelsDiskCache_nomain.o: ${OBJECTDIR}/SpectrumChannelsDiskCache.o SpectrumChannelsDiskCache.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SpectrumChannelsDiskCache.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SpectrumChannelsDiskCache_nomain.o SpectrumChannelsDiskCache.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SpectrumChannelsDiskCache.o ${OBJECTDIR}/SpectrumChannelsDiskCache_nomain.o;\
	fi

${OBJECTDIR}/SpectrumChannelsRAMCache_nomain.o: ${OBJECTDIR}/SpectrumChannelsRAMCache.o SpectrumChannelsRAMCache.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SpectrumChannelsRAMCache.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SpectrumChannelsRAMCache_nomain.o SpectrumChannelsRAMCache.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SpectrumChannelsRAMCache.o ${OBJECTDIR}/SpectrumChannelsRAMCache_nomain.o;\
	fi

${OBJECTDIR}/SpectrumManager_nomain.o: ${OBJECTDIR}/SpectrumManager.o SpectrumManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SpectrumManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SpectrumManager_nomain.o SpectrumManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SpectrumManager.o ${OBJECTDIR}/SpectrumManager_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/spectrum

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
