
#include "WindowsView.h"
#include <iostream>

WindowsView::WindowsView()
	:window(nullptr)
{

}

WindowsView::~WindowsView()
{
	glfwTerminate();
}
void WindowsView::destoryWindows()
{
	glfwTerminate();
}

bool WindowsView::initilizeWindows()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
}

GLFWwindow* WindowsView::getWindowsPtr()
{
	return window;
}