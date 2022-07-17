//bpp.c: The starting point of Blender++.
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdio.h>

int main(int arc, char** argv) {
  if (glfwVulkanSupported())
  {
    printf("Vulkan is available.\n");
  }

  if (!glfwVulkanSupported())
  {
    printf("Vulkan is not available. Please try running the application on a newer computer.\n");
  }

  printf("\nBlender++ returned 0.\n");
  return 0;
}