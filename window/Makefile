CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lGL -lGLU -lGLEW -lglut -lm

OBJECTS=window.o
SOURCE=window.cpp

window: $(OBJECTS)
	$(CC) $(OBJECTS) -o window $(LDFLAGS)

window.o: $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE)

clean:
	rm -f *.o window