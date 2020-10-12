GENERATES = liboutput_static.a liboutput.so prog prog-a prog-so
TRASH = *.o *~ o.*
CFLAGS = -fPIC -Wall

all: prog prog-a prog-so

fun.o: outlib.h

liboutput_static.a:	fun.o const.o
	ar -rcs $@ $^

prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc $(CFLAGS) -L. $< -loutput_static -o $@

liboutput.so:	fun.o const.o
	$(CC) -shared $^ -o $@

prog-so: prog.o liboutput.so
	cc $(CFLAGS) -L. $< -loutput -o $@

test:	prog prog-a prog-so
	./prog > test1
	./prog-a > test2
	LD_LIBRARY_PATH=`pwd`./prog-so > test3

	./prog param1 > test11
	./prog-a param1 > test22
	LD_LIBRARY_PATH=`pwd`./prog-so param1 > test33
	cmp test11 test22
	cmp test22 test33

	./prog param1 param2 > test111
	./prog-a param1 param2 > test222
	LD_LIBRARY_PATH=`pwd`./prog-so param1 param2 > test333
	cmp test111 test222
	cmp test222 test333

clean: 
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)