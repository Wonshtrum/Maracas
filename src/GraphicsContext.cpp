#include "GraphicsContext.h"

namespace Maracas {
	void OpenGLContext::init() {
		int success = glewInit();
		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
		MRC_CORE_ASSERT(success == GLEW_OK, "Could not initialized GLEW");
		MRC_CORE_INFO("OpenGL context initialized (",glGetString(GL_VERSION),")");
	}

	void OpenGLContext::swapBuffers() {
		glfwSwapBuffers(m_windowHandle);
	}
}
