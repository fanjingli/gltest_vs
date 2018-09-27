#pragma once

#ifndef WINDOWSVIEW_H
#define WINDOWSVIEW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowsView
{
public:
	WindowsView();
	~WindowsView();

	bool initilizeWindows();
	GLFWwindow* getWindowsPtr();
	void destoryWindows();
private:
	GLFWwindow* window;
};

#endif