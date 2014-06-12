CC=g++
CFLAGS=-c -Wall
LDFLAGS= -lGL -lGLEW -lglfw3 -lXrandr -lXi

OBJECTS=version.o
SOURCE=version.cpp

version: $(OBJECTS)
	$(CC) $(OBJECTS) -o version $(LDFLAGS)

version.o: $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE)

clean:
	rm -f *.o version