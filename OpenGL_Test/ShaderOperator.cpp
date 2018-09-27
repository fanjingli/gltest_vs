

#include "ShaderOperator.h"


ShaderOperator::ShaderOperator()
{
}
ShaderOperator::~ShaderOperator()
{
}

void ShaderOperator::dealShader(const char* vertexShaderSource, const char* fragShaderSource)
{
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int success;
	char logInfo[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, logInfo);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << logInfo << std::endl;
	}

	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSource, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragShader, 512, NULL, logInfo);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << logInfo << std::endl;
	}
		
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragShader);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, logInfo);
	}
}

unsigned int ShaderOperator::getProgramID()
{
	return programID;
}

