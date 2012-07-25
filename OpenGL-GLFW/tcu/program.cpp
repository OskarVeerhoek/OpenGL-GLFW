#include "program.hpp"
// Core OpenGL Functions.
#include <GL/glew.h>
// Console Input and Output.
#include <iostream>
// OpenGL Error Handling 
#include "error.hpp" // *
// Texture Loading
#include <SOIL.h>

namespace tcu
{
	namespace program
	{	
		// Array containing the vertex data for the triangle
		const GLfloat VERTEX_DATA[] = {
			// Vertex Positions
			0.75f, 0.75f, 0.0f, 1.0f, // each vertex position has four components, x, y, z, and w (which should be 1).
			0.75f, -0.75f, 0.0f, 1.0f,
			-0.75f, -0.75f, 0.0f, 1.0f,
			// Vertex Colours
			1.0f, 0.0f, 0.0f, 1.0f, // each vertex colour has four components, r, g, b, and a
			0.0f, 1.0f, 0.0f, 1.0f, // colours range from 0.0 to 1.0
			0.0f, 0.0f, 1.0f, 1.0f,
		};
		// Store the vertex attributes. These correspond to the number after "layout(location = " in the vertex shader.
		enum VertexAttribute
		{
			VERTEX_POSITION = 0, VERTEX_COLOUR = 1
		};

		Program::Program()
		{
			// Does nothing but construct the object.
		}

		Program::~Program()
		{
			Destroy();
		}
		void Program::Init()
		{
			// >> Vertex Array Objects (VAO) are OpenGL Objects that store the 
			// >> set of bindings between Vertex Attributes and the user's source 
			// >> vertex data. (http://www.opengl.org/wiki/Vertex_Array_Object)
			// >> glGenVertexArrays returns n vertex array object names in arrays.
			// Create one VAO and store it in GLuint vao. 
			glGenVertexArrays(1, &m_vao);
			// >> glBindVertexArray binds the vertex array object with name array.
			// Bind the aforementioned VAO to OpenGL.
			glBindVertexArray(m_vao);
			// >> glGenBuffers returns n buffer object names in buffers.
			// >> No buffer objects are associated with the returned buffer object names
			// >> until they are first bound by calling glBindBuffer.
			glGenBuffers(1, &m_vbo);
			// >> glBindBuffer binds a buffer object to the specified buffer binding point. 
			// >> Vertex Buffer Objects (VBOs) are Buffer Objects that are used for
			// >> vertex data. (VBO = GL_ARRAY_BUFFER)
			// Bind our buffer object to GL_ARRAY_BUFFER, thus making it a VBO.
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			// >> glBufferData creates a new data store for the buffer object currently bound
			// >> to target. Any pre-existing data store is deleted. The new data store is created 
			// >> with the specified size in bytes and usage. If data is not NULL, the data 
			// >> store is initialized with data from this pointer. In its initial state, the
			// >> new data store is not mapped, it has a NULL mapped pointer, and its mapped 
			// >> access is GL_READ_WRITE.
			// Store the vertex data (position and colour) in the VBO.
			glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX_DATA), VERTEX_DATA, GL_STATIC_DRAW);
			// >> glEnableVertexAttribArray enables the generic vertex attribute array specified by index. 
			// >> glDisableVertexAttribArray disables the generic vertex attribute array specified by 
			// >> index. By default, all client-side capabilities are disabled, including all generic 
			// >> vertex attribute arrays. If enabled, the values in the generic vertex attribute array
			// >> will be accessed and used for rendering when calls are made to vertex array commands 
			// >> such as glDrawArrays, glDrawElements, glDrawRangeElements, glMultiDrawElements, or glMultiDrawArrays.
			// Enable the vertex position vertex attribute.
			glEnableVertexAttribArray(VERTEX_POSITION);
			// Enable the vertex colour vertex attribute.
			glEnableVertexAttribArray(VERTEX_COLOUR);
			// >> glVertexAttribPointer and glVertexAttribIPointer specify the location and data format of the 
			// >> array of generic vertex attributes at index index to use when rendering. size specifies 
			// >> the number of components per attribute and must be 1, 2, 3, 4, or GL_BGRA. type specifies
			// >> the data type of each component, and stride specifies the byte stride from one attribute
			// >> to the next, allowing vertices and attributes to be packed into a single array or stored
			// >> in separate arrays.
			// Tell OpenGL where to find the vertex position data (inside the VBO).
			glVertexAttribPointer(VERTEX_POSITION, 4, GL_FLOAT, GL_FALSE, 0, 0);
			// Tell OpenGL where to find the vertex colour data (inside the VBO).
			glVertexAttribPointer(VERTEX_COLOUR, 4, GL_FLOAT, GL_FALSE, 0, (void*) 48);
			// Create a new shader program from the two files containing a vertex shader and a fragment shader.
			m_shader_program.CreateFromFiles("shader.vert", "shader.frag");
			// Binds the shader program to OpenGL.
			glUseProgram(m_shader_program.GetOpenGLID());
			// Load a texture.
			m_texture = SOIL_load_OGL_texture("background.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
			// Check for OpenGL errors. 
			tcu::error::CheckErrors(true, "Initialization: "); // *
		}
		void Program::Render()
		{
			// >> glClear sets the bitplane area of the window to values previously selected by glClearColor.
			// Clear the window of its contents.
			glClear(GL_COLOR_BUFFER_BIT);
			// Draw the triangle using the shader program and the data from the two glVertexAttribPointer calls.
			glDrawArrays(GL_TRIANGLES, 0, 3);
			// Check for OpenGl errors.
			tcu::error::CheckErrors(false, "Render: ");	// *
		}
		void Program::Destroy()
		{
			// >> glDeleteVertexArrays deletes n vertex array objects whose names are stored in the array
			// >> addressed by arrays.
			// Delete the VAO.
			glDeleteVertexArrays(1, &m_vao);
			// >> glDeleteBuffers deletes n buffer objects named by the elements of the array buffers. 
			// Delete the VBO.
			glDeleteBuffers(1, &m_vbo);
			// Destroy the shader program.
			m_shader_program.Destroy();
			// Check for OpenGL errors.
			tcu::error::CheckErrors(true, "Destroying: "); // *
		}
	}		
}			

// * =  I created this method myself, and you are free to copy the implementation to this file.