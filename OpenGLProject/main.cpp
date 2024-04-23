
#include <glad/glad.h>		// GPU driver's specific helper
#include <GLFW/glfw3.h>

#include <cstdio>
#include <thread>
#include <iostream>

#include <Windows.h>
#include "Example1.h"


const char* vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\0";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

int main()
{

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Hello World!", NULL, NULL);
	if (!window)
	{
		printf("Failed to create glfw window.\n");
		glfwTerminate();
		return 0;
	}
	glfwMakeContextCurrent(window);

	//// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return 0;
	}

	// let's create a vertex shader object (referenced by an ID)
	// ----------------------------------
	unsigned int vertexShader = glad_glCreateShader(GL_VERTEX_SHADER);
	// attach the shader source code to the shader object ref and compile the shader
	glad_glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glad_glCompileShader(vertexShader);

	// checking for vertex shader compile is successful or not
	int success{};
	char infoLog[512];
	glad_glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glad_glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);	// Parse the error log into our logBuffer
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	// let's create a fragment shader object (again, referenced by an ID)
	// ---------------------------------
	unsigned int fragmentShader = glad_glCreateShader(GL_FRAGMENT_SHADER);
	glad_glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glad_glCompileShader(fragmentShader);

	// checking for fragment shader compile is successful or not
	// Note: reuse success and infolog variables above
	glad_glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glad_glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}


	// Finally, create a shader program that will link multiple shaders combined!
	// --------------------------------
	unsigned int shaderProgram = glad_glCreateProgram();
	glad_glAttachShader(shaderProgram, vertexShader);
	glad_glAttachShader(shaderProgram, fragmentShader);
	glad_glLinkProgram(shaderProgram);

	// checking if attach and linking is successful or not
	glad_glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glad_glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	// Every shader and rendering call after glUseProgram will now use this program object (and
	// thus the shaders
	// ----------------
	glad_glUseProgram(shaderProgram);

	// Delete the shader objects since we've linked into the program object
	glad_glDeleteShader(vertexShader);
	glad_glDeleteShader(fragmentShader);

}