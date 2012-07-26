#include "program.hpp"
#include "opengl.h"
#include "error.hpp" // *

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
/* 0 */	1.0f, 0.0f, 0.0f, // each colour has three components, red, green and blue
/* 1 */	0.0f, 1.0f, 0.0f, // colours range from 0.0 to 1.0
/* 2 */	0.0f, 0.0f, 1.0f,
/* 3 */	1.0f, 1.0f, 1.0f,
	};
	// Array containing the index data for the two triangles
	const GLushort INDEX_DATA[] = { 
		0, 1, 2,
		0, 2, 3
	};
	// Store the vertex attributes. These correspond to the number after "layout(location = " in the vertex shader.
	enum VertexAttribute
	{
		VERTEX_POSITION = 0, VERTEX_COLOUR = 1
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
		m_error_handler.Create();
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
		// Create a new shader program from the two files containing a vertex shader and a fragment shader.
		m_shader_program.CreateFromFiles("shader.vert", "shader.frag");
		m_brightness_uniform_location = glGetUniformLocation(m_shader_program.GetOpenGLID(), "brightness");
		// Binds the shader program to OpenGL.
		glUseProgram(m_shader_program.GetOpenGLID());
		m_brightness = 0.3f;
		// Check for OpenGL errors. 
		m_error_handler.Check(true, "Initialization Code: ");
	}
	void Program::Update(double passed_time)
	{
		glUniform1f(m_brightness_uniform_location, m_brightness);
		// >> glClear sets the bitplane area of the window to values previously selected by glClearColor.
		// Clear the window of its contents.
		glClear(GL_COLOR_BUFFER_BIT);
		// Draw two triangles using the indices in m_ibo that point to the vertex data in m_vbo.
		// >> When glDrawElements is called, it uses count sequential elements from an enabled array, starting at 
		// >> indices to construct a sequence of geometric primitives. mode specifies what kind of primitives are
		// >> constructed and how the array elements construct these primitives
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		// Check for OpenGl errors.
		m_error_handler.Check(false, "Update Code: ");
		// Input
		std::cout << (passed_time) << std::endl;
		if (glfwGetKey('A') == GLFW_PRESS)
		{
			m_brightness -= 1.0f * passed_time;
		}
		if (glfwGetKey('D') == GLFW_PRESS)
		{
			m_brightness += 1.0f * passed_time;
		}
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
		// Check for OpenGL errors.
		m_error_handler.Check(true, "Clean Up Code: ");
		m_error_handler.Destroy();
	}
}		


// * =  I created this method myself, and you are free to copy the implementation to this file.