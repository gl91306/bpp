//bpp.hpp: The list of things that Blender++ uses
#define GLFW_DLL
#include "../glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace bpp {
  namespace functions {
    void check_params();
    inline void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    inline void process_input(GLFWwindow *window);
  }

  namespace windows {
    extern GLFWwindow *start_window;
  }
}