Useful Commands
===============

To obtain an .o file:
---------------------
g++ -c playground.cpp

To compile into an .exe file:
-----------------------------
g++ playground.o -o playground -lGL -lGLU -lglfw3 -lGLEW -lglut... -lX11 -lXxf86vm -lXrandr -lpthread -lXi

GL = OpenGL
GLU = OpenGL Utilities Library
Glfw3 = window api
Glew = Loading library
Glut = window api (works for freeglut I believe)

To find out GLSL version:
-----------------------------
glxinfo | grep -i opengl 

_Note: GLSL Version 130 works with OpenGL 3.0. Check Wikipedia if different versions for compatibility_


Useful Q&A Resources
====================

Delete/Detach programs/shaders:
-------------------------------
gamedev.stackexchange.com/questions/47910/after-a-successful-glinkprogram-should-i-delete-detach-my-shaders
