//framebuffer_size_callback.cpp: Resize the viewport when the window gets resized.
#define GLFW_DLL
#include "include/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "include/bpp/bpp.hpp"

void bpp::functions::framebuffer_size_callback(GLFWwindow *window, int width, int height) { //This gets called whenever the window gets resized
    glViewport(0, 0, width, height); //Make sure the viewport is the same size as the window.
}