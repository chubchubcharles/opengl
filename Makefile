CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lGL -lGLU -lGLEW -lglfw3 -lXrandr -lXi -lm

OBJECTS=window_glfw3.o
SOURCE=window_glfw3.cpp

window_glfw3: $(OBJECTS)
	$(CC) $(OBJECTS) -o window_glfw3 $(LDFLAGS)

window_glfw3.o: $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE)

clean:
	rm -f *.o window_glfw3