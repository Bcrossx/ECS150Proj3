# Target library
lib := libuthread.a
objs := sem.o tps.o
objs2 := sem.o tps.o thread.o queue.o

all: $(lib)

libuthread.a: $(objs)
	ar rcs $(lib) $(objs2)

sem.o: sem.c
	cc -c -g -Wall -Werror sem.c

tps.o: tps.c
	cc -c -g -Wall -Werror tps.c

clean:
	rm -f $(lib) $(objs)
