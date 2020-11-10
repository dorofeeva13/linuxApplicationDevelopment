CFLAGS = -Wall
TEST_FLAGS = `pkg-config --cflags check`
CHECK_LIBS = `pkg-config --libs check`
TEST_LIBS  = $(CHECK_LIBS) -L$(BUILD_DIR) -lbuf

.ts.c:
	checkmk $< > $@

all: src/buf.c src/buf.h
	gcc $(CFLAGS) -shared -fPIC $< -o libbuf.so

test: test/tests.c libbuf.so
	gcc $(TEST_FLAGS) -I src $< -o $@ $(TEST_LIBS)

profile: src/buf.c src/buf.h test
	gcc $(CFLAGS) --coverage -g -O0 -shared -fPIC -lgcov $< -o libbuf.so

clean:
	rm *.so

.SUFFIXES: .ts .c
.PHONY: all test profile clean