#ifndef OPENGL_GLFW_TCU_PROGRAM_H_
#define OPENGL_GLFW_TCU_PROGRAM_H_
#include <glm/glm.hpp>
#include "shader.hpp"
namespace tcu
{
	namespace program
	{
		class Program
		{
		public:
			Program();
			~Program();
			void Init();
			void Render();
			void Destroy();
		private:
			tcu::shader::Program shader_program;
			GLuint vao;
			GLuint vbo;
		};
	}
}
#endif