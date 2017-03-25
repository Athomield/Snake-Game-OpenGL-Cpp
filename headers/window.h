#ifndef WINDOW_H
#define WINDOW_H


#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
//#include <GL/glu.h>
#include <stdio.h>
#include <string>

#include <iostream>


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>


class Window
{
// member class must start with "m"

private:
    static GLFWwindow* mWindow;
	static Window* mInstance;

private:
	Window();
	~Window();

public:
    void CreateWindow();
	static Window* GetWindow();
	static GLFWwindow* GetGLFWWindow();

};
#endif
