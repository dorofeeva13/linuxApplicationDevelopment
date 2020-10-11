GENERATES = liboutput_static.a liboutput.so prog prog-a prog-so
TRASH = *.o *~ o.*
CFLAGS = -fPIC -Wall

all: prog prog-a prog-so

fun.o: outlib.h

liboutput_static.a:	fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.o const.o
	cc -shared $(CFLAGS) $^ -o $@

prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc $(CFLAGS) -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc $(CFLAGS) -L. $< -loutput -o $@

test:	prog prog-a prog-so
	export LD_LIBRARY_PATH=$(CURR_DIR)

clean: rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)