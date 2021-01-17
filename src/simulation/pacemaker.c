/* sscc : C CODE OF SORTED EQUATIONS PACEMAKER - SIMULATION MODE */

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
#define CSIMUL_H_LOADED
typedef struct {char text[STRLEN];} symbolic;
extern void _boolean(boolean*, boolean);
extern boolean _eq_boolean(boolean, boolean);
extern boolean _ne_boolean(boolean, boolean);
extern boolean _cond_boolean(boolean ,boolean ,boolean);
extern char* _boolean_to_text(boolean);
extern int _check_boolean(char*);
extern void _text_to_boolean(boolean*, char*);
extern void _integer(integer*, integer);
extern boolean _eq_integer(integer, integer);
extern boolean _ne_integer(integer, integer);
extern integer _cond_integer(boolean ,integer ,integer);
extern char* _integer_to_text(integer);
extern int _check_integer(char*);
extern void _text_to_integer(integer*, char*);
extern void _string(string, string);
extern boolean _eq_string(string, string);
extern boolean _ne_string(string, string);
extern string _cond_string(boolean ,string ,string);
extern char* _string_to_text(string);
extern int _check_string(char*);
extern void _text_to_string(string, char*);
extern void _float(float*, float);
extern boolean _eq_float(float, float);
extern boolean _ne_float(float, float);
extern float _cond_float(boolean ,float ,float);
extern char* _float_to_text(float);
extern int _check_float(char*);
extern void _text_to_float(float*, char*);
extern void _double(double*, double);
extern boolean _eq_double(double, double);
extern boolean _ne_double(double, double);
extern double _cond_double(boolean ,double ,double);
extern char* _double_to_text(double);
extern int _check_double(char*);
extern void _text_to_double(double*, char*);
extern void _symbolic(symbolic*, symbolic);
extern boolean _eq_symbolic(symbolic, symbolic);
extern boolean _ne_symbolic(symbolic, symbolic);
extern symbolic _cond_symbolic(boolean ,symbolic ,symbolic);
extern char* _symbolic_to_text(symbolic);
extern int _check_symbolic(char*);
extern void _text_to_symbolic(symbolic*, char*);
extern char* __PredefinedTypeToText(int, char*);
#define _true 1
#define _false 0
#define __PACEMAKER_GENERIC_TEST(TEST) return TEST;
typedef void (*__PACEMAKER_APF)();
static __PACEMAKER_APF *__PACEMAKER_PActionArray;
static int **__PACEMAKER_PCheckArray;
struct __SourcePoint {
int linkback;
int line;
int column;
int instance_index;
};
struct __InstanceEntry {
char *module_name;
int father_index;
char *dir_name;
char *file_name;
struct __SourcePoint source_point;
struct __SourcePoint end_point;
struct __SourcePoint instance_point;
};
struct __TaskEntry {
char *name;
int   nb_args_ref;
int   nb_args_val;
int  *type_codes_array;
struct __SourcePoint source_point;
};
struct __SignalEntry {
char *name;
int code;
int variable_index;
int present;
struct __SourcePoint source_point;
int number_of_emit_source_points;
struct __SourcePoint* emit_source_point_array;
int number_of_present_source_points;
struct __SourcePoint* present_source_point_array;
int number_of_access_source_points;
struct __SourcePoint* access_source_point_array;
};
struct __InputEntry {
char *name;
int hash;
char *type_name;
int is_a_sensor;
int type_code;
int multiple;
int signal_index;
int (*p_check_input)(char*);
void (*p_input_function)();
int present;
struct __SourcePoint source_point;
};
struct __ReturnEntry {
char *name;
int hash;
char *type_name;
int type_code;
int signal_index;
int exec_index;
int (*p_check_input)(char*);
void (*p_input_function)();
int present;
struct __SourcePoint source_point;
};
struct __ImplicationEntry {
int master;
int slave;
struct __SourcePoint source_point;
};
struct __ExclusionEntry {
int *exclusion_list;
struct __SourcePoint source_point;
};
struct __VariableEntry {
char *full_name;
char *short_name;
char *type_name;
int type_code;
int comment_kind;
int is_initialized;
char *p_variable;
char *source_name;
int written;
unsigned char written_in_transition;
unsigned char read_in_transition;
struct __SourcePoint source_point;
};
struct __ExecEntry {
int task_index;
int *var_indexes_array;
char **p_values_array;
struct __SourcePoint source_point;
};
struct __HaltEntry {
struct __SourcePoint source_point;
};
struct __NetEntry {
int known;
int value;
int number_of_source_points;
struct __SourcePoint* source_point_array;
};
struct __ModuleEntry {
char *version_id;
char *name;
int number_of_instances;
int number_of_tasks;
int number_of_signals;
int number_of_inputs;
int number_of_returns;
int number_of_sensors;
int number_of_outputs;
int number_of_locals;
int number_of_exceptions;
int number_of_implications;
int number_of_exclusions;
int number_of_variables;
int number_of_execs;
int number_of_halts;
int number_of_nets;
int number_of_states;
int state;
unsigned short *halt_list;
unsigned short *awaited_list;
unsigned short *emitted_list;
unsigned short *started_list;
unsigned short *killed_list;
unsigned short *suspended_list;
unsigned short *active_list;
int run_time_error_code;
int error_info;
void (*init)();
int (*run)();
int (*reset)();
char *(*show_variable)(int);
void (*set_variable)(int, char*, char*);
int (*check_value)(int, char*);
int (*execute_action)();
struct __InstanceEntry* instance_table;
struct __TaskEntry* task_table;
struct __SignalEntry* signal_table;
struct __InputEntry* input_table;
struct __ReturnEntry* return_table;
struct __ImplicationEntry* implication_table;
struct __ExclusionEntry* exclusion_table;
struct __VariableEntry* variable_table;
struct __ExecEntry* exec_table;
struct __HaltEntry* halt_table;
struct __NetEntry* net_table;
};

