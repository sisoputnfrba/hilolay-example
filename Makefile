UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	CFLAGS := -D_XOPEN_SOURCE -Wno-deprecated-declarations
endif

CC := gcc
NAME := hilolayex
BUILD=bin

all: clean $(NAME).so 

clean:
	$(RM) *.o
	$(RM) *.so
	$(RM) -r bin/
	mkdir -p bin

$(NAME).o:
	$(CC) -c -Wall $(CFLAGS) -fpic example_alumnos.c -o $(BUILD)/$(NAME).o -lhilolay

$(NAME).so: $(NAME).o
	$(CC) -shared -o $(BUILD)/lib$(NAME).so $(BUILD)/$(NAME).o -lhilolay
	
example:
	$(CC) -L./$(BUILD)/ -Wall $(CFLAGS) -o $(BUILD)/example example_program.c -l$(NAME) -lhilolay
	
test: clean all example
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):./$(BUILD) ./$(BUILD)/example
