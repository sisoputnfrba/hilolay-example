#include <hilolay/alumnos.h>

int create_thread(void (*f)(void)) {
	return 1;
}

static struct hilolay_operations hiloops = {
		.create_thread = create_thread
};

void hilolay_init(void){
	init_internal(&hiloops);
}
