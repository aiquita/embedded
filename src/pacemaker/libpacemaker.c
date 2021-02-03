/* sscc : C CODE OF SORTED EQUATIONS PACEMAKER - INLINE MODE */

/* AUXILIARY DECLARATIONS */

#ifndef STRLEN
#define STRLEN 81
#endif
#define _COND(A,B,C) ((A)?(B):(C))
#ifdef TRACE_ACTION
#include <stdio.h>
#endif
#ifndef NULL
#define NULL ((char*)0)
#endif

#ifndef __EXEC_STATUS_H_LOADED
#define __EXEC_STATUS_H_LOADED

typedef struct {
unsigned int start:1;
unsigned int kill:1;
unsigned int active:1;
unsigned int suspended:1;
unsigned int prev_active:1;
unsigned int prev_suspended:1;
unsigned int exec_index;
unsigned int task_exec_index;
void (*pStart)();
void (*pRet)();
} __ExecStatus;

#endif
#define __ResetExecStatus(status) {\
   status.prev_active = status.active; \
   status.prev_suspended = status.suspended; \
   status.start = status.kill = status.active = status.suspended = 0; }
#define __DSZ(V) (--(V)<=0)
#define BASIC_TYPES_DEFINED
typedef int boolean;
typedef int integer;
typedef char* string;
#define _true 1
#define _false 0
#define __PACEMAKER_GENERIC_TEST(TEST) return TEST;
typedef void (*__PACEMAKER_APF)();
static __PACEMAKER_APF *__PACEMAKER_PActionArray;

#include "libpacemaker.h"

/* EXTERN DECLARATIONS */

#ifndef _NO_EXTERN_DEFINITIONS
#ifndef _NO_FUNCTION_DEFINITIONS
#ifndef _CALC_AMPL_DEFINED
#ifndef CALC_AMPL
extern float CALC_AMPL(integer);
#endif
#endif
#ifndef _BPM_TO_FREQ_DEFINED
#ifndef BPM_TO_FREQ
extern integer BPM_TO_FREQ(integer);
#endif
#endif
#ifndef _CALC_BPM_DEFINED
#ifndef CALC_BPM
extern integer CALC_BPM();
#endif
#endif
#endif
#ifndef _NO_PROCEDURE_DEFINITIONS
#ifndef _SEND_PULSE_DEFINED
#ifndef SEND_PULSE
extern void SEND_PULSE(float);
#endif
#endif
#endif
#endif

/* INITIALIZED CONSTANTS */

/* MEMORY ALLOCATION */

static integer __PACEMAKER_V0;
static boolean __PACEMAKER_V1;
static boolean __PACEMAKER_V2;
static integer __PACEMAKER_V3;
static integer __PACEMAKER_V4;
static float __PACEMAKER_V5;
static integer __PACEMAKER_V6;
static integer __PACEMAKER_V7;


/* INPUT FUNCTIONS */

void PACEMAKER_I_INT (integer __V) {
__PACEMAKER_V0 = __V;
__PACEMAKER_V1 = _true;
}
void PACEMAKER_I_HEART_BEAT () {
__PACEMAKER_V2 = _true;
}

/* ACTIONS */

/* PREDEFINED ACTIONS */

/* PRESENT SIGNAL TESTS */

#define __PACEMAKER_A1 \
__PACEMAKER_V1
#define __PACEMAKER_A2 \
__PACEMAKER_V2

/* OUTPUT ACTIONS */

#define __PACEMAKER_A3 \
PACEMAKER_O_BPM(__PACEMAKER_V3)
#define __PACEMAKER_A4 \
PACEMAKER_O_TIME_OUT()

/* ASSIGNMENTS */

