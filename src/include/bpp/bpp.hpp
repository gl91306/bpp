//bpp.hpp: The list of things that Blender++ uses
#define GLFW_DLL
#include "../glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#define VER_STRING	"0.0.0.9"
#define VER_MAJOR	0
#define VER_MINOR	0
#define VER_RELEASE	0
#define VER_BUILD	9
#define COMPANY_NAME	"HackerDaGreat57 Software"
#define FILE_VERSION	"0.0.0.9"
#define FILE_DESCRIPTION	"NuklearToolz - Windows x64"
#define INTERNAL_NAME	"nktlz.exe"
#define LEGAL_COPYRIGHT	"(c) HackerDaGreat57 Software 2022. All rights reserved."
#define LEGAL_TRADEMARKS	"(Not trademarked)"
#define ORIGINAL_FILENAME	"nktlz.exe"
#define PRODUCT_NAME	"NuklearToolz"
#define PRODUCT_VERSION	"0.0.0.9"

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