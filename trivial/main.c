#include <stdio.h>
#include <time.h>
#include "trivial.h"

extern int trivial ();

int trivial_O_O(int o){
    return o;
}

int PRINT() {
    printf("PRINT\n");
    return 0;
}

int main(void) {
    int pr = 0;
    long t = time(NULL);
    while(pr < 5) {
        long nt;
        if((nt = time(NULL)) - t >= 1) {
            t = nt;
            trivial_I_SECOND();
            pr++;
        }
        trivial();
    }
    return 0;
}