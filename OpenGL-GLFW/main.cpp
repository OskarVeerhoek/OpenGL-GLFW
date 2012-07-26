// Copyright (c) 2012, Oskar Veerhoek
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// The views and conclusions contained in the software and documentation are those
// of the authors and should not be interpreted as representing official policies,
// either expressed or implied, of the FreeBSD Project.

// The OpenGL Extension Wrangler Library
// Copyright (C) 2002-2008, Milan Ikits <milan ikits[]ieee org>
// Copyright (C) 2002-2008, Marcelo E. Magallon <mmagallo[]debian org>
// Copyright (C) 2002, Lev Povalahev
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice, 
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice, 
//   this list of conditions and the following disclaimer in the documentation 
//   and/or other materials provided with the distribution.
// * The name of the author may be used to endorse or promote products 
//   derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
// THE POSSIBILITY OF SUCH DAMAGE.

// Copyright (c) 2012, GLM
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal in 
// the Software without restriction, including without limitation the rights 
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
// copies of the Software, and to permit persons to whom the Software is furnished
// to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE 
// USE OR OTHER DEALINGS IN THE SOFTWARE.

// ">>" indicates a snippet of the documentation of the library in question

#include "opengl.h"
#include "standard.h"
#include "program.hpp"

// Creates an instance of tcu::program::Program, the class containing our OpenGL code
program::Program g_program;
bool g_is_program_destroyed = false;

// A method which is executed after the user presses the exit button on the window
int GLFWCALL WindowCloseCallback()
{
	// Clean up the resources (OpenGL Code)
	g_program.Destroy();
	g_is_program_destroyed = true;
	// Allow the user to get rid of the window

	return GL_TRUE;
}
int main(void)
{
	// >> glfwInit initializes GLFW. No other function of GLFW may be called before 
	// >> it has been invoked. If glfwInit returns GL_FALSE if it has failed. 
	if (glfwInit() == GL_FALSE)
		// Quit the program if glfwInit fails.
		return EXIT_FAILURE;
	// >> glfwOpenWindowHint sets additional properties for a window that is to be opened. 
	// >> Calls to glfwOpenWindowHint after glfwOpenWindow will be discarded.
	// Set the OpenGL version to 3.2. 
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	// Set forward compatibility to true. This step is necessary for Mac OS Lion.
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// Enable the OpenGL core profile. This step is necessary for Mac OS Lion, too.
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Make the window unresizable.
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	// >> glfwOpenWindow opens an OpenGL window with the following parameters
	// >> int width = width of the window
	// >> int height = height of the window
	// >> int redbits, int greenbits, int bluebits = color buffer bit depth
	// >> int alphabits = alpha buffer bit depth
	// >> int depthbits = depth buffer (Z-Buffer) bit depth
	// >> int stencilbits = stencil buffer bit depth
	// >> int mode = whether to go fullscreen (GLFW_FULLSCREEN) or windowed (GLFW_WINDOW) 
	// >> glfwOpenWindow returns GL_TRUE if the window was opened correctly, or GL_FALSE if GLFW
	// >> failed to open the window. 
	if (glfwOpenWindow(640, 480, 8, 8, 8, 8, 24, 8, GLFW_WINDOW) == GL_FALSE)
		// Quit the program if GLFW fails to open a window.
		glfwTerminate();
	// Enable Vsync (improves visual quality, caps frame-rate to 60fps).
	glfwSwapInterval(1);
	// Intitialize GLEW so we can use modern OpenGL functions.
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "GLEW failed." << std::endl;
	}
	// >> glfwSetWindowCloseCallback selects which function should be called
	// >> upon on a window close event. The function should have the following 
	// >> prototype:
	// >> int GLFWCALL functionname(void);
	glfwSetWindowCloseCallback(WindowCloseCallback);
	// This variable is true when the window is open and should be rendered on, 
	// and false if it should be closed or - in the case that it has already
	// been closed - cleaned up.
	bool running = true;
	// Initialize the OpenGL code.
	g_program.Init();
	double last_time = glfwGetTime();
	while (running)
	{
		// Render graphics to the display
		g_program.Update(glfwGetTime() - last_time);
		last_time = glfwGetTime();
		// Updates the screen (with double buffering)
		glfwSwapBuffers();
		// If we press escape and if the window has not been closed, keep running.
		running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	}
	// Clean up the OpenGL code.
	if (!g_is_program_destroyed)
	{
		g_program.Destroy();
	}
	// >> glfwCloseWindow closes the OpenGL window
	glfwCloseWindow();
	// Quit the program.
	return EXIT_SUCCESS;
}