#include "pacemaker.h"

/* EXTERN DECLARATIONS */

extern int __CheckVariables(int*);
extern void __ResetInput();
extern void __ResetExecs();
extern void __ResetVariables();
extern void __ResetVariableStatus();
extern void __AppendToList(unsigned short*, unsigned short);
extern void __ListCopy(unsigned short*, unsigned short**);
extern void __WriteVariable(int);
extern void __ResetVariable(int);
extern void __ResetModuleEntry();
extern void __ResetModuleEntryBeforeReaction();
extern void __ResetModuleEntryAfterReaction();
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

static integer __PACEMAKER_V0;
static boolean __PACEMAKER_V1;
static boolean __PACEMAKER_V2;
static integer __PACEMAKER_V3;
static float __PACEMAKER_V4;
static integer __PACEMAKER_V5;
static integer __PACEMAKER_V6;
static integer __PACEMAKER_V7;

static unsigned short __PACEMAKER_HaltList[12];
static unsigned short __PACEMAKER_AwaitedList[8];
static unsigned short __PACEMAKER_EmittedList[8];
static unsigned short __PACEMAKER_StartedList[1];
static unsigned short __PACEMAKER_KilledList[1];
static unsigned short __PACEMAKER_SuspendedList[1];
static unsigned short __PACEMAKER_ActiveList[1];
static unsigned short __PACEMAKER_AllAwaitedList[8]={2,0,1};


/* INPUT FUNCTIONS */

void PACEMAKER_I_INT (integer __V) {
__WriteVariable(0);
__PACEMAKER_V0 = __V;
__PACEMAKER_V1 = _true;
}
void PACEMAKER_IS_INT (string __V) {
__WriteVariable(0);
_text_to_integer(&__PACEMAKER_V0,__V);
__PACEMAKER_V1 = _true;
}
void PACEMAKER_I_HEART_BEAT () {
__PACEMAKER_V2 = _true;
}
void PACEMAKER_IS_HEART_BEAT () {
__PACEMAKER_V2 = _true;
}

