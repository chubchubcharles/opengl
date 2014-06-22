/* Using the standard output for fprintf */
#include <stdio.h>
#include <stdlib.h>
/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
/* ADD GLOBAL VARIABLES HERE LATER */
GLuint program; 
GLint attribute_coord2d;
//#define DEBUG

static void error_callback(int error, const char* description)
  {
    fputs(description, stderr);
  }
//sets window to close if escape key pressed
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key == 'P' && action == GLFW_PRESS)
        fputs("P was pressed!", stderr);
}

int init_resources(void)
{
  /* FILLED IN LATER */
  fputs("start init resources\n", stderr);

  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    /* Problem: glewInit failed, something is seriously wrong. */
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    
  }
  fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

  
  GLint compile_ok = GL_FALSE, link_ok  = GL_FALSE;
 
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  fputs("shader created\n", stderr);
  const char *vs_source = "#version 130\n"
      "attribute vec2 coord2d;\n"
      "void main(void) {\n"                        
      "  gl_Position = vec4(coord2d, 0.0, 1.0);\n"
      "}";

  fputs("string of shaders\n", stderr);
  glShaderSource(vs, 1, &vs_source, NULL);
  fputs("shaders selected\n", stderr);
  glCompileShader(vs);
  fputs("shaders compiled\n", stderr);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
  if (compile_ok == GL_FALSE)
  {
    GLchar* strInfoLog = new GLchar[compile_ok + 1];
    int loglen;
    char logbuffer[1000];
    glGetShaderInfoLog(vs, sizeof(logbuffer), &loglen, logbuffer);
    fprintf(stderr, "OpenGL Shader Compile Error at :\n%.*s", loglen, logbuffer);
    fprintf(stderr, "Error in vertex shader\n");
    delete[] strInfoLog;
    glDeleteShader(vs);
    return 0;
  }
  fputs("shaderiv\n", stderr);

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  const char *fs_source =
    "#version 130           \n"
    "void main(void) {        "
    "  gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);"
    "}";
  glShaderSource(fs, 1, &fs_source, NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
  if (!compile_ok) {
    fprintf(stderr, "Error in fragment shader\n");
    glDeleteShader(fs);
    return 0;
  }

  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);

  /*each vertex has many attributes, attribute for position is location = 0 in this case*/
  glBindAttribLocation(program, 0, "vertex_Position");

  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    fprintf(stderr, "glLinkProgram:");
    glDetachShader(program, vs);
    glDetachShader(program, fs);
    return 0;
  }

  const char* attribute_name = "coord2d";
  attribute_coord2d = glGetAttribLocation(program, attribute_name);
  if (attribute_coord2d == -1) {
    fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    return 0;
  }

  /*since we've attached shader to program, we can detach and delete!*/
  glDetachShader(program, vs);
  glDeleteShader(vs);
  glDetachShader(program, fs);
  glDeleteShader(fs);
  
  return 1;
}
 
void onDisplay()
{
  /* Clear the background as white */
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  #ifdef DEBUG
  fputs("Cleared buffer\n", stderr);
  #endif
 
  glUseProgram(program);

  #ifdef DEBUG
  fputs("Used program\n", stderr);
  #endif

  glEnableVertexAttribArray(attribute_coord2d);
  GLfloat triangle_vertices[] = {
     0.0,  0.8,
    -0.8, -0.8,
     0.8, -0.8,
  };

  #ifdef DEBUG
  fputs("Vertices described\n", stderr);
  #endif

  /* Describe our vertices array to OpenGL (it can't guess its format automatically) */
  glVertexAttribPointer(
    attribute_coord2d, // attribute
    2,                 // number of elements per vertex, here (x,y)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    0,                 // no extra data between each position
    triangle_vertices  // pointer to the C array
  );
  //This part binds attribute_coord2d with data from triangle_vertices[]
  
  #ifdef DEBUG
  fputs("Vertex types", stderr);
  #endif

  /* Push each element in buffer_vertices to the vertex shader */
  glDrawArrays(GL_TRIANGLES, 0, 3);

  #ifdef DEBUG
  fputs("Drawn array", stderr);
  #endif

  glDisableVertexAttribArray(attribute_coord2d);

}
 
int main(int argc, char* argv[])
{
  //Set error callback before init glfw to make sure errors can be reported if init fails.
  fputs("Start\n", stderr); 
  glfwSetErrorCallback(error_callback);

  if (!glfwInit()){
    exit(EXIT_FAILURE);
  }

  fputs("glfwInit\n", stderr); 
  GLFWwindow* window = glfwCreateWindow(640, 480, "Standard GLFW3 Window", NULL, NULL); 
  //To make fullscreen, place 'glfwGetPrimaryMonitor() in fourth param'
  //If window init failed, terminate, exit
  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  fputs("Window created\n", stderr); 

  //Make current window the current context for OpenGL to work on
  glfwMakeContextCurrent(window);
  fputs("MakeContextCurrent\n", stderr);

  //Key callback set
  glfwSetKeyCallback(window, key_callback);
  fputs("SetKeyCallback\n", stderr);

  if (!init_resources()){
    fputs("Failed to init resources", stderr);
    exit(EXIT_FAILURE);
  }

  #ifdef DEBUG
  fputs("init_resources already", stderr);
  #endif 

   while(!glfwWindowShouldClose(window))
    {
    //Keep running
    //Get framebuffer's dimensions and call glViewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    int ratio = width / (float) height;

    glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // Choose color for clearing background (RGBA)
    glClear(GL_COLOR_BUFFER_BIT); //Clear background with color chosen  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations  
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /*look at OpenGL transformation pipeline last command() is the first transformation. i.e. modelview -> projection -> .. -> viewport */
    onDisplay();

    //After rendering, we swap buffers to display rendered image
    glfwSwapBuffers(window);

    //Process events received and return immediately, renders continually
    glfwPollEvents();
   }
 
  /* If the program exits in the usual way,
  free resources and exit with a success */
    glfwDestroyWindow(window);
    glfwTerminate();
  return EXIT_SUCCESS;
}