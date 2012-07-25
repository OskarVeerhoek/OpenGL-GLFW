#ifndef OPENGL_GLFW_TCU_ERROR_H_
#define OPENGL_GLFW_TCU_ERROR_H_
#include <string>
#include <iostream>
#include <fstream>

namespace error
{
	std::ofstream g_error_file;
	void Initialize()
	{
		g_error_file.open("debug.txt");
	}
	void Destroy()
	{
		g_error_file.close();
	}
	void CheckErrors(bool print_if_no_error = true, std::string prefix_string = "")
	{
		const GLenum err = glGetError();
		if (GL_NO_ERROR == err)
		{
			if (print_if_no_error)
			{
				g_error_file << prefix_string << "No Error" << std::endl;
			}
		}
		else if (GL_INVALID_ENUM == err)
		{
			g_error_file << prefix_string << "Invalid Enum" << std::endl;
		}
		else if (GL_INVALID_VALUE == err)
		{
			g_error_file << prefix_string << "Invalid Value" << std::endl;
		}
		else if (GL_INVALID_OPERATION == err)
		{
			g_error_file << prefix_string << "Invalid Operation" << std::endl;
		}
		else if (GL_STACK_OVERFLOW == err)
		{
			g_error_file << prefix_string << "Stack Overflow" << std::endl;
		}
		else if (GL_STACK_UNDERFLOW == err)
		{
			g_error_file << prefix_string << "Stack Underflow" << std::endl;
		}
		else if (GL_OUT_OF_MEMORY == err)
		{
			g_error_file << prefix_string << "Out Of Memory" << std::endl;
		}
		else if (GL_TABLE_TOO_LARGE == err)
		{
			g_error_file << prefix_string << "Table Too Large" << std::endl;
		}
		else
		{
			g_error_file << "Unknown Error" << std::endl;
		}
	}
}

#endif