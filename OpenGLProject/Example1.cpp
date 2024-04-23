
#include <glad/glad.h>		// GPU driver's specific helper
#include <GLFW/glfw3.h>		// Window creation helper

#include <cstdio>
#include <thread>


static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glad_glViewport(0, 0, 800, 600);
}

static void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void RunExample1()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Hello World!", NULL, NULL);
	if (!window)
	{
		printf("Failed to create glfw window.\n");
		glfwTerminate();
		return ;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);	// Register callback when window is resized.


	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return ;
	}


#define glClearColorRed		glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
#define glClearColorGreen	glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
#define glClearColorBlue	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);


	uint64_t counter = 0;

	while (!glfwWindowShouldClose(window))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		// Screen clearing
		// ------------
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);		// Specify the color we want to apply when clear the screen;
		switch (counter % 3)
		{
		case 0:
			glClearColorRed;
			break;
		case 1:
			glClearColorGreen;
			break;
		case 2:
			glClearColorBlue;
			break;
		}
		glClear(GL_COLOR_BUFFER_BIT);


		// input
		// --------
		process_input(window);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	   // -------------------------------------------------------------------------------
		glfwSwapBuffers(window);			// Swappping color buffer to render the screen.
		glfwPollEvents();

		++counter;
	}

	// Clean up
	glfwTerminate();
}