#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Lab1_part3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Lab1_part3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../Lab1_part2.X/Ascii.c ../Lab1_part2.X/BOARD.c ../Lab1_part2.X/Oled.c ../Lab1_part2.X/OledDriver.c part3.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/2067562461/Ascii.o ${OBJECTDIR}/_ext/2067562461/BOARD.o ${OBJECTDIR}/_ext/2067562461/Oled.o ${OBJECTDIR}/_ext/2067562461/OledDriver.o ${OBJECTDIR}/part3.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/2067562461/Ascii.o.d ${OBJECTDIR}/_ext/2067562461/BOARD.o.d ${OBJECTDIR}/_ext/2067562461/Oled.o.d ${OBJECTDIR}/_ext/2067562461/OledDriver.o.d ${OBJECTDIR}/part3.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/2067562461/Ascii.o ${OBJECTDIR}/_ext/2067562461/BOARD.o ${OBJECTDIR}/_ext/2067562461/Oled.o ${OBJECTDIR}/_ext/2067562461/OledDriver.o ${OBJECTDIR}/part3.o

# Source Files
SOURCEFILES=../Lab1_part2.X/Ascii.c ../Lab1_part2.X/BOARD.c ../Lab1_part2.X/Oled.c ../Lab1_part2.X/OledDriver.c part3.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Lab1_part3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX340F512H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/2067562461/Ascii.o: ../Lab1_part2.X/Ascii.c  .generated_files/flags/default/ad6b132d5de2abffdf14ca29fc4004c6b428d30b .generated_files/flags/default/411a0bba36ae87630292d0c795f181b015b09521
	@${MKDIR} "${OBJECTDIR}/_ext/2067562461" 
	@${RM} ${OBJECTDIR}/_ext/2067562461/Ascii.o.d 
	@${RM} ${OBJECTDIR}/_ext/2067562461/Ascii.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/2067562461/Ascii.o.d" -o ${OBJECTDIR}/_ext/2067562461/Ascii.o ../Lab1_part2.X/Ascii.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2067562461/BOARD.o: ../Lab1_part2.X/BOARD.c  .generated_files/flags/default/67b6389580c8d48d863101acdd2c7b1d90daaf79 .generated_files/flags/default/411a0bba36ae87630292d0c795f181b015b09521
	@${MKDIR} "${OBJECTDIR}/_ext/2067562461" 
	@${RM} ${OBJECTDIR}/_ext/2067562461/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/2067562461/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/2067562461/BOARD.o.d" -o ${OBJECTDIR}/_ext/2067562461/BOARD.o ../Lab1_part2.X/BOARD.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2067562461/Oled.o: ../Lab1_part2.X/Oled.c  .generated_files/flags/default/a4578b0d92b3da6eb6347b2cd9637c9042ae9059 .generated_files/flags/default/411a0bba36ae87630292d0c795f181b015b09521
	@${MKDIR} "${OBJECTDIR}/_ext/2067562461" 
	@${RM} ${OBJECTDIR}/_ext/2067562461/Oled.o.d 
	@${RM} ${OBJECTDIR}/_ext/2067562461/Oled.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/2067562461/Oled.o.d" -o ${OBJECTDIR}/_ext/2067562461/Oled.o ../Lab1_part2.X/Oled.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2067562461/OledDriver.o: ../Lab1_part2.X/OledDriver.c  .generated_files/flags/default/7f9c93176afc968b9ccacb5b283e4092ea4f6955 .generated_files/flags/default/411a0bba36ae87630292d0c795f181b015b09521
	@${MKDIR} "${OBJECTDIR}/_ext/2067562461" 
	@${RM} ${OBJECTDIR}/_ext/2067562461/OledDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/2067562461/OledDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/2067562461/OledDriver.o.d" -o ${OBJECTDIR}/_ext/2067562461/OledDriver.o ../Lab1_part2.X/OledDriver.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/part3.o: part3.c  .generated_files/flags/default/634d7eda42788e646a850d7e3fc343fb55e67a91 .generated_files/flags/default/411a0bba36ae87630292d0c795f181b015b09521
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/part3.o.d 
	@${RM} ${OBJECTDIR}/part3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/part3.o.d" -o ${OBJECTDIR}/part3.o part3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/2067562461/Ascii.o: ../Lab1_part2.X/Ascii.c  .generated_files/flags/default/c027375fa66c67f5fb0d7c43e7e73fbb02b0c06d .generated_files/flags/default/411a0bba36ae87630292d0c795f181b015b09521
	@${MKDIR} "${OBJECTDIR}/_ext/2067562461" 
	@${RM} ${OBJECTDIR}/_ext/2067562461/Ascii.o.d 
	@${RM} ${OBJECTDIR}/_ext/2067562461/Ascii.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/2067562461/Ascii.o.d" -o ${OBJECTDIR}/_ext/2067562461/Ascii.o ../Lab1_part2.X/Ascii.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2067562461/BOARD.o: ../Lab1_part2.X/BOARD.c  .generated_files/flags/default/ddbea12a2e887b6dc381f5e8079f7887453918b3 .generated_files/flags/default/411a0bba36ae87630292d0c795f181b015b09521
	@${MKDIR} "${OBJECTDIR}/_ext/2067562461" 
	@${RM} ${OBJECTDIR}/_ext/2067562461/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/2067562461/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/2067562461/BOARD.o.d" -o ${OBJECTDIR}/_ext/2067562461/BOARD.o ../Lab1_part2.X/BOARD.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2067562461/Oled.o: ../Lab1_part2.X/Oled.c  .generated_files/flags/default/22cce3bfc490cc25f8793f213e8e4e1fb655df5d .generated_files/flags/default/411a0bba36ae87630292d0c795f181b015b09521
	@${MKDIR} "${OBJECTDIR}/_ext/2067562461" 
	@${RM} ${OBJECTDIR}/_ext/2067562461/Oled.o.d 
	@${RM} ${OBJECTDIR}/_ext/2067562461/Oled.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/2067562461/Oled.o.d" -o ${OBJECTDIR}/_ext/2067562461/Oled.o ../Lab1_part2.X/Oled.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2067562461/OledDriver.o: ../Lab1_part2.X/OledDriver.c  .generated_files/flags/default/7fe4f3f02803f3b80cae0b9492ff235cdd578cc0 .generated_files/flags/default/411a0bba36ae87630292d0c795f181b015b09521
	@${MKDIR} "${OBJECTDIR}/_ext/2067562461" 
	@${RM} ${OBJECTDIR}/_ext/2067562461/OledDriver.o.d 
	@${RM} ${OBJECTDIR}/_ext/2067562461/OledDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/2067562461/OledDriver.o.d" -o ${OBJECTDIR}/_ext/2067562461/OledDriver.o ../Lab1_part2.X/OledDriver.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/part3.o: part3.c  .generated_files/flags/default/781892e879bd0676a7e910a7e3b24c5491a8d9f5 .generated_files/flags/default/411a0bba36ae87630292d0c795f181b015b09521
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/part3.o.d 
	@${RM} ${OBJECTDIR}/part3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/part3.o.d" -o ${OBJECTDIR}/part3.o part3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Lab1_part3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Lab1_part3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/Lab1_part3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Lab1_part3.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/Lab1_part3.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
