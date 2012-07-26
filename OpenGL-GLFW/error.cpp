#include "error.hpp"
#include "opengl.h"

namespace error
{
	ErrorHandler::ErrorHandler()
	{

	}
	ErrorHandler::~ErrorHandler()
	{

	}
	void ErrorHandler::Create()
	{
		glGetError();
		m_stream.open("debug.txt"); 
	}
	void ErrorHandler::Destroy()
	{
		m_stream.close();
	}
	void ErrorHandler::Check(bool print_if_no_error, std::string prefix)
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
		else if (GL_INVALID_FRAMEBUFFER_OPERATION == err)
		{
			m_ss << prefix << "Invalid Framebuffer Operation";
			m_errors.push_back(m_ss.str());
			m_ss.str(std::string());
			m_stream << prefix << "Invalid Framebuffer Operation" << std::endl;
		}
		else if (GL_OUT_OF_MEMORY == err)
		{
			m_ss << prefix << "Out Of Memory";
			m_errors.push_back(m_ss.str());
			m_ss.str(std::string());
			m_stream << prefix << "Out Of Memory" << std::endl;
		}
		else
		{
			m_ss << prefix << "Unkown Error";
			m_errors.push_back(m_ss.str());
			m_ss.str(std::string());
			m_stream << "Unknown Error" << std::endl;
		}
	}
	std::vector<std::string> ErrorHandler::GetErrors()
	{
		return m_errors;
	}
}