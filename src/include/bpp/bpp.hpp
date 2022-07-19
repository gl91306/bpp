//bpp.hpp: The list of things that Blender++ uses
#define GLFW_DLL
#include "../glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

std::string glVersion = std::string((char *)glGetString(GL_VERSION));
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);
GLFWwindow *start_window;

/*namespace bpp {
  namespace variables {
    std::string glVersion = std::string((char *)glGetString(GL_VERSION));
  }

  namespace functions {
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void process_input(GLFWwindow *window);
  }

  namespace windows {
    GLFWwindow *start_window;
  }
}*/