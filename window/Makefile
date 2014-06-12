CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lGL -lGLU -lGLEW -lglut -lm

OBJECTS=window_glut.o
SOURCE=window_glut.cpp

window_glut: $(OBJECTS)
	$(CC) $(OBJECTS) -o window_glut $(LDFLAGS)

window_glut.o: $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE)

clean:
	rm -f *.o window_glut