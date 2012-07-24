#include "program.hpp"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glfw.h>
#include <iostream>
#include "error.hpp"

namespace tcu
{
	namespace program
	{	
		const GLfloat VERTEX_DATA[] = {
			// Vertex Positions
			0.75f, 0.75f, 0.0f, 1.0f,
			0.75f, -0.75f, 0.0f, 1.0f,
			-0.75f, -0.75f, 0.0f, 1.0f,
			// Vertex Colours
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
		};
		enum VertexAttribute
		{
			VERTEX_POSITION = 0, VERTEX_COLOUR = 1
		};

		Program::Program()
		{
			
		}
		Program::~Program()
		{

		}
		void Program::Init()
		{
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX_DATA), VERTEX_DATA, GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTEX_POSITION);
			glEnableVertexAttribArray(VERTEX_COLOUR);
			glVertexAttribPointer(VERTEX_POSITION, 4, GL_FLOAT, GL_FALSE, 0, 0);
			glVertexAttribPointer(VERTEX_COLOUR, 4, GL_FLOAT, GL_FALSE, 0, (void*) 48);
			shader_program = tcu::shader::CreateProgramFromFiles("shader.vert", "shader.frag");
			tcu::shader::UseProgram(shader_program);
			tcu::error::CheckErrors(true, "Initialization: ");
		}
		void Program::Render()
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			tcu::error::CheckErrors(false, "Render: ");	
		}
		void Program::Destroy()
		{
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
			tcu::shader::DestroyProgram(shader_program);
			tcu::error::CheckErrors(true, "Destroying: ");
		}
	}		
}			
