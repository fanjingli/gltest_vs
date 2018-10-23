

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "ShaderOperator.h"
#include "WindowsView.h"
#include "stb_image.h"
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <glm\glm\gtc\type_ptr.hpp>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	WindowsView windowsview;
	if (!windowsview.initilizeWindows()) {
		return -1;
	}
	
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(windowsview.getWindowsPtr(), framebuffer_size_callback);
	
	ShaderOperator shaderOperator;
	shaderOperator.dealShader(vertexShaderSource, fragShaderSource);
	
	float firstVertices[] = {
		//     ---- 位置 ----       - 纹理坐标 -
		0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // 右上
		0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // 左下

		0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // 右上
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // 左上
	};


	//生成纹理
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	int imgWidth, imgHeight, imgChannels;
	unsigned char *imgData = stbi_load("container.jpg", &imgWidth, &imgHeight, &imgChannels, 0);
	if (nullptr != imgData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(imgData);

	unsigned int VBO[2], VAO;

	glGenBuffers(2, VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstVertices), firstVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	while (!glfwWindowShouldClose(windowsview.getWindowsPtr()))
	{
		processInput(windowsview.getWindowsPtr());

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glUseProgram(shaderOperator.getProgramID());

		glm::mat4 model;
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 view;
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -90.0f));
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 1.3f, 0.1f, 100.0f);

		unsigned int modelMat = glGetUniformLocation(shaderOperator.getProgramID(), "model");
		glUniformMatrix4fv(modelMat,1,GL_FALSE, glm::value_ptr(model));
		unsigned int viewMat = glGetUniformLocation(shaderOperator.getProgramID(), "view");
		glUniformMatrix4fv(viewMat, 1, GL_FALSE, &view[0][0]);
		unsigned int projMat = glGetUniformLocation(shaderOperator.getProgramID(), "project");
		glUniformMatrix4fv(projMat, 1, GL_FALSE, glm::value_ptr(projection));

		//glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(windowsview.getWindowsPtr());
		glfwPollEvents();
	}
	
	glDeleteBuffers(2, VBO);

	windowsview.destoryWindows();
	return 0;
}
