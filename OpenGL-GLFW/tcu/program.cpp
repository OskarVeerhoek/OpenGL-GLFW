#include "program.hpp"
// Core OpenGL Functions.
#include <GL/glew.h>
// Console Input and Output.
#include <iostream>
// OpenGL Error Handling 
#include "error.hpp" // *
// Texture Loading
#include <SOIL.h>

namespace program
{	
	// Array containing the vertex data for the two triangles
	const GLfloat VERTEX_DATA[] = {
		// Vertex Positions
/* 0 */	-1.0f, -1.0f, // each vertex position has two components, x, and y
/* 1 */	+1.0f, -1.0f,
/* 2 */	+1.0f, +1.0f,
/* 3 */	-1.0f, +1.0f,
		// Colours
		1.0f, 0.0f, 0.0f, // each colour has three components, red, green and blue
		0.0f, 1.0f, 0.0f, // colours range from 0.0 to 1.0
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		// Texture Coordinates
		0.0f, 0.0f, // each texture coordinate has two component, x and y
		1.0f, 0.0f, // texture coordinates range from 0.0 to 1.0
		1.0f, 1.0f,
		0.0f, 1.0f
	};
	// Array containing the index data for the two triangles
	const GLushort INDEX_DATA[] = { 
		0, 1, 2,
		0, 2, 3
	};

	// Store the vertex attributes. These correspond to the number after "layout(location = " in the vertex shader.
	enum VertexAttribute
	{
		VERTEX_POSITION = 0, VERTEX_COLOUR = 1, VERTEX_TEXTURE = 2
	};
	// >> GLBooleanToString returns a string equivalent of a GLboolean.
	// >> If the GLboolean equals GL_TRUE, the result will be "true".
	// >> If the GLboolean equals GL_FALSE, the result will be "false".
	inline std::string GLBooleanToString(GLboolean value)
	{
		return (value == GL_TRUE && value != GL_FALSE) ? "true" : "false";
	}
	// >> GLBooleanToString returns a bool equivalent of a GLboolean.
	// >> If the GLboolean equals GL_TRUE, the result will be true.
	// >> If the GLboolean equals GL_FALSE, the result will be false.
	inline bool GLBooleanToBool(GLboolean value)
	{
		return (value == GL_TRUE && value != GL_FALSE) ? true : false;
	}
	Program::Program()
	{
		// Does nothing but construct the object.
	}
	Program::~Program()
	{
		// Does nothing but destruct the object.
	}
	void Program::Init()
	{
		error::Initialize();
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
		glGenBuffers(1, &m_ibo);
		// >> glBindBuffer binds a buffer object to the specified buffer binding point. 
		// >> Vertex Buffer Objects (VBOs) are Buffer Objects that are used for
		// >> vertex data. (VBO = GL_ARRAY_BUFFER)
		// Bind our buffer object to GL_ARRAY_BUFFER, thus making it a VBO.
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		// >> glBufferData creates a new data store for the buffer object currently bound
		// >> to target. Any pre-existing data store is deleted. The new data store is created 
		// >> with the specified size in bytes and usage. If data is not NULL, the data 
		// >> store is initialized with data from this pointer. In its initial state, the
		// >> new data store is not mapped, it has a NULL mapped pointer, and its mapped 
		// >> access is GL_READ_WRITE.
		// Store the vertex data (position and colour) in the VBO.
		glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX_DATA), VERTEX_DATA, GL_STATIC_DRAW);
		// Store the vertex index data in the IBO.
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDEX_DATA), INDEX_DATA, GL_STATIC_DRAW);
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
		// Enable the vertex texture coordinate vertex attribute.
		glEnableVertexAttribArray(VERTEX_TEXTURE);
		// >> glVertexAttribPointer and glVertexAttribIPointer specify the location and data format of the 
		// >> array of generic vertex attributes at index index to use when rendering. size specifies 
		// >> the number of components per attribute and must be 1, 2, 3, 4, or GL_BGRA. type specifies
		// >> the data type of each component, and stride specifies the byte stride from one attribute
		// >> to the next, allowing vertices and attributes to be packed into a single array or stored
		// >> in separate arrays.
		// Tell OpenGL where to find the vertex position data (inside the VBO).
		glVertexAttribPointer(VERTEX_POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);
		// Tell OpenGL where to find the vertex colour data (inside the VBO).
		glVertexAttribPointer(VERTEX_COLOUR, 3, GL_FLOAT, GL_FALSE, 0, (void*) 32);
		// Tell OpenGL where to find the texture coordinate data (inside the VBO).
		glVertexAttribPointer(VERTEX_TEXTURE, 2, GL_FLOAT, GL_FALSE, 0, (void*) 80);
		// Create a new shader program from the two files containing a vertex shader and a fragment shader.
		m_shader_program.CreateFromFiles("shader.vert", "shader.frag");
		// Binds the shader program to OpenGL.
		glUseProgram(m_shader_program.GetOpenGLID());
		// >> glActiveTexture selects which texture unit subsequent texture state calls will affect.
		glActiveTexture(GL_TEXTURE0);
		// Load the texture.
		m_texture = SOIL_load_OGL_texture("background.dds", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_DDS_LOAD_DIRECT);
		if (0 == m_texture)
			std::cout << "SOIL Loading Error: " << SOIL_last_result() << std::endl;
		glGetError(); // Reset error flag because SOIL has a bug
		// Bind the texture.
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glUniform1i(glGetUniformLocation(m_shader_program.GetOpenGLID(), "texture"), 0);
		// Check for OpenGL errors. 
		error::CheckErrors(false, "Initialization: "); // *
	}
	void Program::Render()
	{
		// >> glClear sets the bitplane area of the window to values previously selected by glClearColor.
		// Clear the window of its contents.
		glClear(GL_COLOR_BUFFER_BIT);
		// Draw the triangle using the shader program and the data from the two glVertexAttribPointer calls.
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (GLvoid*) 0);
		//glDrawRangeElements(GL_TRIANGLES, 0, 6, 6, GL_UNSIGNED_SHORT, NULL);
		// Check for OpenGl errors.
		error::CheckErrors(false, "Render: ");	// *
	}
	void Program::Destroy()
	{
		// Unbind the VBO.
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Unbind the IBO.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		// Unbind the VAO.
		glBindVertexArray(0);
		// Unbind the shader program.
		glUseProgram(0);
		// Unbind the texture.
		glBindTexture(GL_TEXTURE_2D, 0);
		// >> glDeleteVertexArrays deletes n vertex array objects whose names are stored in the array
		// >> addressed by arrays.
		// Delete the VAO.
		glDeleteVertexArrays(1, &m_vao);
		// >> glDeleteBuffers deletes n buffer objects named by the elements of the array buffers. 
		// Delete the VBO.
		glDeleteBuffers(1, &m_vbo);
		// Destroy the shader program.
		m_shader_program.Destroy();
		// Unload the texture.
		glDeleteTextures(1, &m_texture);
		// Check for OpenGL errors.
		error::CheckErrors(false, "Destroying: "); // *
		error::Destroy();
	}
}		


// * =  I created this method myself, and you are free to copy the implementation to this file.