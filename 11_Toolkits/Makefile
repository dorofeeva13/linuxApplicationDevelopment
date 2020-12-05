CFLAGS = -Wall -g $(GLIB_CFLAGS)
GLIB_CFLAGS  = `pkg-config --cflags glib-2.0`
LDFLAGS = `pkg-config --libs glib-2.0`

all: main

counter: main.c
	gcc $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm main