#include "shader.hpp"
#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

namespace tcu
{
	namespace shader
	{
		const std::string LoadFileContents(const std::string filename) 
		{
			std::ifstream file;
			file.open(filename.c_str());		
			if (!file) 
				std::cerr << "File " << filename << " could not be opened."	<< std::endl;
			std::stringstream stream;
			stream << file.rdbuf();
			file.close();
			return stream.str();
		}
		const GLuint CreateShaderFromFile(const std::string file_name, const GLenum shader_type)
		{
			const std::string shader_source = LoadFileContents(file_name);
			const char *shader_source_cstr = shader_source.c_str();
			const GLuint shader = glCreateShader(shader_type);
			glShaderSource(shader, 1, &shader_source_cstr, NULL);
			glCompileShader(shader);
			GLint status;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
			if (status == GL_FALSE)
			{
				GLint infoLogLength;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
				GLchar *strInfoLog = new GLchar[infoLogLength + 1];
				glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
				fprintf(stderr, "Compile failure in shader:\n%s\n", strInfoLog);
				delete[] strInfoLog;
			}
			return shader;
		}
		const GLuint CreateShaderProgram(const GLuint vertex_shader, const GLuint fragment_shader, const GLuint geometry_shader = 0)
		{
			GLuint program = glCreateProgram();
			glAttachShader(program, vertex_shader);
			glAttachShader(program, fragment_shader);
			if (0 != geometry_shader)
				glAttachShader(program, geometry_shader);
			glLinkProgram(program);
			glValidateProgram(program);
			GLint status;
			glGetProgramiv (program, GL_LINK_STATUS, &status);
			if (status == GL_FALSE)
			{
				GLint infoLogLength;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

				GLchar *strInfoLog = new GLchar[infoLogLength + 1];
				glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
				fprintf(stderr, "Linker failure: %s\n", strInfoLog);
				delete[] strInfoLog;
			}
			return program;
		}
		void ShaderProgram::CreateFromFiles(const std::string vertex_shader_file_name, const std::string fragment_shader_file_name)
		{
			m_opengl_vertex_shader = CreateShaderFromFile(vertex_shader_file_name, GL_VERTEX_SHADER);
			m_opengl_fragment_shader = CreateShaderFromFile(fragment_shader_file_name, GL_FRAGMENT_SHADER);
			m_opengl_shader_program = CreateShaderProgram(m_opengl_vertex_shader, m_opengl_fragment_shader);
		}
		void ShaderProgram::Destroy()
		{
			glDeleteProgram(m_opengl_shader_program);
			glDeleteShader(m_opengl_vertex_shader);
			glDeleteShader(m_opengl_fragment_shader);
		}
		ShaderProgram::~ShaderProgram()
		{
			Destroy();
		}
		ShaderProgram::ShaderProgram()
		{

		}
		GLuint ShaderProgram::GetOpenGLID()
		{
			return m_opengl_shader_program;
		}
	}
}