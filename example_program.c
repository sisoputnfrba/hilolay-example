#include <stdio.h>
#include <unistd.h>
#include <hilolay/hilolay.h>

void recursiva(int cant) {
    if(cant > 0) recursiva(cant - 1);
}

void *test1(void *arg) {
    int i, tid;

    for (i = 0; i < 10; i++) {
        tid = hilolay_get_tid();
        printf("Soy el ult %d mostrando el numero %d \n", tid, i);
        usleep(5000 * i * tid); /* Randomizes the sleep, so it gets larger after a few iterations */

        recursiva(i);

        // Round Robin will yield the CPU
        hilolay_yield();
    }

    return 0;
}

void *test2(void *arg) {
    int i, tid;

    for (i = 0; i < 5; i++) {
        tid = hilolay_get_tid();
        printf("Soy el ult %d mostrando el numero %d \n", tid, i);
        usleep(2000 * i * tid); /* Randomizes the sleep, so it gets larger after a few iterations */
        recursiva(i);
        hilolay_yield();
    }

    return 0;
}


/* Main program */
int main() {
    int i;

    hilolay_init();
    struct hilolay_t th1;
    struct hilolay_t th2;

	hilolay_create(&th1, NULL, &test1, NULL);
	hilolay_create(&th2, NULL, &test2, NULL);

	hilolay_join(&th2);
	hilolay_join(&th1);
    return hilolay_return(0);
}
