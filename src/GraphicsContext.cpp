#include "GraphicsContext.h"

namespace Maracas {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle): m_windowHandle(windowHandle) { glfwMakeContextCurrent(windowHandle); };
	OpenGLContext::~OpenGLContext() {
		MRC_INFO("OpenGL context destroyed");
	}
	void OpenGLContext::init() {
		int success = glewInit();
		MRC_CORE_ASSERT(success == GLEW_OK, "Could not initialized GLEW");
		MRC_CORE_INFO("OpenGL context initialized");
		MRC_CORE_INFO("  Vendor:   ",glGetString(GL_VENDOR));
		MRC_CORE_INFO("  Renderer: ",glGetString(GL_RENDERER));
		MRC_CORE_INFO("  Version:  ",glGetString(GL_VERSION));
		glfwSwapInterval(1);
	}
	
	void OpenGLContext::drawTriangles(VertexArray* vertexArray, Shader* shader, const glm::mat4& transform) {
		shader->bind();
		int locT = glGetUniformLocation(shader->getProgram(), "u_transform");
		glUniformMatrix4fv(locT, 1, GL_FALSE, glm::value_ptr(transform));
		vertexArray->bind();
		glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}

	VertexArray* OpenGLContext::createVertexArray() { return new OpenGL_VertexArray(); }
	VertexBuffer* OpenGLContext::createVertexBuffer(float data[], unsigned int size) { return new OpenGL_VertexBuffer(data, size); }
	IndexBuffer* OpenGLContext::createIndexBuffer(unsigned int indices[], unsigned int size) { return new OpenGL_IndexBuffer(indices, size); }

	void OpenGLContext::clearColor(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLContext::swapBuffers() {
		glfwSwapBuffers(m_windowHandle);
	}
}
