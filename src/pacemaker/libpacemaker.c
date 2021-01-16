/* sscc : C CODE OF SORTED EQUATIONS pacemaker - INLINE MODE */

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
#define __pacemaker_GENERIC_TEST(TEST) return TEST;
typedef void (*__pacemaker_APF)();
static __pacemaker_APF *__pacemaker_PActionArray;

#include "libpacemaker.h"

/* EXTERN DECLARATIONS */

#ifndef _NO_EXTERN_DEFINITIONS
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

static integer __pacemaker_V0;
static boolean __pacemaker_V1;
static boolean __pacemaker_V2;
static integer __pacemaker_V3;
static float __pacemaker_V4;
static integer __pacemaker_V5;
static integer __pacemaker_V6;
static integer __pacemaker_V7;


/* INPUT FUNCTIONS */

void pacemaker_I_INT (integer __V) {
__pacemaker_V0 = __V;
__pacemaker_V1 = _true;
}
void pacemaker_I_HEART_BEAT () {
__pacemaker_V2 = _true;
}

/* ACTIONS */

/* PREDEFINED ACTIONS */

/* PRESENT SIGNAL TESTS */

#define __pacemaker_A1 \
__pacemaker_V1
#define __pacemaker_A2 \
__pacemaker_V2

/* OUTPUT ACTIONS */

#define __pacemaker_A3 \
pacemaker_O_TIME_OUT()

/* ASSIGNMENTS */

#define __pacemaker_A4 \
__pacemaker_V1 = _false
#define __pacemaker_A5 \
__pacemaker_V2 = _false
#define __pacemaker_A6 \
__pacemaker_V4 = (float)2.167
#define __pacemaker_A7 \
__pacemaker_V5 = __pacemaker_V3
#define __pacemaker_A8 \
__pacemaker_V6 = 0
#define __pacemaker_A9 \
__pacemaker_V6 = __pacemaker_V6+__pacemaker_V0
#define __pacemaker_A10 \
__pacemaker_V5 = __pacemaker_V3
#define __pacemaker_A11 \
__pacemaker_V7 = 0
#define __pacemaker_A12 \
__pacemaker_V7 = __pacemaker_V7+__pacemaker_V0
#define __pacemaker_A13 \
__pacemaker_V3 = 60000/(__pacemaker_V7*5)

/* PROCEDURE CALLS */

#define __pacemaker_A14 \
SEND_PULSE(__pacemaker_V4)

/* CONDITIONS */

#define __pacemaker_A15 \
__pacemaker_V6>((12000/(__pacemaker_V5+3))+1)

/* DECREMENTS */

/* START ACTIONS */

/* KILL ACTIONS */

/* SUSPEND ACTIONS */

/* ACTIVATE ACTIONS */

/* WRITE ARGS ACTIONS */

/* RESET ACTIONS */

#define __pacemaker_A16 \

#define __pacemaker_A17 \

#define __pacemaker_A18 \

#define __pacemaker_A19 \


/* ACTION SEQUENCES */

/* FUNCTIONS RETURNING NUMBER OF EXEC */

int pacemaker_number_of_execs () {
return (0);
}


/* AUTOMATON (STATE ACTION-TREES) */



static void __pacemaker__reset_input () {
__pacemaker_V1 = _false;
__pacemaker_V2 = _false;
}

/* REDEFINABLE BIT TYPE */

#ifndef __SSC_BIT_TYPE_DEFINED
typedef char __SSC_BIT_TYPE;
#endif

/* REGISTER VARIABLES */

static __SSC_BIT_TYPE __pacemaker_R[10] = {_true,
 _false,
 _false,
 _false,
 _false,
 _false,
 _false,
 _false,
 _false,
 _false};

/* AUTOMATON ENGINE */

