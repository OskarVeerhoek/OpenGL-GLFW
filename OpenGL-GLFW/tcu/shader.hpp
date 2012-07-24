#ifndef OPENGL_GLFW_TCU_SHADER_H_
#define OPENGL_GLFW_TCU_SHADER_H_
#include <string>
#include <map>
typedef unsigned int GLuint;
typedef unsigned int GLenum;
namespace tcu
{
	namespace shader
	{
		struct Program
		{
			GLuint _shader_program;
			GLuint _vertex_shader;
			GLuint _geometry_shader;
			GLuint _fragment_shader;
			bool _use_geometry_shader;
			std::map<std::string, GLuint> _vertex_attributes;
			std::map<std::string, GLuint> _uniforms;
		};
		//const GLuint CreateShaderFromFile(const std::string file_name, const GLenum shader_type);
		//const GLuint CreateShaderProgram(const GLuint vertex_shader, const GLuint fragment_shader);
		const Program CreateProgramFromFiles(const std::string vertex_shader_file_name, const std::string fragment_shader_file_name, const std::string geometry_shader_file_name = "NULL");
		const void AddVertexAttributeToProgram(Program &program, const std::string attribute);
		const void AddUniformToProgram(Program &program, const std::string uniform);
		const GLuint GetVertexAttribute(const Program program, std::string attribute);
		const GLuint GetUniform(const Program program, std::string uniform);
		const void UseProgram(const Program program);
		const void DestroyProgram(const Program program);
	}
}
#endif