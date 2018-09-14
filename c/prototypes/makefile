CFLAGS=-Wall -Werror -g

all: escape-char char-count fixed-width-input live-count counter.o counter_main

counter.o: counter.c

counter_main: counter_main.c counter.o

clean:
	rm -rf *~ # Remove Emacs temp files
	rm -rf escape-char char-count fixed-width-input live-count counter.o counter_main
