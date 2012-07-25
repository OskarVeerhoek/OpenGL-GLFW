#ifndef OPENGL_GLFW_TCU_SHADER_H_
#define OPENGL_GLFW_TCU_SHADER_H_
#include <string>
typedef unsigned int GLuint;
typedef unsigned int GLenum;
namespace tcu
{
	namespace shader
	{
		class ShaderProgram
		{
		public:
			ShaderProgram();
			~ShaderProgram();
			void CreateFromFiles(const std::string vertex_shader_file_name, const std::string fragment_shader_file_name);
			void CreateFromStrings(const std::string vertex_shader_source, const std::string fragment_shader_source);
			GLuint GetOpenGLID();
			void Destroy();
		private:
			GLuint m_opengl_shader_program;
			GLuint m_opengl_vertex_shader;
			GLuint m_opengl_fragment_shader;
		};
	}
}
#endif