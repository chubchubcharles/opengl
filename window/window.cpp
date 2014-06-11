#include <GL/glew.h>   
#include <GL/glut.h> 
  
void display (void) {  
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // Choose color for clearing background (RGBA)
	glClear(GL_COLOR_BUFFER_BIT); //Clear background with color chosen  
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations  
	  
	glFlush(); // Flush the OpenGL buffers to the window  
}  
  
int main (int argc, char **argv) {  

	glutInit(&argc, argv);   
	glutInitDisplayMode (GLUT_SINGLE); // Set basic display mode to single buffer 
	glutInitWindowSize (500, 500); // Set the width and height of the window  
	glutInitWindowPosition (100, 100); // Set the position of the window  
	
	glutCreateWindow ("OpenGL Window"); // Set the title for the window  
	  
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering  
	  
	glutMainLoop(); // Enter GLUT's main loop, which is repeatedly displaying. Not interesting, yet.
} 

//Modeled after http://www.swiftless.com/tutorials/opengl/window.html