/* FUNCTIONS RETURNING NUMBER OF EXEC */

int PACEMAKER_number_of_execs () {
return (0);
}


/* AUTOMATON (STATE ACTION-TREES) */

/* ACTIONS */

/* PREDEFINED ACTIONS */

/* PRESENT SIGNAL TESTS */

static int __PACEMAKER_A1 () {
__PACEMAKER_GENERIC_TEST(__PACEMAKER_V1);
}
static int __PACEMAKER_Check1 [] = {1,0,0};
static int __PACEMAKER_A2 () {
__PACEMAKER_GENERIC_TEST(__PACEMAKER_V2);
}
static int __PACEMAKER_Check2 [] = {1,0,0};

/* OUTPUT ACTIONS */

static void __PACEMAKER_A3 () {
#ifdef __OUTPUT
PACEMAKER_O_TIME_OUT();
#endif
__AppendToList(__PACEMAKER_EmittedList,2);
}
static int __PACEMAKER_Check3 [] = {1,0,0};

/* ASSIGNMENTS */

static void __PACEMAKER_A4 () {
__PACEMAKER_V1 = _false;
}
static int __PACEMAKER_Check4 [] = {1,0,1,1};
static void __PACEMAKER_A5 () {
__PACEMAKER_V2 = _false;
}
static int __PACEMAKER_Check5 [] = {1,0,1,2};
static void __PACEMAKER_A6 () {
__PACEMAKER_V4 = (float)2.167;
}
static int __PACEMAKER_Check6 [] = {1,0,1,4};
static void __PACEMAKER_A7 () {
__PACEMAKER_V5 = __PACEMAKER_V3;
}
static int __PACEMAKER_Check7 [] = {1,1,3,1,5};
static void __PACEMAKER_A8 () {
__PACEMAKER_V6 = 0;
}
static int __PACEMAKER_Check8 [] = {1,0,1,6};
static void __PACEMAKER_A9 () {
__PACEMAKER_V6 = __PACEMAKER_V6+__PACEMAKER_V0;
}
static int __PACEMAKER_Check9 [] = {1,2,6,0,1,6};
static void __PACEMAKER_A10 () {
__PACEMAKER_V5 = __PACEMAKER_V3;
}
static int __PACEMAKER_Check10 [] = {1,1,3,1,5};
static void __PACEMAKER_A11 () {
__PACEMAKER_V7 = 0;
}
static int __PACEMAKER_Check11 [] = {1,0,1,7};
static void __PACEMAKER_A12 () {
__PACEMAKER_V7 = __PACEMAKER_V7+__PACEMAKER_V0;
}
static int __PACEMAKER_Check12 [] = {1,2,7,0,1,7};
static void __PACEMAKER_A13 () {
__PACEMAKER_V3 = 60000/(__PACEMAKER_V7*5);
}
static int __PACEMAKER_Check13 [] = {1,1,7,1,3};

/* PROCEDURE CALLS */

static void __PACEMAKER_A14 () {
SEND_PULSE(__PACEMAKER_V4);
}
static int __PACEMAKER_Check14 [] = {1,1,4,0};

/* CONDITIONS */

static int __PACEMAKER_A15 () {
__PACEMAKER_GENERIC_TEST(__PACEMAKER_V6>((12000/(__PACEMAKER_V5-3))+2));
}
static int __PACEMAKER_Check15 [] = {1,2,6,5,0};

/* DECREMENTS */

/* START ACTIONS */

/* KILL ACTIONS */

/* SUSPEND ACTIONS */

/* ACTIVATE ACTIONS */

/* WRITE ARGS ACTIONS */

/* RESET ACTIONS */

