#include "shader.hpp"
#include <GL/glew.h>
#include <string>
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
		const Program CreateProgramFromFiles(const std::string vertex_shader_file_name, const std::string fragment_shader_file_name, const std::string geometry_shader_file_name)
		{
			Program program;
			program._vertex_shader = CreateShaderFromFile(vertex_shader_file_name, GL_VERTEX_SHADER);
			program._fragment_shader = CreateShaderFromFile(fragment_shader_file_name, GL_FRAGMENT_SHADER);
			if ("NULL" != geometry_shader_file_name)
			{
				program._geometry_shader = CreateShaderFromFile(geometry_shader_file_name, GL_GEOMETRY_SHADER);
				program._shader_program = CreateShaderProgram(program._vertex_shader, program._fragment_shader, program._geometry_shader);
				program._use_geometry_shader = true;
				return program;
			}
			else
			{
				program._shader_program = CreateShaderProgram(program._vertex_shader, program._fragment_shader);
				program._use_geometry_shader = false;
				return program;
			}
		}
		const void DestroyProgram(const Program program)
		{
			glDeleteProgram(program._shader_program);
			glDeleteShader(program._vertex_shader);
			glDeleteShader(program._fragment_shader);
			if (true == program._use_geometry_shader)
				glDeleteShader(program._geometry_shader);
		}
		const void UseProgram(Program program)
		{
			glUseProgram(program._shader_program);
		}
		const void AddVertexAttributeToProgram(Program &program, std::string attribute)
		{
			program._vertex_attributes[attribute] = glGetAttribLocation(program._shader_program, attribute.c_str());
		}
		const void AddUniformToProgram(Program &program, std::string uniform)
		{
			program._uniforms[uniform] = glGetUniformLocation(program._shader_program, uniform.c_str());
		}
		const GLuint GetVertexAttribute(const Program program, std::string attribute)
		{
			if (program._vertex_attributes.find(attribute) == program._vertex_attributes.end())
			{
				std::cout << "Map does not contain value." << std::endl;
				return 0;
			}
			else
			{
				return program._vertex_attributes.find(attribute)->second;
			}
		}
		const GLuint GetUniform(const Program program, std::string uniform)
		{
			if (program._uniforms.find(uniform) == program._uniforms.end())
			{
				std::cout << "Map does not contain value." << std::endl;
				return 0;
			}
			else
			{
				return program._uniforms.find(uniform)->second;
			}
		}
	}
}