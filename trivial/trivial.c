/* sscc : C CODE OF SORTED EQUATIONS trivial - INLINE MODE */

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
#define __trivial_GENERIC_TEST(TEST) return TEST;
typedef void (*__trivial_APF)();
static __trivial_APF *__trivial_PActionArray;

#include "trivial.h"

/* EXTERN DECLARATIONS */

#ifndef _NO_EXTERN_DEFINITIONS
#ifndef _NO_FUNCTION_DEFINITIONS
#ifndef _PRINT_DEFINED
#ifndef PRINT
extern boolean PRINT();
#endif
#endif
#endif
#endif

/* INITIALIZED CONSTANTS */

/* MEMORY ALLOCATION */

static boolean __trivial_V0;
static boolean __trivial_V1;


/* INPUT FUNCTIONS */

void trivial_I_SECOND () {
__trivial_V0 = _true;
}

/* ACTIONS */

/* PREDEFINED ACTIONS */

/* PRESENT SIGNAL TESTS */

#define __trivial_A1 \
__trivial_V0

/* OUTPUT ACTIONS */

#define __trivial_A2 \
trivial_O_O(__trivial_V1)

/* ASSIGNMENTS */

#define __trivial_A3 \
__trivial_V0 = _false
#define __trivial_A4 \
__trivial_V1 = PRINT()

/* PROCEDURE CALLS */

/* CONDITIONS */

/* DECREMENTS */

/* START ACTIONS */

/* KILL ACTIONS */

/* SUSPEND ACTIONS */

/* ACTIVATE ACTIONS */

/* WRITE ARGS ACTIONS */

/* RESET ACTIONS */

#define __trivial_A5 \


/* ACTION SEQUENCES */

/* FUNCTIONS RETURNING NUMBER OF EXEC */

int trivial_number_of_execs () {
return (0);
}


/* AUTOMATON (STATE ACTION-TREES) */



static void __trivial__reset_input () {
__trivial_V0 = _false;
}

/* REDEFINABLE BIT TYPE */

#ifndef __SSC_BIT_TYPE_DEFINED
typedef char __SSC_BIT_TYPE;
#endif

/* REGISTER VARIABLES */

static __SSC_BIT_TYPE __trivial_R[3] = {_true,
 _false,
 _false};

/* AUTOMATON ENGINE */

int trivial () {
/* AUXILIARY VARIABLES */

static __SSC_BIT_TYPE E[3];
if (__trivial_R[0]) {
__trivial_A5;
#ifdef TRACE_ACTION
fprintf(stderr, "__trivial_A5\n");
#endif
}
E[0] = (__trivial_R[1]||__trivial_R[2])&&!(__trivial_R[0]);
E[1] = E[0]&&(
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__trivial_A1);
E[1] = __trivial_R[0]||E[1];
if (E[1]) {
__trivial_A4;
#ifdef TRACE_ACTION
fprintf(stderr, "__trivial_A4\n");
#endif
}
if (E[1]) {
__trivial_A2;
#ifdef TRACE_ACTION
fprintf(stderr, "__trivial_A2\n");
#endif
}
E[2] = !(_true);
E[0] = E[0]&&!((
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__trivial_A1));
__trivial_R[2] = (__trivial_R[1]&&E[0])||(__trivial_R[2]&&E[0]);
E[0] = E[1]||__trivial_R[2];
__trivial_R[0] = !(_true);
__trivial_R[1] = E[1];
__trivial__reset_input();
return E[0];
}

/* AUTOMATON RESET */

int trivial_reset () {
__trivial_R[0] = _true;
__trivial_R[1] = _false;
__trivial_R[2] = _false;
__trivial__reset_input();
return 0;
}
