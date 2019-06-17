#include "GraphicsContext.h"

namespace Maracas {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle): m_windowHandle(windowHandle) { glfwMakeContextCurrent(windowHandle); };
	OpenGLContext::~OpenGLContext() {
		if (m_shader) {
			delete m_shader;
		}
		MRC_INFO("OpenGL context destroyed");
	}
	void OpenGLContext::init() {
		int success = glewInit();
		MRC_CORE_ASSERT(success == GLEW_OK, "Could not initialized GLEW");
		MRC_CORE_INFO("OpenGL context initialized");
		MRC_CORE_INFO("  Vendor:   ",glGetString(GL_VENDOR));
		MRC_CORE_INFO("  Renderer: ",glGetString(GL_RENDERER));
		MRC_CORE_INFO("  Version:  ",glGetString(GL_VERSION));
		/////////////////////////////////////
		//       EXTREMELY TEMPORARY
		/////////////////////////////////////
		float vertices[] = {
			-0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 1.0f, 1.0f, 0.0f
		};
		unsigned int indices[] {
			0, 1, 2,
			2, 3, 0
		};
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);

		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		m_shader = new Shader(
				R"(
				#version 330 core
				layout(location = 0) in vec4 a_position;
				out vec4 v_position;
				void main() {
					v_position = a_position;
					gl_Position = a_position;
				})", R"(
				#version 330 core
				in vec4 v_position;
				layout(location = 0) out vec4 color;
				void main() {
					color = vec4(1.0,0.0,0.0,1.0);
				})");
		m_shader->bind();
	}

	void OpenGLContext::swapBuffers() {
		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glfwSwapBuffers(m_windowHandle);
	}
}
