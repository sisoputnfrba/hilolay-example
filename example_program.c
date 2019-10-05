#include <hilolay/hilolay.h>

void recursiva(int cant) {
    if(cant > 0) recursiva(cant - 1);
}

void test1() {
    int i, tid;

    for (i = 0; i < 10; i++) {
        tid = hilolay_get_tid();
        printf("Soy el ult %d mostrando el numero %d \n", tid, i);
        usleep(5000 * i * tid); /* Randomizes the sleep, so it gets larger after a few iterations */

        recursiva(i);

        // Round Robin will yield the CPU
        th_yield();
    }
}

void test2() {
    int i, tid;

    for (i = 0; i < 5; i++) {
        tid = hilolay_get_tid();
        printf("Soy el ult %d mostrando el numero %d \n", tid, i);
        usleep(2000 * i * tid); /* Randomizes the sleep, so it gets larger after a few iterations */
        recursiva(i);
        th_yield();
    }
}

/* Main program */
void main() {
    int i;

    hilolay_init();
	th_create(test1);
	th_create(test1);

    th_return(0);
}