int pacemaker () {
/* AUXILIARY VARIABLES */

static __SSC_BIT_TYPE E[30];
E[0] = __pacemaker_R[5]&&!(__pacemaker_R[0]);
E[1] = E[0]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__pacemaker_A1);
if (E[1]) {
__pacemaker_A9;
#ifdef TRACE_ACTION
fprintf(stderr, "__pacemaker_A9\n");
#endif
}
E[2] = E[1]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 15\n"),
#endif
__pacemaker_A15);
if (E[2]) {
__pacemaker_A3;
#ifdef TRACE_ACTION
fprintf(stderr, "__pacemaker_A3\n");
#endif
}
E[3] = __pacemaker_R[0]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__pacemaker_A1));
if (E[3]) {
__pacemaker_A16;
#ifdef TRACE_ACTION
fprintf(stderr, "__pacemaker_A16\n");
#endif
}
if (__pacemaker_R[0]) {
__pacemaker_A17;
#ifdef TRACE_ACTION
fprintf(stderr, "__pacemaker_A17\n");
#endif
}
if (__pacemaker_R[0]) {
__pacemaker_A18;
#ifdef TRACE_ACTION
fprintf(stderr, "__pacemaker_A18\n");
#endif
}
E[4] = (__pacemaker_R[2]&&!(__pacemaker_R[0]))||__pacemaker_R[0];
E[5] = E[4]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 2\n"),
#endif
__pacemaker_A2);
E[6] = __pacemaker_R[1]&&!(__pacemaker_R[0]);
E[7] = E[6]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 2\n"),
#endif
__pacemaker_A2);
E[7] = E[5]||E[7];
E[5] = __pacemaker_R[9]&&!(__pacemaker_R[0]);
E[8] = E[5]&&E[7];
E[9] = __pacemaker_R[8]||__pacemaker_R[9];
E[10] = __pacemaker_R[8]&&!(__pacemaker_R[0]);
E[11] = E[10]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__pacemaker_A1);
if (E[11]) {
__pacemaker_A12;
#ifdef TRACE_ACTION
fprintf(stderr, "__pacemaker_A12\n");
#endif
}
E[10] = E[10]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__pacemaker_A1));
E[10] = E[11]||(__pacemaker_R[8]&&E[10]);
E[12] = (E[9]&&!(__pacemaker_R[8]))||E[10];
E[5] = __pacemaker_R[9]&&E[5]&&!(E[7]);
E[13] = (E[9]&&!(__pacemaker_R[9]))||E[5];
E[8] = E[8]&&E[12]&&(E[13]||E[8]);
if (E[8]) {
__pacemaker_A13;
#ifdef TRACE_ACTION
fprintf(stderr, "__pacemaker_A13\n");
#endif
}
E[6] = E[6]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 2\n"),
#endif
__pacemaker_A2));
E[6] = __pacemaker_R[1]&&E[6];
E[14] = E[6]&&E[2];
if (E[14]) {
__pacemaker_A6;
#ifdef TRACE_ACTION
fprintf(stderr, "__pacemaker_A6\n");
#endif
}
E[15] = !(_true);
E[16] = (__pacemaker_R[3]&&!(__pacemaker_R[0]))||__pacemaker_R[0];
E[17] = E[16]&&E[14];
if (E[17]) {
__pacemaker_A14;
#ifdef TRACE_ACTION
fprintf(stderr, "__pacemaker_A14\n");
#endif
}
E[16] = E[17]||(E[16]&&!(E[14]));
E[18] = E[7]||E[14];
E[4] = E[4]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 2\n"),
#endif
__pacemaker_A2));
E[6] = E[4]||(__pacemaker_R[1]&&E[6]&&!(E[2]));
E[4] = __pacemaker_R[2]||__pacemaker_R[1];
E[19] = __pacemaker_R[3]||E[4];
E[4] = (E[16]||E[18]||E[6])&&((E[19]&&!(__pacemaker_R[3]))||E[16])&&((E[19]&&!(E[4]))||E[18]||E[6]);
if (__pacemaker_R[0]) {
__pacemaker_A19;
#ifdef TRACE_ACTION
fprintf(stderr, "__pacemaker_A19\n");
#endif
}
E[20] = __pacemaker_R[4]&&!(__pacemaker_R[0]);
E[21] = (__pacemaker_R[0]&&E[8])||(E[20]&&E[8]);
if (E[21]) {
__pacemaker_A7;
#ifdef TRACE_ACTION
fprintf(stderr, "__pacemaker_A7\n");
#endif
}
E[22] = E[21]||(__pacemaker_R[7]&&!(__pacemaker_R[0]));
if (E[22]) {
__pacemaker_A8;
#ifdef TRACE_ACTION
fprintf(stderr, "__pacemaker_A8\n");
#endif
}
E[0] = E[0]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__pacemaker_A1));
E[0] = E[22]||(E[1]&&!(E[2]))||(__pacemaker_R[5]&&E[0]);
E[23] = __pacemaker_R[6]&&!(__pacemaker_R[0]);
E[24] = (E[22]&&!(E[7]))||(__pacemaker_R[6]&&E[23]&&!(E[7]));
E[25] = __pacemaker_R[5]||__pacemaker_R[6];
E[26] = (E[25]&&!(__pacemaker_R[5]))||E[0];
E[27] = (E[25]&&!(__pacemaker_R[6]))||E[24];
E[28] = (E[0]||E[24])&&E[26]&&E[27];
E[29] = E[22]&&E[7];
E[7] = E[23]&&E[7];
E[26] = E[26]||E[2];
E[7] = (E[29]||E[7])&&E[26]&&(E[27]||E[29]||E[7]);
if (E[7]) {
__pacemaker_A10;
#ifdef TRACE_ACTION
fprintf(stderr, "__pacemaker_A10\n");
#endif
}
E[27] = E[2]&&E[26]&&E[27];
E[26] = E[7]||E[27];
E[20] = (__pacemaker_R[0]&&!(E[8]))||(__pacemaker_R[4]&&E[20]&&!(E[8]));
E[29] = __pacemaker_R[0]||E[8];
if (E[29]) {
__pacemaker_A11;
#ifdef TRACE_ACTION
fprintf(stderr, "__pacemaker_A11\n");
#endif
}
E[13] = (E[10]||E[5])&&E[12]&&E[13];
E[25] = __pacemaker_R[7]||E[25]||__pacemaker_R[4];
E[12] = E[19]||E[25]||E[9];
E[13] = (E[4]||E[28]||E[26]||E[20]||E[29]||E[13])&&((E[12]&&!(E[19]))||E[4])&&((E[12]&&!(E[25]))||E[28]||E[26]||E[20])&&((E[12]&&!(E[9]))||E[29]||E[13]);
E[27] = E[7]||E[27];
__pacemaker_R[5] = E[0]&&!(E[27]);
__pacemaker_R[6] = E[24]&&!(E[27]);
__pacemaker_R[8] = E[29]||(E[10]&&!(E[8]));
__pacemaker_R[9] = E[29]||(E[5]&&!(E[8]));
__pacemaker_R[0] = !(_true);
__pacemaker_R[1] = E[6];
__pacemaker_R[2] = E[18];
__pacemaker_R[3] = E[16];
__pacemaker_R[4] = E[20];
__pacemaker_R[7] = E[26];
__pacemaker__reset_input();
return E[13];
}

/* AUTOMATON RESET */

int pacemaker_reset () {
__pacemaker_R[0] = _true;
__pacemaker_R[1] = _false;
__pacemaker_R[2] = _false;
__pacemaker_R[3] = _false;
__pacemaker_R[4] = _false;
__pacemaker_R[5] = _false;
__pacemaker_R[6] = _false;
__pacemaker_R[7] = _false;
__pacemaker_R[8] = _false;
__pacemaker_R[9] = _false;
__pacemaker__reset_input();
return 0;
}
