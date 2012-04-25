# Tuan T. Pham <tuan at vt dot edu>

all: memd.so

memd.o: memd.c
	gcc -fPIC -g -c -o memd.o memd.c

memd.so: memd.o
	gcc -shared -o memd.so memd.o -lpthread

clean:
	rm -f memd.o memd.so
