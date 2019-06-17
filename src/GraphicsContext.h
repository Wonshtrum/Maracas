#ifndef MRC_GRAPHICSCONTEXT_H
#define MRC_GRAPHICSCONTEXT_H
#pragma once

/* =========================================== *
 * load headers
 * =========================================== */
#include "Core.h"
#include "Shader.h"
//ENDHEAD
namespace Maracas {
	/* =========================================== *
	 * abstract class GraphicsContext, Maracas API
	 * =========================================== */
	class GraphicsContext {
		public:
			virtual void init() = 0;
			virtual void swapBuffers() = 0;
	};

	/* =========================================== *
	 * implemented class GraphicsContext with openGL
	 * =========================================== */
	class OpenGLContext: public GraphicsContext {
		public:
			OpenGLContext(GLFWwindow* windowHandle);
			~OpenGLContext();
			virtual void init() override;
			virtual void swapBuffers() override;
		private:
			GLFWwindow* m_windowHandle;
			unsigned int m_vao;
			unsigned int m_vbo;
			unsigned int m_ibo;
			Shader* m_shader;
	};
}

#endif
