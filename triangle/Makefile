CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lGL -lGLU -lGLEW -lglfw3 -lXi -lXrandr -lm

OBJECTS=triangle.o
SOURCE=triangle.cpp

triangle: $(OBJECTS)
	$(CC) $(OBJECTS) -o triangle $(LDFLAGS)

triangle.o: $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE)

clean:
	rm -f *.o triangle