#define __PACEMAKER_A5 \
__PACEMAKER_V1 = _false
#define __PACEMAKER_A6 \
__PACEMAKER_V2 = _false
#define __PACEMAKER_A7 \
__PACEMAKER_V4 = 70
#define __PACEMAKER_A8 \
__PACEMAKER_V5 = CALC_AMPL(__PACEMAKER_V4)
#define __PACEMAKER_A9 \
__PACEMAKER_V4 = __PACEMAKER_V3
#define __PACEMAKER_A10 \
__PACEMAKER_V6 = BPM_TO_FREQ(__PACEMAKER_V3)
#define __PACEMAKER_A11 \
__PACEMAKER_V7 = 0
#define __PACEMAKER_A12 \
__PACEMAKER_V7 = __PACEMAKER_V7+__PACEMAKER_V0
#define __PACEMAKER_A13 \
__PACEMAKER_V6 = BPM_TO_FREQ(__PACEMAKER_V3)
#define __PACEMAKER_A14 \
__PACEMAKER_V3 = CALC_BPM()

/* PROCEDURE CALLS */

#define __PACEMAKER_A15 \
SEND_PULSE(__PACEMAKER_V5)

/* CONDITIONS */

#define __PACEMAKER_A16 \
__PACEMAKER_V7>__PACEMAKER_V6

/* DECREMENTS */

/* START ACTIONS */

/* KILL ACTIONS */

/* SUSPEND ACTIONS */

/* ACTIVATE ACTIONS */

/* WRITE ARGS ACTIONS */

/* RESET ACTIONS */

#define __PACEMAKER_A17 \

#define __PACEMAKER_A18 \

#define __PACEMAKER_A19 \

#define __PACEMAKER_A20 \


/* ACTION SEQUENCES */

/* FUNCTIONS RETURNING NUMBER OF EXEC */

int PACEMAKER_number_of_execs () {
return (0);
}


/* AUTOMATON (STATE ACTION-TREES) */



static void __PACEMAKER__reset_input () {
__PACEMAKER_V1 = _false;
__PACEMAKER_V2 = _false;
}

/* REDEFINABLE BIT TYPE */

#ifndef __SSC_BIT_TYPE_DEFINED
typedef char __SSC_BIT_TYPE;
#endif

/* REGISTER VARIABLES */

static __SSC_BIT_TYPE __PACEMAKER_R[8] = {_true,
 _false,
 _false,
 _false,
 _false,
 _false,
 _false,
 _false};

/* AUTOMATON ENGINE */

