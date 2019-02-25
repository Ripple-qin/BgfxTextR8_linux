#include <iostream>
#include <stdio.h>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <GL/glew.h>
#include <omp.h>
#include <GLFW/glfw3.h>
#include "ExampleFBO.h"
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#	define GLFW_EXPOSE_NATIVE_X11
#	define GLFW_EXPOSE_NATIVE_GLX
# include <GLFW/glfw3.h>
# include <GLFW/glfw3native.h>
#endif

ExampleFBO *exampleCubes;

int main() {
    exampleCubes = new ExampleFBO();

    std::cout << "Hello, World!" << std::endl;
    int fw_code = -1;
    fw_code =  glfwInit();

    if (!fw_code)
    {
        fprintf(stderr, "Failed to initialize GLFW,error code=%d\n",fw_code);
        getchar();
        return 1;
    }

    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_ALPHA_BITS, GLFW_DONT_CARE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE); // windows unvisible

    // Open a window and create its OpenGL context
    int windowWidth = 512;
    int windowHeight = 768;

    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "Tutorial 14 - Render To Texture", nullptr, nullptr);
    if (window == nullptr)
    {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = static_cast<GLboolean>(true); // Needed for core profile
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        return 1;
    }

    exampleCubes->init(window, 512,768);
    exampleCubes->update();

    std::cout << "Hello, World! 1111" << std::endl;

    return 0;
}




