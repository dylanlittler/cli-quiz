CFLAGS=-Wall -Werror -g

all: escape-char char-count fixed-width-input live-count count-functions.o counter

count-functions.o: count-functions.c

counter: counter.c count-functions.o

clean:
	rm -rf *~ # Remove Emacs temp files
	rm -rf escape-char char-count fixed-width-input live-count
