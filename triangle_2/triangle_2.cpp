#include <GL/glew.h>
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

	glewExperimental = GL_TRUE;
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

	//Begin edit
	float points[] = {
	   0.0f,  0.5f,  0.0f,
  	 0.5f, -0.5f,  0.0f,
  	-0.5f, -0.5f,  0.0f
	};

	GLuint vbo = 0;
	glGenBuffers (1, &vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);


	GLuint vao = 0;
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	const char* vertex_shader =
		"#version 150\n"
		"in vec3 vp;"
		"void main () {"
		"  gl_Position = vec4 (vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 150\n"
		"out vec4 frag_colour;"
		"void main () {"
		"  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}";

	GLuint vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vs, 1, &vertex_shader, NULL);
	glCompileShader (vs);
	GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fs, 1, &fragment_shader, NULL);
	glCompileShader (fs);

	// glGEtShaderiv(shader, GL_COMPILE_STATUS, &bDidCompile);

	GLuint shader_programme = glCreateProgram ();
	glAttachShader (shader_programme, fs);
	glAttachShader (shader_programme, vs);
	glLinkProgram (shader_programme);

	// glGetProgramiv(program, GL_LINK_STATUS, &)bDidLink);

	while (!glfwWindowShouldClose(window)) {
	  // wipe the drawing surface clear
		  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		  glUseProgram (shader_programme);
		  glBindVertexArray (vao);
		  // draw points 0-3 from the currently bound VAO with current in-use shader
		  glDrawArrays (GL_TRIANGLES, 0, 3);
		  // update other events like input handling 
		  glfwPollEvents ();
		  // put the stuff we've been drawing onto the display
		  glfwSwapBuffers (window);
	}
	//End edit
	// while (!glfwWindowShouldClose(window)){
	// 	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	// 	glClear(GL_COLOR_BUFFER_BIT);
	// 	glLoadIdentity();
	// 	glfwSwapBuffers(window);
	// 	glfwPollEvents();
	// }

		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_SUCCESS);	
	};