static void __PACEMAKER_A16 () {
;
__ResetVariable(0);
}
static int __PACEMAKER_Check16 [] = {1,0,0};
static void __PACEMAKER_A17 () {
;
__ResetVariable(3);
}
static int __PACEMAKER_Check17 [] = {1,0,0};
static void __PACEMAKER_A18 () {
;
__ResetVariable(4);
}
static int __PACEMAKER_Check18 [] = {1,0,0};
static void __PACEMAKER_A19 () {
;
__ResetVariable(5);
}
static int __PACEMAKER_Check19 [] = {1,0,0};

/* ACTION SEQUENCES */


static int *__PACEMAKER_CheckArray[] = {
0,
__PACEMAKER_Check1,
__PACEMAKER_Check2,
__PACEMAKER_Check3,
__PACEMAKER_Check4,
__PACEMAKER_Check5,
__PACEMAKER_Check6,
__PACEMAKER_Check7,
__PACEMAKER_Check8,
__PACEMAKER_Check9,
__PACEMAKER_Check10,
__PACEMAKER_Check11,
__PACEMAKER_Check12,
__PACEMAKER_Check13,
__PACEMAKER_Check14,
__PACEMAKER_Check15,
__PACEMAKER_Check16,
__PACEMAKER_Check17,
__PACEMAKER_Check18,
__PACEMAKER_Check19
};
static int **__PACEMAKER_PCheckArray =  __PACEMAKER_CheckArray;

/* INIT FUNCTION */

#ifndef NO_INIT
void PACEMAKER_initialize () {
}
#endif

/* SHOW VARIABLE FUNCTION */

char* __PACEMAKER_show_variable (int __V) {
extern struct __VariableEntry __PACEMAKER_VariableTable[];
struct __VariableEntry* p_var = &__PACEMAKER_VariableTable[__V];
if (p_var->type_code < 0) {return __PredefinedTypeToText(p_var->type_code, p_var->p_variable);
} else {
switch (p_var->type_code) {
default: return 0;
}
}
}

/* SET VARIABLE FUNCTION */

static void __PACEMAKER_set_variable(int __Type, char* __pVar, char* __Text) {
}

/* CHECK VALUE FUNCTION */

static int __PACEMAKER_check_value (int __Type, char* __Text) {
return 0;
}

/* SIMULATION TABLES */

struct __InstanceEntry __PACEMAKER_InstanceTable [] = {
{"PACEMAKER",0,"","pacemaker.strl",{1,1,11,0},{1,11,1,0},{0,0,0,0}},
{"COORDINATOR",0,"","coordinator.strl",{1,1,1,1},{1,20,1,1},{1,5,9,0}},
{"PULSE_TRIGGER",1,"","pulseTrigger.strl",{1,1,11,2},{1,10,1,2},{1,6,13,1}},
{"TIMEOUT",0,"","timeout.strl",{1,1,11,3},{1,26,1,3},{1,7,9,0}},
{"FREQ_CONV",0,"","freqConv.strl",{1,1,11,4},{1,15,1,4},{1,9,9,0}},
};

struct __SignalEntry __PACEMAKER_SignalTable [] = {
{"INT",1,0,0,{1,2,7,0},0,(void*) NULL,0,(void*) NULL,0,(void*) NULL},
{"HEART_BEAT",33,0,0,{1,2,21,0},0,(void*) NULL,0,(void*) NULL,0,(void*) NULL},
{"TIME_OUT",34,0,0,{1,3,8,0},0,(void*) NULL,0,(void*) NULL,0,(void*) NULL},
{"RESET",40,0,0,{1,4,12,0},0,(void*) NULL,0,(void*) NULL,0,(void*) NULL},
{"BPM",8,3,0,{1,4,19,0},0,(void*) NULL,0,(void*) NULL,0,(void*) NULL},
{"TRIGGER",8,4,0,{1,5,16,1},0,(void*) NULL,0,(void*) NULL,0,(void*) NULL},
{"TOUT",48,0,0,{1,11,22,3},0,(void*) NULL,0,(void*) NULL,0,(void*) NULL}};

