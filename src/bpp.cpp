//bpp.c: The starting point of Blender++.
#define GLFW_DLL
#include "include/glad.h"
#include <GLFW/glfw3.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
//#include "include/bpp/bpp.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
  //GLFW: Initialize and configure
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
  #ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  //GLFW window creation
  GLFWwindow *window = glfwCreateWindow(800, 600, "Blender++", NULL, NULL);
  if (window == NULL) {
    std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Failed to create GLFW window. Please make sure your graphics card supports OpenGL 4.6, or run the executable with the --renderer-cpu parameter." << std::endl;
    glfwTerminate();
    return 1;
  }
  
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  //GLAD: Load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Failed to initialize GLAD. Try running this application on a different computer." << std::endl;
    return 2;
  }

  //Print information about detected hardware
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Found OpenGL version " << std::string((char *)glGetString(GL_VERSION)) << std::endl;
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Found OpenGL vendor " << std::string((char *)glGetString(GL_VENDOR)) << std::endl;
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Found OpenGL renderer " << std::string((char *)glGetString(GL_RENDERER)) << std::endl;
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Found GLSL version " << std::string((char *)glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;


  //Render loop
  while (!glfwWindowShouldClose(window)) {
    //Input
    processInput(window);

    //Render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //GLFW: Swap buffers and poll I/O events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  //Terminate.
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Terminating GLFW." << std::endl;
  glfwTerminate();
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] GLFW has been gracefully terminated. Exiting..." << std::endl;
  return 0;
}

//Query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

//This gets called whenever the window gets resized
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    //Make sure the viewport is the same size as the window.
    glViewport(0, 0, width, height);
}

/*int main(int argc, char **argv) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
  #ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  start_window = glfwCreateWindow(800, 600, "Blender++", NULL, NULL);
  if (start_window == NULL)
  {
    std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Failed to create GLFW window. Please make sure your graphics card supports OpenGL 4.6." << std::endl;
    glfwTerminate();
    return 9;
  }

  glfwMakeContextCurrent(start_window); //So we can get the OpenGL version
  glfwSetFramebufferSizeCallback(start_window, framebuffer_size_callback);
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Found OpenGL version " << glVersion << std::endl;

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Failed to initialize GLAD. Try running this application on a different computer." << std::endl;
    return 8;
  }    

  while (!glfwWindowShouldClose(start_window)) //Render loop
  {
    //Process input
    process_input(start_window);

    //Render the stuff to the screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //GLFW: Swap buffers and poll I/O events
    glfwSwapBuffers(start_window);
    glfwPollEvents();
  }

  //Terminate GLFW
  glfwTerminate();

  std::cout << std::endl << "Blender++ returned 0." << std::endl;
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Called framebuffer size callback" << std::endl;
  glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}*/