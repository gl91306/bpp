//bpp.cpp: The source code for Blender++.
#define GLFW_DLL

#include "include/glad.h"
#include <GLFW/glfw3.h>

#include <boost/program_options.hpp>

#include <iostream>
#include <iterator>
#include <string_view>
#include <string>
#include <cstring>

namespace bpp {
  namespace variables {
    short int active_renderer;
  }

  namespace functions {
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void process_input(GLFWwindow *window);
  }

  namespace windows {
    GLFWwindow *start_window;
  }

  void quit(int retval);
}

int main(int argc, char *argv[]) {
  try {
    boost::program_options::options_description bpp_options_description("Test123");
    bpp_options_description.add_options()
      ("help", "Print help message");

    boost::program_options::variables_map bpp_variables_map;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, bpp_options_description), bpp_variables_map);
    boost::program_options::notify(bpp_variables_map);

    if (bpp_variables_map.count("help")) {
      std::cout << bpp_options_description << std::endl;
      bpp::quit(0);
    }
  }

  catch(std::exception &e) {
    std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Error:  " << e.what() << std::endl;
    bpp::quit(1);
  }

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

void bpp::quit(int retval) {
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Blender++ terminated. " << std::endl;
  exit(0);
}

void bpp::functions::process_input(GLFWwindow *window) { //Query GLFW whether relevant keys are pressed/released this frame and react accordingly
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true); //Escape obviously means "Quit".
  }
}

void bpp::functions::framebuffer_size_callback(GLFWwindow *window, int width, int height) { //This gets called whenever the window gets resized
  glViewport(0, 0, width, height); //Make sure the viewport is the same size as the window.
}