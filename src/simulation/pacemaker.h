#if defined(__cplusplus)
extern "C"
{
#endif
void pacemaker_I_HEART_BEAT();
void pacemaker_I_INT(int);
// void pacemaker_O_BPM(int);
// void pacemaker_O_PASSED(int);
void pacemaker_O_TIME_OUT();
int pacemaker();
void SEND_PULSE(float scale) {
	printf("Pulse %f", scale);
}
#if defined(__cplusplus)
}
#endif