int PACEMAKER () {
/* AUXILIARY VARIABLES */

static __SSC_BIT_TYPE E[22];
E[0] = __PACEMAKER_R[0]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__PACEMAKER_A1));
if (E[0]) {
__PACEMAKER_A17;
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A17\n");
#endif
}
if (__PACEMAKER_R[0]) {
__PACEMAKER_A18;
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A18\n");
#endif
}
E[1] = (__PACEMAKER_R[7]&&!(__PACEMAKER_R[0]))||__PACEMAKER_R[0];
if (__PACEMAKER_R[0]) {
__PACEMAKER_A7;
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A7\n");
#endif
}
if (__PACEMAKER_R[0]) {
__PACEMAKER_A19;
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A19\n");
#endif
}
E[2] = (__PACEMAKER_R[2]&&!(__PACEMAKER_R[0]))||__PACEMAKER_R[0];
E[3] = E[2]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 2\n"),
#endif
__PACEMAKER_A2);
E[4] = __PACEMAKER_R[1]&&!(__PACEMAKER_R[0]);
E[5] = E[4]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 2\n"),
#endif
__PACEMAKER_A2);
E[5] = E[3]||E[5];
E[3] = E[1]&&E[5];
if (E[3]) {
__PACEMAKER_A14;
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A14\n");
#endif
}
if (E[3]) {
__PACEMAKER_A3;
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A3\n");
#endif
}
E[6] = __PACEMAKER_R[5]&&!(__PACEMAKER_R[0]);
E[7] = __PACEMAKER_R[5]&&E[6]&&!(E[5]);
E[8] = E[7]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__PACEMAKER_A1);
if (E[8]) {
__PACEMAKER_A12;
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A12\n");
#endif
}
E[9] = E[8]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 16\n"),
#endif
__PACEMAKER_A16);
if (E[9]) {
__PACEMAKER_A4;
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A4\n");
#endif
}
E[4] = E[4]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 2\n"),
#endif
__PACEMAKER_A2));
E[4] = __PACEMAKER_R[1]&&E[4];
E[10] = E[4]&&E[9];
if (E[10]) {
__PACEMAKER_A8;
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A8\n");
#endif
}
E[11] = !(_true);
E[12] = (__PACEMAKER_R[3]&&!(__PACEMAKER_R[0]))||__PACEMAKER_R[0];
E[13] = E[12]&&E[10];
if (E[13]) {
__PACEMAKER_A15;
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A15\n");
#endif
}
E[12] = E[13]||(E[12]&&!(E[10]));
E[14] = E[5]&&E[3];
if (E[14]) {
__PACEMAKER_A9;
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A9\n");
#endif
}
E[15] = E[14]||(E[5]&&!(E[3]))||E[10];
E[2] = E[2]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 2\n"),
#endif
__PACEMAKER_A2));
E[4] = E[2]||(__PACEMAKER_R[1]&&E[4]&&!(E[9]));
E[2] = __PACEMAKER_R[2]||__PACEMAKER_R[1];
E[16] = __PACEMAKER_R[3]||E[2];
E[2] = (E[12]||E[15]||E[4])&&((E[16]&&!(__PACEMAKER_R[3]))||E[12])&&((E[16]&&!(E[2]))||E[15]||E[4]);
if (__PACEMAKER_R[0]) {
__PACEMAKER_A20;
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A20\n");
#endif
}
E[17] = __PACEMAKER_R[4]&&!(__PACEMAKER_R[0]);
E[18] = (__PACEMAKER_R[0]&&E[3])||(E[17]&&E[3]);
if (E[18]) {
__PACEMAKER_A10;
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A10\n");
#endif
}
E[19] = E[18]||(__PACEMAKER_R[6]&&!(__PACEMAKER_R[0]));
if (E[19]) {
__PACEMAKER_A11;
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A11\n");
#endif
}
E[6] = (E[19]&&E[5])||(E[6]&&E[5]);
if (E[6]) {
__PACEMAKER_A13;
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A13\n");
#endif
}
E[20] = E[6]||E[9];
E[7] = E[7]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__PACEMAKER_A1));
E[7] = (E[19]&&!(E[5]))||(E[8]&&!(E[9]))||(__PACEMAKER_R[5]&&E[7]);
E[17] = (__PACEMAKER_R[0]&&!(E[3]))||(__PACEMAKER_R[4]&&E[17]&&!(E[3]));
E[5] = E[3]||(E[1]&&!(E[5]));
E[1] = __PACEMAKER_R[6]||__PACEMAKER_R[5]||__PACEMAKER_R[4];
E[21] = E[16]||E[1]||__PACEMAKER_R[7];
E[21] = (E[2]||E[20]||E[7]||E[17]||E[5])&&((E[21]&&!(E[16]))||E[2])&&((E[21]&&!(E[1]))||E[20]||E[7]||E[17])&&((E[21]&&!(__PACEMAKER_R[7]))||E[5]);
__PACEMAKER_R[0] = !(_true);
__PACEMAKER_R[1] = E[4];
__PACEMAKER_R[2] = E[15];
__PACEMAKER_R[3] = E[12];
__PACEMAKER_R[4] = E[17];
__PACEMAKER_R[5] = E[7];
__PACEMAKER_R[6] = E[20];
__PACEMAKER_R[7] = E[5];
__PACEMAKER__reset_input();
return E[21];
}

/* AUTOMATON RESET */

int PACEMAKER_reset () {
__PACEMAKER_R[0] = _true;
__PACEMAKER_R[1] = _false;
__PACEMAKER_R[2] = _false;
__PACEMAKER_R[3] = _false;
__PACEMAKER_R[4] = _false;
__PACEMAKER_R[5] = _false;
__PACEMAKER_R[6] = _false;
__PACEMAKER_R[7] = _false;
__PACEMAKER__reset_input();
return 0;
}