struct __InputEntry __PACEMAKER_InputTable [] = {
{"INT",33,"integer",0,-3,0,0,_check_integer,PACEMAKER_IS_INT,0,{1,2,7,0}},
{"HEART_BEAT",44,0,0,-1,0,1,0,PACEMAKER_IS_HEART_BEAT,0,{1,2,21,0}}};

struct __VariableEntry __PACEMAKER_VariableTable [] = {
{"__PACEMAKER_V0","V0","integer",-3,1,0,(char*)&__PACEMAKER_V0,"INT",0,0,0,{1,2,7,0}},
{"__PACEMAKER_V1","V1","boolean",-2,2,0,(char*)&__PACEMAKER_V1,"INT",0,0,0,{1,2,7,0}},
{"__PACEMAKER_V2","V2","boolean",-2,2,0,(char*)&__PACEMAKER_V2,"HEART_BEAT",0,0,0,{1,2,21,0}},
{"__PACEMAKER_V3","V3","integer",-3,1,0,(char*)&__PACEMAKER_V3,"BPM",0,0,0,{1,4,19,0}},
{"__PACEMAKER_V4","V4","float",-5,1,0,(char*)&__PACEMAKER_V4,"TRIGGER",0,0,0,{1,5,16,1}},
{"__PACEMAKER_V5","V5","integer",-3,0,0,(char*)&__PACEMAKER_V5,"lastBPM",0,0,0,{1,5,9,3}},
{"__PACEMAKER_V6","V6","integer",-3,0,0,(char*)&__PACEMAKER_V6,"passed",0,0,0,{1,9,17,3}},
{"__PACEMAKER_V7","V7","integer",-3,0,0,(char*)&__PACEMAKER_V7,"ticks",0,0,0,{1,5,13,4}}
};

struct __HaltEntry __PACEMAKER_HaltTable [] = {
{{1,11,1,0}},
{{1,10,21,1}},
{{1,15,17,1}},
{{1,18,9,1}},
{{1,8,9,2}},
{{1,6,9,3}},
{{1,12,21,3}},
{{1,10,17,3}},
{{1,23,13,3}},
{{1,7,17,4}},
{{1,6,13,4}}
};


static void __PACEMAKER__reset_input () {
__PACEMAKER_V1 = _false;
__PACEMAKER_V2 = _false;
}


/* MODULE DATA FOR SIMULATION */

int PACEMAKER();
int PACEMAKER_reset();

static struct __ModuleEntry __PACEMAKER_ModuleData = {
"Simulation interface release 5","PACEMAKER",
5,0,7,2,0,0,1,3,1,0,0,8,0,11,0,0,0,
__PACEMAKER_HaltList,
__PACEMAKER_AwaitedList,
__PACEMAKER_EmittedList,
__PACEMAKER_StartedList,
__PACEMAKER_KilledList,
__PACEMAKER_SuspendedList,
__PACEMAKER_ActiveList,
0,0,
PACEMAKER_initialize,PACEMAKER,PACEMAKER_reset,
__PACEMAKER_show_variable,__PACEMAKER_set_variable,__PACEMAKER_check_value,0,
__PACEMAKER_InstanceTable,
0,
__PACEMAKER_SignalTable,__PACEMAKER_InputTable,0,
0,0,
__PACEMAKER_VariableTable,
0,
__PACEMAKER_HaltTable,
0};

/* REDEFINABLE BIT TYPE */

#ifndef __SSC_BIT_TYPE_DEFINED
typedef char __SSC_BIT_TYPE;
#endif

/* REGISTER VARIABLES */

