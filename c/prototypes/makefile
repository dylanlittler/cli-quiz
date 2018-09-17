CFLAGS=-Wall -Werror -g

all: escape-char live-count counter.o counter_main raw_mode.o char-count.o fixed-width-input.o input-processor

raw_mode.o: raw_mode.c
char-count.o: char-count.c 
fixed-width-input.o: fixed-width-input.c
input-processor: input-processor.c raw_mode.o char-count.o fixed-width-input.o

counter.o: counter.c
counter_main: counter_main.c counter.o

clean:
	rm -rf *~ # Remove Emacs temp files
	rm -rf escape-char char-count fixed-width-input live-count counter.o counter_main char-count.o fixed-width-input.o input-processor raw_mode.o
