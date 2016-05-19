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
	${OBJECTDIR}/FrequencyRangesCache.o \
	${OBJECTDIR}/GoogleAPIClient.o \
	${OBJECTDIR}/Log.o \
	${OBJECTDIR}/Request.o \
	${OBJECTDIR}/SpectrumUtilities.o \
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
CCFLAGS=-ggdb -Wall -pedantic -fsanitize=address -O3 -fno-omit-frame-pointer
CXXFLAGS=-ggdb -Wall -pedantic -fsanitize=address -O3 -fno-omit-frame-pointer

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/spectrumtmp

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/spectrumtmp: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/spectrumtmp ${OBJECTFILES} ${LDLIBSOPTIONS} -lcurl -fsanitize=address

${OBJECTDIR}/FrequencyRangesCache.o: FrequencyRangesCache.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FrequencyRangesCache.o FrequencyRangesCache.cpp

${OBJECTDIR}/GoogleAPIClient.o: GoogleAPIClient.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GoogleAPIClient.o GoogleAPIClient.cpp

${OBJECTDIR}/Log.o: Log.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Log.o Log.cpp

${OBJECTDIR}/Request.o: Request.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Request.o Request.cpp

${OBJECTDIR}/SpectrumUtilities.o: SpectrumUtilities.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SpectrumUtilities.o SpectrumUtilities.cpp

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


${OBJECTDIR}/FrequencyRangesCache_nomain.o: ${OBJECTDIR}/FrequencyRangesCache.o FrequencyRangesCache.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/FrequencyRangesCache.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FrequencyRangesCache_nomain.o FrequencyRangesCache.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/FrequencyRangesCache.o ${OBJECTDIR}/FrequencyRangesCache_nomain.o;\
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

${OBJECTDIR}/SpectrumUtilities_nomain.o: ${OBJECTDIR}/SpectrumUtilities.o SpectrumUtilities.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SpectrumUtilities.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -DDEBUG -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SpectrumUtilities_nomain.o SpectrumUtilities.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SpectrumUtilities.o ${OBJECTDIR}/SpectrumUtilities_nomain.o;\
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
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/spectrumtmp

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
