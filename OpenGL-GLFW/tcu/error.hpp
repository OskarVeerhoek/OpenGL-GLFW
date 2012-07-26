#ifndef OPENGL_GLFW_TCU_ERROR_H_
#define OPENGL_GLFW_TCU_ERROR_H_
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

namespace error
{
	class ErrorHandler
	{
	public:
		ErrorHandler() 
		{

		}
		~ErrorHandler()
		{

		}
		void Create()
		{
			m_stream.open("debug.txt"); 
		}
		void Destroy()
		{
			m_stream.close();
		}
		void Check(bool print_if_no_error, std::string prefix)
		{
			const GLenum err = glGetError();
			if (GL_NO_ERROR == err)
			{
				if (print_if_no_error)
				{
					m_ss << prefix << "No Error";
					m_errors.push_back(m_ss.str());
					m_ss.str(std::string());
					m_stream << prefix << "No Error" << std::endl;
				}
			}
			else if (GL_INVALID_ENUM == err)
			{
				m_ss << prefix << "Invalid Enum";
				m_errors.push_back(m_ss.str());
				m_ss.str(std::string());
				m_stream << prefix << "Invalid Enum" << std::endl;
			}
			else if (GL_INVALID_VALUE == err)
			{
				m_ss << prefix << "Invalid Value";
				m_errors.push_back(m_ss.str());
				m_ss.str(std::string());
				m_stream << prefix << "Invalid Value" << std::endl;
			}
			else if (GL_INVALID_OPERATION == err)
			{
				m_ss << prefix << "Invalid Operation";
				m_errors.push_back(m_ss.str());
				m_ss.str(std::string());
				m_stream << prefix << "Invalid Operation" << std::endl;
			}
			else if (GL_STACK_OVERFLOW == err)
			{
				m_ss << prefix << "Stack Overflow";
				m_errors.push_back(m_ss.str());
				m_ss.str(std::string());
				m_stream << prefix << "Stack Overflow" << std::endl;
			}

			else if (GL_STACK_UNDERFLOW == err)
			{
				m_ss << prefix << "Stack Underflow";
				m_errors.push_back(m_ss.str());
				m_ss.str(std::string());
				m_stream << prefix << "Stack Underflow" << std::endl;
			}
			else if (GL_OUT_OF_MEMORY == err)
			{
				m_ss << prefix << "Out Of Memory";
				m_errors.push_back(m_ss.str());
				m_ss.str(std::string());
				m_stream << prefix << "Out Of Memory" << std::endl;
			}
			else if (GL_TABLE_TOO_LARGE == err)
			{
				m_ss << prefix << "Table Too Large";
				m_errors.push_back(m_ss.str());
				m_ss.str(std::string());
				m_stream << prefix << "Table Too Large" << std::endl;
			}
			else
			{
				m_ss << prefix << "Unkown Error";
				m_errors.push_back(m_ss.str());
				m_ss.str(std::string());
				m_stream << "Unknown Error" << std::endl;
			}
		}
		std::vector<std::string> GetErrors()
		{
			return m_errors;
		}
	private:
		// The file output stream that will be used to write the errors to.
		std::ofstream m_stream;
		// A vector containing all the errors.
		std::vector<std::string> m_errors;
		std::stringstream m_ss;
	};
}
#endif