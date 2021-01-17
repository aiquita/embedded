#if defined(__cplusplus)
extern "C"
{
#endif
void PACEMAKER_I_HEART_BEAT();
void PACEMAKER_I_INT(int);
void PACEMAKER_O_BPM(int);
// void PACEMAKER_O_PASSED(int);
void PACEMAKER_O_TIME_OUT();
int PACEMAKER();
#if defined(__cplusplus)
}
#endif