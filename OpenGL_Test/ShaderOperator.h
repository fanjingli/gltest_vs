


#ifndef SHADER_H
#define SHADER_H


#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;


class ShaderOperator
{
	
public:
	ShaderOperator();
	~ShaderOperator();
	void dealShader(const char* vertexShaderSource, const char* fragShaderSource);
	unsigned int getProgramID();
private:
	unsigned int programID;
};





#endif