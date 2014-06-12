#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

//displays error if error_callback
static void error_callback(int error, const char* description)
	{
		fputs(description, stderr);
	}
//sets window to close if escape key pressed
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}


int main(void){

	//Set error callback before init glfw to make sure errors can be reported if init fails.
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()){
		exit(EXIT_FAILURE);
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Standard GLFW3 Window", NULL, NULL); 
	//To make fullscreen, place 'glfwGetPrimaryMonitor() in fourth param'
	//If window init failed, terminate, exit
	if (!window){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Make current window the current context for OpenGL to work on
	glfwMakeContextCurrent(window);

	//Key callback set
	glfwSetKeyCallback(window, key_callback);

	//If not flagged for close
	while(!glfwWindowShouldClose(window))
	{
		//Keep running
		//Get framebuffer's dimensions and call glViewport
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // Choose color for clearing background (RGBA)
		glClear(GL_COLOR_BUFFER_BIT); //Clear background with color chosen  
		glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations  

		//After rendering, we swap buffers to display rendered image
		glfwSwapBuffers(window);

		//Process events received and return immediately, renders continually
		glfwPollEvents();
	}


		glfwDestroyWindow(window);

		glfwTerminate();
		exit(EXIT_SUCCESS);

	};