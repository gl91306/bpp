//bpp.cpp: The starting point of Blender++.
#define GLFW_DLL
#include "include/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "include/bpp/bpp.hpp"

int main() {
  glfwInit(); //GLFW: Initialize and configure
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
  #ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  bpp::windows::start_window = glfwCreateWindow(800, 600, "Blender++", NULL, NULL); //GLFW window creation
  if (bpp::windows::start_window == NULL) {
    std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Failed to create GLFW window. Please make sure your graphics card supports OpenGL 4.6, or run the executable with the --renderer-cpu parameter." << std::endl;
    glfwTerminate();
    return 1;
  }
  
  glfwMakeContextCurrent(bpp::windows::start_window);
  glfwSetFramebufferSizeCallback(bpp::windows::start_window, bpp::functions::framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { //GLAD: Load all OpenGL function pointers
    std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Failed to initialize GLAD. Try running this application on a different computer." << std::endl;
    return 2;
  }

  //Print information about detected hardware
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Found OpenGL version " << std::string((char *)glGetString(GL_VERSION)) << std::endl;
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Found OpenGL vendor " << std::string((char *)glGetString(GL_VENDOR)) << std::endl;
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Found OpenGL renderer " << std::string((char *)glGetString(GL_RENDERER)) << std::endl;
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Found GLSL version " << std::string((char *)glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;


  //Render loop
  while (!glfwWindowShouldClose(bpp::windows::start_window)) {
    bpp::functions::process_input(bpp::windows::start_window); //Process input

    //Render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(bpp::windows::start_window); //Swap buffers
    glfwPollEvents(); //Poll I/O events (keys pressed/released, mouse moved etc.)
  }

  //Terminate.
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Terminating GLFW." << std::endl;
  glfwTerminate();
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] GLFW has been gracefully terminated. Exiting..." << std::endl;
  return 0;
}