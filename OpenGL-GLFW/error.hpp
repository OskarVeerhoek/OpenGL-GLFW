#ifndef OPENGL_GLFW_TCU_ERROR_H_
#define OPENGL_GLFW_TCU_ERROR_H_

#include "standard.h"

namespace error
{
	class ErrorHandler
	{
	public:
		ErrorHandler();
		~ErrorHandler();
		void Create();
		void Destroy();
		void Check(bool print_if_no_error, std::string prefix);
		std::vector<std::string> GetErrors();
	private:
		// The file output stream that will be used to write the errors to.
		std::ofstream m_stream;
		// A vector containing all the errors.
		std::vector<std::string> m_errors;
		std::stringstream m_ss;
	};
}
#endif