static __SSC_BIT_TYPE __PACEMAKER_R[10] = {_true,
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

int PACEMAKER () {
/* AUXILIARY VARIABLES */

static __SSC_BIT_TYPE E[30];

__PACEMAKER_ModuleData.awaited_list = __PACEMAKER_AwaitedList;
__ResetModuleEntryBeforeReaction();
E[0] = __PACEMAKER_R[5]&&!(__PACEMAKER_R[0]);
E[1] = E[0]&&(__CheckVariables(__PACEMAKER_CheckArray[1]),
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__PACEMAKER_A1());
if (E[1]) {
__CheckVariables(__PACEMAKER_CheckArray[9]);__PACEMAKER_A9();
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A9\n");
#endif
}
E[2] = E[1]&&(__CheckVariables(__PACEMAKER_CheckArray[15]),
#ifdef TRACE_ACTION
fprintf(stderr, "test 15\n"),
#endif
__PACEMAKER_A15());
if (E[2]) {
__AppendToList(__PACEMAKER_EmittedList,2);
__AppendToList(__PACEMAKER_EmittedList,6);
}
if (E[2]) {
__CheckVariables(__PACEMAKER_CheckArray[3]);__PACEMAKER_A3();
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A3\n");
#endif
}
E[3] = __PACEMAKER_R[0]&&!((__CheckVariables(__PACEMAKER_CheckArray[1]),
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__PACEMAKER_A1()));
if (E[3]) {
__CheckVariables(__PACEMAKER_CheckArray[16]);__PACEMAKER_A16();
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A16\n");
#endif
}
if (__PACEMAKER_R[0]) {
__CheckVariables(__PACEMAKER_CheckArray[17]);__PACEMAKER_A17();
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A17\n");
#endif
}
if (__PACEMAKER_R[0]) {
__CheckVariables(__PACEMAKER_CheckArray[18]);__PACEMAKER_A18();
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A18\n");
#endif
}
E[4] = (__PACEMAKER_R[2]&&!(__PACEMAKER_R[0]))||__PACEMAKER_R[0];
E[5] = E[4]&&(__CheckVariables(__PACEMAKER_CheckArray[2]),
#ifdef TRACE_ACTION
fprintf(stderr, "test 2\n"),
#endif
__PACEMAKER_A2());
E[6] = __PACEMAKER_R[1]&&!(__PACEMAKER_R[0]);
E[7] = E[6]&&(__CheckVariables(__PACEMAKER_CheckArray[2]),
#ifdef TRACE_ACTION
fprintf(stderr, "test 2\n"),
#endif
__PACEMAKER_A2());
E[7] = E[5]||E[7];
if (E[7]) {
__AppendToList(__PACEMAKER_EmittedList,3);
}
E[5] = __PACEMAKER_R[9]&&!(__PACEMAKER_R[0]);
E[8] = E[5]&&E[7];
E[9] = __PACEMAKER_R[8]||__PACEMAKER_R[9];
E[10] = __PACEMAKER_R[8]&&!(__PACEMAKER_R[0]);
E[11] = E[10]&&(__CheckVariables(__PACEMAKER_CheckArray[1]),
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__PACEMAKER_A1());
if (E[11]) {
__CheckVariables(__PACEMAKER_CheckArray[12]);__PACEMAKER_A12();
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A12\n");
#endif
}
E[10] = E[10]&&!((__CheckVariables(__PACEMAKER_CheckArray[1]),
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__PACEMAKER_A1()));
E[10] = E[11]||(__PACEMAKER_R[8]&&E[10]);
E[12] = (E[9]&&!(__PACEMAKER_R[8]))||E[10];
E[5] = __PACEMAKER_R[9]&&E[5]&&!(E[7]);
E[13] = (E[9]&&!(__PACEMAKER_R[9]))||E[5];
E[8] = E[8]&&E[12]&&(E[13]||E[8]);
if (E[8]) {
__AppendToList(__PACEMAKER_EmittedList,4);
}
if (E[8]) {
__CheckVariables(__PACEMAKER_CheckArray[13]);__PACEMAKER_A13();
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A13\n");
#endif
}
E[6] = E[6]&&!((__CheckVariables(__PACEMAKER_CheckArray[2]),
#ifdef TRACE_ACTION
fprintf(stderr, "test 2\n"),
#endif
__PACEMAKER_A2()));
E[6] = __PACEMAKER_R[1]&&E[6];
E[14] = E[6]&&E[2];
if (E[14]) {
__AppendToList(__PACEMAKER_EmittedList,5);
}
if (E[14]) {
__CheckVariables(__PACEMAKER_CheckArray[6]);__PACEMAKER_A6();
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A6\n");
#endif
}
E[15] = !(_true);
E[16] = (__PACEMAKER_R[3]&&!(__PACEMAKER_R[0]))||__PACEMAKER_R[0];
E[17] = E[16]&&E[14];
if (E[17]) {
__CheckVariables(__PACEMAKER_CheckArray[14]);__PACEMAKER_A14();
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A14\n");
#endif
}
E[16] = E[17]||(E[16]&&!(E[14]));
E[18] = E[7]||E[14];
E[4] = E[4]&&!((__CheckVariables(__PACEMAKER_CheckArray[2]),
#ifdef TRACE_ACTION
fprintf(stderr, "test 2\n"),
#endif
__PACEMAKER_A2()));
E[6] = E[4]||(__PACEMAKER_R[1]&&E[6]&&!(E[2]));
E[4] = __PACEMAKER_R[2]||__PACEMAKER_R[1];
E[19] = __PACEMAKER_R[3]||E[4];
E[4] = (E[16]||E[18]||E[6])&&((E[19]&&!(__PACEMAKER_R[3]))||E[16])&&((E[19]&&!(E[4]))||E[18]||E[6]);
if (__PACEMAKER_R[0]) {
__CheckVariables(__PACEMAKER_CheckArray[19]);__PACEMAKER_A19();
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A19\n");
#endif
}
E[20] = __PACEMAKER_R[4]&&!(__PACEMAKER_R[0]);
E[21] = (__PACEMAKER_R[0]&&E[8])||(E[20]&&E[8]);
if (E[21]) {
__CheckVariables(__PACEMAKER_CheckArray[7]);__PACEMAKER_A7();
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A7\n");
#endif
}
E[22] = E[21]||(__PACEMAKER_R[7]&&!(__PACEMAKER_R[0]));
if (E[22]) {
__CheckVariables(__PACEMAKER_CheckArray[8]);__PACEMAKER_A8();
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A8\n");
#endif
}
E[0] = E[0]&&!((__CheckVariables(__PACEMAKER_CheckArray[1]),
#ifdef TRACE_ACTION
fprintf(stderr, "test 1\n"),
#endif
__PACEMAKER_A1()));
E[0] = E[22]||(E[1]&&!(E[2]))||(__PACEMAKER_R[5]&&E[0]);
E[23] = __PACEMAKER_R[6]&&!(__PACEMAKER_R[0]);
E[24] = (E[22]&&!(E[7]))||(__PACEMAKER_R[6]&&E[23]&&!(E[7]));
E[25] = __PACEMAKER_R[5]||__PACEMAKER_R[6];
E[26] = (E[25]&&!(__PACEMAKER_R[5]))||E[0];
E[27] = (E[25]&&!(__PACEMAKER_R[6]))||E[24];
E[28] = (E[0]||E[24])&&E[26]&&E[27];
E[29] = E[22]&&E[7];
E[7] = E[23]&&E[7];
E[26] = E[26]||E[2];
E[7] = (E[29]||E[7])&&E[26]&&(E[27]||E[29]||E[7]);
if (E[7]) {
__CheckVariables(__PACEMAKER_CheckArray[10]);__PACEMAKER_A10();
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A10\n");
#endif
}
E[27] = E[2]&&E[26]&&E[27];
E[26] = E[7]||E[27];
E[20] = (__PACEMAKER_R[0]&&!(E[8]))||(__PACEMAKER_R[4]&&E[20]&&!(E[8]));
E[29] = __PACEMAKER_R[0]||E[8];
if (E[29]) {
__CheckVariables(__PACEMAKER_CheckArray[11]);__PACEMAKER_A11();
#ifdef TRACE_ACTION
fprintf(stderr, "__PACEMAKER_A11\n");
#endif
}
E[13] = (E[10]||E[5])&&E[12]&&E[13];
E[25] = __PACEMAKER_R[7]||E[25]||__PACEMAKER_R[4];
E[12] = E[19]||E[25]||E[9];
E[13] = (E[4]||E[28]||E[26]||E[20]||E[29]||E[13])&&((E[12]&&!(E[19]))||E[4])&&((E[12]&&!(E[25]))||E[28]||E[26]||E[20])&&((E[12]&&!(E[9]))||E[29]||E[13]);
E[27] = E[7]||E[27];
__PACEMAKER_R[5] = E[0]&&!(E[27]);
__PACEMAKER_R[6] = E[24]&&!(E[27]);
__PACEMAKER_R[8] = E[29]||(E[10]&&!(E[8]));
__PACEMAKER_R[9] = E[29]||(E[5]&&!(E[8]));
__PACEMAKER_R[0] = !(_true);
__PACEMAKER_R[1] = E[6];
if (__PACEMAKER_R[1]) { __AppendToList(__PACEMAKER_HaltList,1); }
__PACEMAKER_R[2] = E[18];
if (__PACEMAKER_R[2]) { __AppendToList(__PACEMAKER_HaltList,2); }
__PACEMAKER_R[3] = E[16];
if (__PACEMAKER_R[3]) { __AppendToList(__PACEMAKER_HaltList,4); }
__PACEMAKER_R[4] = E[20];
if (__PACEMAKER_R[4]) { __AppendToList(__PACEMAKER_HaltList,5); }
if (__PACEMAKER_R[5]) { __AppendToList(__PACEMAKER_HaltList,6); }
if (__PACEMAKER_R[6]) { __AppendToList(__PACEMAKER_HaltList,7); }
__PACEMAKER_R[7] = E[26];
if (__PACEMAKER_R[7]) { __AppendToList(__PACEMAKER_HaltList,8); }
if (__PACEMAKER_R[8]) { __AppendToList(__PACEMAKER_HaltList,9); }
if (__PACEMAKER_R[9]) { __AppendToList(__PACEMAKER_HaltList,10); }
if (!E[13]) { __AppendToList(__PACEMAKER_HaltList,0); }
__ResetModuleEntryAfterReaction();
__PACEMAKER_ModuleData.awaited_list = __PACEMAKER_AllAwaitedList;
__PACEMAKER__reset_input();
return E[13];
}

/* AUTOMATON RESET */

int PACEMAKER_reset () {
__PACEMAKER_ModuleData.awaited_list = __PACEMAKER_AwaitedList;
__ResetModuleEntry();
__PACEMAKER_ModuleData.awaited_list = __PACEMAKER_AllAwaitedList;
__PACEMAKER_ModuleData.state = 0;
__PACEMAKER_R[0] = _true;
__PACEMAKER_R[1] = _false;
__PACEMAKER_R[2] = _false;
__PACEMAKER_R[3] = _false;
__PACEMAKER_R[4] = _false;
__PACEMAKER_R[5] = _false;
__PACEMAKER_R[6] = _false;
__PACEMAKER_R[7] = _false;
__PACEMAKER_R[8] = _false;
__PACEMAKER_R[9] = _false;
__PACEMAKER__reset_input();
return 0;
}
char* CompilationType = "Compiled Sorted Equations";

int __NumberOfModules = 1;
struct __ModuleEntry* __ModuleTable[] = {
&__PACEMAKER_ModuleData
};
