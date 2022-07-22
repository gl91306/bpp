//bpp.cpp: The source code for Blender++.
#define GLFW_DLL

#include "include/glad.h"
#include <GLFW/glfw3.h>

#include <boost/program_options.hpp>

#include <ncursesw/curses.h>

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
    int check_params(int pargc, char **pargv);
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void process_input(GLFWwindow *window);
  }

  namespace windows {
    GLFWwindow *start_window;
  }

  void start_standard(void);
  void start_support(void);
  void quit(short int retval);
}

int main(int argc, char *argv[]) {
  int running_mode = bpp::functions::check_params(argc, argv);

  switch (running_mode) {
    case 0:
      bpp::start_standard();
      break;
    case 1:
      bpp::start_support();
      break;
  }

  bpp::quit(0);
}

void bpp::start_standard(void) {
  glfwInit(); //GLFW: Initialize and configure
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
  #ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  bpp::windows::start_window = glfwCreateWindow(800, 600, "Blender++", NULL, NULL); //GLFW window creation
  if (bpp::windows::start_window == NULL) {
    glfwTerminate();
    bpp::quit(1);
  }
  
  glfwMakeContextCurrent(bpp::windows::start_window);
  glfwSetFramebufferSizeCallback(bpp::windows::start_window, bpp::functions::framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { //GLAD: Load all OpenGL function pointers
    bpp::quit(2);
  }

  //Print information about detected hardware
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Found OpenGL version " << std::string((char *)glGetString(GL_VERSION)) << std::endl;
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Found GPU vendor " << std::string((char *)glGetString(GL_VENDOR)) << std::endl;
  std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Rendering on GPU " << std::string((char *)glGetString(GL_RENDERER)) << std::endl;
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
  bpp::quit(0);
}

void bpp::quit(short int retval) {
  switch (retval) {
    case 0:
      std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Blender++ terminated, returned error code 0 (nothing went wrong, successful exit). " << std::endl;
      break;
    case 1:
      std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Blender++ terminated, returned error code 1 (failed to create GLFW window. Run Blender++ with --errorhelp-1 for possible fixes)." << std::endl;
      break;
    case 2:
      std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Blender++ terminated, returned error code 2 (failed to initialize GLAD. Run Blender++ with --errorhelp-2 for possible fixes)." << std::endl;
      break;
    case 3:
      std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Blender++ terminated, returned error code 3 (bad arguments. Run Blender++ with --errorhelp-3 for possible fixes). " << std::endl;
      break;
    default:
      std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Blender++ terminated with unknown error. " << std::endl;
      break;
  }

  exit(retval);
}

void bpp::functions::process_input(GLFWwindow *window) { //Query GLFW whether relevant keys are pressed/released this frame and react accordingly
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true); //Escape obviously means "Quit".
  }
}

void bpp::functions::framebuffer_size_callback(GLFWwindow *window, int width, int height) { //This gets called whenever the window gets resized
  glViewport(0, 0, width, height); //Make sure the viewport is the same size as the window.
}

int bpp::functions::check_params(int pargc, char **pargv) {
  short int cp_retval;
  short int errorcode;

  try {
    boost::program_options::options_description options_description("Blender++ v0.0.1.0 Help");
    options_description.add_options()
      ("help", "Print help message (the thing you're reading right now)")
      ("errorhelp", "Print basic information about all error codes")
      ("errorcode", boost::program_options::value(&errorcode) , "Displays a longer description for a specific error code with possible solutions. Replace 'arg' with your error code")
      ("support", "Launches the command-line-based support manual");

    boost::program_options::variables_map variables_map;
    boost::program_options::store(boost::program_options::parse_command_line(pargc, pargv, options_description), variables_map);
    boost::program_options::notify(variables_map);

    if (variables_map.count("help")) {
      std::cout << options_description << std::endl;
      bpp::quit(0);
    }

    if (variables_map.count("errorhelp")) {
      std::cout << "There are different types of errors in Blender++. And it is generally good computer programming practice to assign an ID or code to every error. The types of errors in Blender++ are listed below. Run the application with --errorhelp {your error code here} to learn about possible solutions for your error." << std::endl;
      std::cout << "0: Success. Nothing to worry about." << std::endl;
      std::cout << "1: Failed to create GLFW window." << std::endl;
      std::cout << "2: Failed to initialize GLAD." << std::endl;
      std::cout << "3: Couldn't recognise an argument." << std::endl;
      std::cout << std::endl << "If you get any other kind of error, please try reinstalling Blender++. If none of these options work, you can reach out to me at HackerDaGreat57@gmail.com." << std::endl << std::endl;
      bpp::quit(0);
    }

    if (variables_map.count("errorcode")) {
      switch (errorcode) {
        case 0:
          std::cout << "Error 0: Success. (BTW this is the reason why early versions of Windows used to say \"Task failed successfully.\" until someone realized that meant to opposite of what it was supposed to mean." << std::endl;
          bpp::quit(0);
        case 1:
          std::cout << "Error 1: Failed to create GLFW window. This means that your graphics card (aka GPU) doesn't support OpenGL 4.6. Try rerunning Blender++ with --renderer-cpu." << std::endl;
          bpp::quit(0);
        case 2:
          std::cout << "Error 2: Failed to initialize GLAD. This means that your computer either does not have a graphics card (aka GPU) or is too old. Try running the application with --renderer-cpu." << std::endl;
          bpp::quit(0);
        case 3:
          std::cout << "Error 3: Invalid arguments. This means that one of the application's command-line settings (the things that are seperated by spaces and begin with --) are incorrect and probably have a spelling error. Check your arguments carefully and make sure that not a single letter is off. Remember, the command-line doesn't have autocorrect!" << std::endl;
          bpp::quit(0);

        default:
          std::cout << "Invalid error code. Try again with the right number this time" << std::endl;
          bpp::quit(0);
      }

      if (variables_map.count("support")) {
        return 1;
        //bpp::support::launch();
      }
    }
  }

  catch(std::exception &exception_check_params) {
    std::cout << "{Blender++ Core} [" << __FILE__ << ":" << __LINE__ << "] Error: " << exception_check_params.what() << std::endl;
    bpp::quit(3);
  }

  return 0;
}

void bpp::start_support(void) {bpp::quit(0);
  initscr();
  printw("Hello Support!");
  refresh();
  getch();
  endwin();

  bpp::quit(0);
}