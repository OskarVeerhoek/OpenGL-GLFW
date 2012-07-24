/**#include "error.hpp"
#include <iostream>
#include <GL/glew.h>

namespace tcu
{
	namespace error
	{
		void CheckErrors(bool print_if_no_error = true, std::string prefix_string = "")
		{
			const GLenum err = glGetError();
			if (GL_NO_ERROR == err)
				if (print_if_no_error)
					std::cout << prefix_string << "No Error" << std::endl;
				else if (GL_INVALID_ENUM == err)
					std::cout << prefix_string << "Invalid Enum" << std::endl;
				else if (GL_INVALID_VALUE == err)
					std::cout << prefix_string << "Invalid Value" << std::endl;
				else if (GL_INVALID_OPERATION == err)
					std::cout << prefix_string << "Invalid Operation" << std::endl;
				else if (GL_STACK_OVERFLOW == err)
					std::cout << prefix_string << "Stack Overflow" << std::endl;
				else if (GL_STACK_UNDERFLOW == err)
					std::cout << prefix_string << "Stack Underflow" << std::endl;
				else if (GL_OUT_OF_MEMORY == err)
					std::cout << prefix_string << "Out Of Memory" << std::endl;
				else if (GL_TABLE_TOO_LARGE == err)
					std::cout << prefix_string << "Table Too Large" << std::endl;
		}
	}
}**/