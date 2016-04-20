/**
*   This is the testing file libraries, dependencies and makefiles
**/
#define GLEW_STATIC

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main()
{
    if(!glfwInit())
    {
        fprintf(stderr, "GLFW Failed to initailze\n");
        exit(EXIT_FAILURE);
    }

    GLFWwindow* context = glfwCreateWindow(800,600, "Title", NULL, NULL);
    if(!context)
    {
        fprintf(stderr, "Context creation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Hello World!\n");

    while(!glfwWindowShouldClose(context))
    {
        glfwPollEvents();
    }

    if(!glewInit())
    {
        fprintf(stderr, "GLEW Failed to initilize\n");
        exit(EXIT_FAILURE);
    }

    glfwTerminate();

    return 0;
}
