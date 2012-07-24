#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glfw.h>
#include "tcu/shader.hpp"
#include "tcu/program.hpp"

tcu::program::Program program;

int WindowCloseCallback()
{
	program.Destroy();
	return GL_TRUE;
}

int main(void)
{
	if (glfwInit() == GL_FALSE)
		glfwTerminate();
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	if (glfwOpenWindow(640, 480, 8, 8, 8, 8, 24, 8, GLFW_WINDOW) == GL_FALSE)
		glfwTerminate();
	glfwSwapInterval(1);
	GLFWvidmode desktop_video_mode;
	glfwGetDesktopMode(&desktop_video_mode);
	glfwSetWindowPos(desktop_video_mode.Width / 2 - 640/2, desktop_video_mode.Height / 2 - 480/2);
	GLenum err = glewInit();
	glGetError(); //s Reset Error Flag
	if (err != GLEW_OK)
	{
		std::cout << glewGetErrorString(err) << std::endl;
		std::cin.get();
		return EXIT_FAILURE;
	}
	glfwSetWindowCloseCallback(WindowCloseCallback);
	bool running = true;
	program.Init();
	while (running)
	{
		program.Render();
		glfwSwapBuffers();
		running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	}
	program.Destroy();
	glfwCloseWindow();
	return EXIT_SUCCESS;
}