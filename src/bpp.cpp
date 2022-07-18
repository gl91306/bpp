//bpp.c: The starting point of Blender++.
#define GLFW_DLL
#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "bpp/bpp.hpp"

int main(int argc, char **argv[]) {
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
    return 1;
  }

  glfwMakeContextCurrent(start_window); //So we can get the OpenGL version
  glfwSetFramebufferSizeCallback(start_window, framebuffer_size_callback);
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Found OpenGL version " << glVersion << std::endl;

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Failed to initialize GLAD. Try running this application on a different computer." << std::endl;
    return -1;
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
}