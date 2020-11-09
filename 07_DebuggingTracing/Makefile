FLAGS = -shared -fPIC

all: unlink.c
	gcc unlink.c $(FLAGS) -o unlink.so -ldl

test: unlink.so
	touch file1 file2
	rm file1 file2

	touch file1 file2
	LD_PRELOAD=./unlink.so rm file2
	LD_PRELOAD=./unlink.so rm file1

clean:
	rm -f *.so file1 file2