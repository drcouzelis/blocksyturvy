OBJECTS = block.o gamecontrol.o gameinput.o gamescreen.o main.o
HEADERS = block.h blocksyturvy.h gamecontrol.h gameinput.h gamescreen.h
CC = gcc
DEBUG = -Wall
LINKING_OPTIONS = -l objc
CFLAGS = $(shell allegro-config --cflags) $(shell pkg-config --cflags glib-2.0)
LDFLAGS = $(shell allegro-config --libs) $(shell pkg-config --libs glib-2.0)

blocksyturvy: $(OBJECTS)
	 $(CC) $(DEBUG) $(LINKING_OPTIONS) -o ../bin/blocksyturvy $(OBJECTS) $(LDFLAGS)

block.o: block.c $(HEADERS)
	 $(CC) $(DEBUG) -c block.c $(CFLAGS)

gamecontrol.o: gamecontrol.c $(HEADERS)
	 $(CC) $(DEBUG) -c gamecontrol.c $(CFLAGS)

gameinput.o: gameinput.c $(HEADERS)
	 $(CC) $(DEBUG) -c gameinput.c $(CFLAGS)

gamescreen.o: gamescreen.c $(HEADERS)
	 $(CC) $(DEBUG) -c gamescreen.c $(CFLAGS)

main.o: main.c $(HEADERS)
	 $(CC) $(DEBUG) -c main.c $(CFLAGS)

clean:
	 rm -f $(OBJECTS)

