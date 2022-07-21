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
    void check_params(int pargc, char **pargv);
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void process_input(GLFWwindow *window);
  }

  namespace windows {
    GLFWwindow *start_window;
  }

  void quit(int retval);
}

int main(int argc, char *argv[]) {
  bpp::functions::check_params(argc, argv);

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
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Blender++ terminated. " << std::endl;
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

void bpp::functions::check_params(int pargc, char **pargv) {
  try {
    boost::program_options::options_description bpp_options_description("Blender++ Help");
    bpp_options_description.add_options()
      ("help", "Print help message")
      ("errorhelp", "What an error means (0 for success, 1 for bla bla bla etc)")
      ("errorhelp-{code}", "Displays the description for a specific error code");

    boost::program_options::variables_map bpp_variables_map;
    boost::program_options::store(boost::program_options::parse_command_line(pargc, pargv, bpp_options_description), bpp_variables_map);
    boost::program_options::notify(bpp_variables_map);

    if (bpp_variables_map.count("help")) {
      std::cout << bpp_options_description << std::endl;
      bpp::quit(0);
    }

    if (bpp_variables_map.count("errorhelp")) {
      std::cout << "There are different types of errors in Blender++. And it is generally good computer programming practice to assign an ID or code to every error. The types of errors in Blender++ are listed below." << std::endl;
      std::cout << "0: Success. (BTW this is the reason why early versions of Windows used to say \"Task failed successfully.\" until someone realized that meant to opposite of what it was supposed to mean." << std::endl;
      std::cout << "1: Failed to create GLFW window. This usually means you either need a new computer with a better GPU or you should start the program with the '--renderer-cpu' argument." << std::endl;
      std::cout << "2: Failed to initialize GLAD. This problem has the same answer as error 1." << std::endl;
      std::cout << "3: Couldn't recognise an argument. Please make sure you run Blender++ with the correct arguments, run it with '--help' to learn more." << std::endl;
      std::cout << std::endl << "If you get any other kind of error, please try reinstalling Blender++. Or try running it on a different computer. You can also try running the application with '--errorhelp-{your error code here}'. If none of these options work, you can reach out to me at HackerDaGreat57@gmail.com." << std::endl;
      bpp::quit(0);
    }

    if (bpp_variables_map.count("errorhelp-0")) {
      std::cout << "0: Success. (BTW this is the reason why early versions of Windows used to say \"Task failed successfully.\" until someone realized that meant to opposite of what it was supposed to mean." << std::endl;
      bpp::quit(0);
    }
  }

  catch(std::exception &e) {
    std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Error: " << e.what() << std::endl;
    bpp::quit(3);
  }
}