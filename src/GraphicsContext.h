#ifndef MRC_GRAPHICSCONTEXT_H
#define MRC_GRAPHICSCONTEXT_H
#pragma once

/* =========================================== *
 * load headers
 * =========================================== */
#include "Core.h"
#include "GraphicsData.h"
//ENDHEAD
namespace Maracas {
	/* =========================================== *
	 * abstract class GraphicsContext, Maracas API
	 * =========================================== */
	class GraphicsContext {
		public:
			virtual ~GraphicsContext() {}
			virtual void init() = 0;
			virtual void swapBuffers() = 0;
			virtual void clearColor(float r, float g, float b, float a) = 0;
			virtual void drawTriangles(VertexArray* vertexArray) = 0;
			virtual VertexArray* createVertexArray() = 0;
			virtual VertexBuffer* createVertexBuffer(float data[], unsigned int size) = 0;
			virtual IndexBuffer* createIndexBuffer(unsigned int indices[], unsigned int size) = 0;
	};

	/* =========================================== *
	 * implemented class GraphicsContext with openGL
	 * =========================================== */
	class OpenGLContext: public GraphicsContext {
		public:
			OpenGLContext(GLFWwindow* windowHandle);
			virtual ~OpenGLContext() override;
			virtual void init() override;
			virtual void swapBuffers() override;
			virtual void clearColor(float r, float g, float b, float a) override;
			virtual void drawTriangles(VertexArray* vertexArray) override;
			virtual VertexArray* createVertexArray() override;
			virtual VertexBuffer* createVertexBuffer(float data[], unsigned int size) override;
			virtual IndexBuffer* createIndexBuffer(unsigned int indices[], unsigned int size) override;
		private:
			GLFWwindow* m_windowHandle;
	};
}

#endif
