//bpp.cpp: The source code for Blender++.
#define GLFW_DLL

#include "include/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string_view>
#include <string>
#include <cstring>

namespace bpp {
  namespace variables {
    short int active_renderer;
  }

  namespace functions {
    void check_params(int pargc, char **pargv);
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void process_input(GLFWwindow *window);
  }

  namespace windows {
    GLFWwindow *start_window;
  }
}


int main(int argc, char *argv[]) {
  //bpp::functions::check_params(argc, argv);

  std::string s = argv[1];
  //int i = strcmp(s, "-h");
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] h " << s << std::endl;

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

void bpp::functions::process_input(GLFWwindow *window) { //Query GLFW whether relevant keys are pressed/released this frame and react accordingly
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true); //Escape obviously means "Quit".
  }
}

void bpp::functions::framebuffer_size_callback(GLFWwindow *window, int width, int height) { //This gets called whenever the window gets resized
    glViewport(0, 0, width, height); //Make sure the viewport is the same size as the window.
}

void bpp::functions::check_params(int pargc, char **pargv) {
  //using namespace std::literals;
  //std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] pargv: " << pargv[1] << std::endl;

  if (pargc > 1) {
    if (strcmp(pargv[2], "-h") || strcmp(pargv[2], "--help") != 0) {
      std::cout << "Help page for Blender++ v0.0.1.0" << std::endl;
      std::cout << "List of commands: " << std::endl;
      std::cout << "-h, --help            Displays this help page." << std::endl;
      std::cout << "--renderer-X          Choose the rendering engine. X can be either 'gl1-0', " << std::endl;
    }

    /*if (pargv[1] == "--help") {
      std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] yeet " << std::endl;
    }*/
  }

  /*using namespace std::literals;

  if (pargv[2] == "-h"sv || pargv[2] == "--help"sv) {
    std::cout << "Help page for Blender++ v0.0.1.0" << std::endl;
    std::cout << "List of commands: " << std::endl;
    std::cout << "-h, --help            Displays this help page." << std::endl;
    std::cout << "--renderer-X          Choose the rendering engine. X can be either 'gl1-0', " << std::endl;
  }*/
}