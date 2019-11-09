# Target library
lib := libuthread.a
objs := sem.o tps.o

all: $(lib)

libuthread.a: $(objs)
	ar rcs $(lib) $(objs)

sem.o: sem.c
	cc -c -g -Wall -Werror sem.c

tps.o: tps.c
	cc -c -g -Wall -Werror tps.c

clean:
	rm -f $(lib) $(objs)
