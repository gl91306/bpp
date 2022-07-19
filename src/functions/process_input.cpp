//process_input.cpp: The function which lets Blender++ receive input
#define GLFW_DLL
#include "../include/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/bpp/bpp.hpp"

void bpp::functions::process_input(GLFWwindow *window) { //Query GLFW whether relevant keys are pressed/released this frame and react accordingly
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true); //Escape obviously means "Quit".
  }
}