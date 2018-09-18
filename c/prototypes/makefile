CFLAGS=-Wall -Werror -g

all: escape-char live-count counter.o counter_main raw_mode.o char-count.o fixed-width-input.o input_processor_main

raw_mode.o: raw_mode.c
char-count.o: char-count.c 
fixed-width-input.o: fixed-width-input.c
input_processor_main: input_processor_main.c raw_mode.o char-count.o fixed-width-input.o

counter.o: counter.c
counter_main: counter_main.c counter.o raw_mode.o

live-count: live-count.c raw_mode.o

clean:
	rm -rf *~ # Remove Emacs temp files
	rm -rf escape-char char-count fixed-width-input live-count counter.o counter_main char-count.o fixed-width-input.o input_processor_main raw_mode.o
