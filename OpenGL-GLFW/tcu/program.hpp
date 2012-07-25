#ifndef OPENGL_GLFW_TCU_PROGRAM_H_
#define OPENGL_GLFW_TCU_PROGRAM_H_
// Include the tcu::shader contents.
#include "shader.hpp"

namespace program
{
	// Program represents the OpenGL code that is to be executed in the application.
	class Program
	{
	public:
		// Constructs an instance of Program. Does nothing else.
		Program();
		// Destructs the intsnace in question of Program. 
		~Program();
		// Initializes the Program. Sets up rendering code.
		void Init();
		// Renders to the screen.
		void Render();
		// Destroys the Program. Cleans up resources.
		void Destroy();
	private:
		// The OpenGL shader program.
		shader::ShaderProgram m_shader_program; // *
		// The OpenGL VAO (Vertex Array Object).
		GLuint m_vao;
		// The OpenGL VBO (Vertex Buffer Object).
		GLuint m_vbo;
		// An OpenGL Texture
		GLuint m_texture;
	};
}

#endif

// * = I made this method/function/class myself, feel free to merge the implementation into this file.