#ifndef MRC_GRAPHICSDATA_H
#define MRC_GRAPHICSDATA_H
#pragma once

/* =========================================== *
 * load headers
 * =========================================== */
#include "Core.h"

/* =========================================== *
 * GraphicsData specific macros
 * =========================================== */
#define NB_SHADERDATA_TYPES 11
//ENDHEAD
namespace Maracas {
	namespace ShaderData {
		enum Type {
			Float,
			Float2,
			Float3,
			Float4,
			Mat3,
			Mat4,
			Int,
			Int2,
			Int3,
			Int4,
			Bool
		};
	}

	/* =========================================== *
	 * buffer element for buffer layout
	 * =========================================== */
	struct BufferElement {
		const char* m_name;
		ShaderData::Type m_type;
		unsigned int m_size;
		unsigned int m_offset;
		bool m_normalized;
		unsigned int getCount() { return s_counts[m_type]; }
		GLenum getOpenGLType() { return s_OpenGLTypes[m_type]; }
		static unsigned int s_sizes[NB_SHADERDATA_TYPES];
		static unsigned int s_counts[NB_SHADERDATA_TYPES];
		static GLenum s_OpenGLTypes[NB_SHADERDATA_TYPES];
		BufferElement(ShaderData::Type type, const char* name, bool normalized=false): m_name(name), m_type(type), m_size(s_sizes[type]), m_offset(0), m_normalized(normalized) {}
	};

	/* =========================================== *
	 * general class buffer layout
	 * =========================================== */
	class BufferLayout {
		public:
			BufferLayout(BufferElement* elements, unsigned int elementCount): m_elements(elements), m_elementCount(elementCount), m_stride(0) { calculateOffsetAndStride(); }
			~BufferLayout() {}
			BufferElement* getElements() { return m_elements; }
			unsigned int getElementCount() { return m_elementCount; }
			unsigned int getStride() { return m_stride; }
		private:
			void calculateOffsetAndStride() {
				m_stride = 0;
				for (unsigned int i = 0 ; i < m_elementCount ; i++) {
					m_elements[i].m_offset = m_stride;
					m_stride += m_elements[i].m_size;
					MRC_CORE_DEBUG(m_elements[i].m_name," ",m_stride);
				}
			}
			BufferElement* m_elements;
			unsigned int m_elementCount;
			unsigned int m_stride;
	};

	/* =========================================== *
	 * abstracted class VertexBuffer
	 * =========================================== */
	class VertexBuffer {
		public:
			virtual ~VertexBuffer() {}
			virtual void bind() = 0;
			virtual void unbind() = 0;
			BufferLayout* getLayout() { return m_layout; }
			virtual void setLayout(BufferLayout* layout) { m_layout = layout; };
		protected:
			BufferLayout* m_layout;
	};

	/* =========================================== *
	 * abstracted class IndexBuffer
	 * =========================================== */
	class IndexBuffer {
		public:
			virtual ~IndexBuffer() {}
			virtual void bind() = 0;
			virtual void unbind() = 0;
			unsigned int getCount() { return m_count; }
		protected:
			unsigned int m_count;
	};

	/* =========================================== *
	 * abstracted class VertexArray (openGL inspired)
	 * =========================================== */
	class VertexArray {
		public:
			virtual ~VertexArray() {};
			virtual void bind() = 0;
			virtual void unbind() = 0;
			virtual void addVertexBuffer(VertexBuffer* vertexBuffer) = 0;
			virtual void setIndexBuffer(IndexBuffer* indexBuffer) = 0;
			virtual IndexBuffer* getIndexBuffer() = 0;

	};

	/* =========================================== *
	 * OpenGL implementation of Vertex Buffer
	 * =========================================== */
	class OpenGL_VertexBuffer: public VertexBuffer {
		public:
			OpenGL_VertexBuffer(float data[], unsigned int size) {
				glGenBuffers(1, &m_rendererID);
				glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
				glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			}
			virtual void bind() override { glBindBuffer(GL_ARRAY_BUFFER, m_rendererID); }
			virtual void unbind() override { glBindBuffer(GL_ARRAY_BUFFER, 0); }
		private:
			unsigned int m_rendererID;
	};

	/* =========================================== *
	 * OpenGL implementation of Index Buffer
	 * =========================================== */
	class OpenGL_IndexBuffer: public IndexBuffer {
		public:
			OpenGL_IndexBuffer(unsigned int indices[], unsigned int size) {
				m_count = size/sizeof(unsigned int);
				glGenBuffers(1, &m_rendererID);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
			}
			virtual void bind() override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID); }
			virtual void unbind() override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
		private:
			unsigned int m_rendererID;
	};
	
	/* =========================================== *
	 * OpenGL implementation of Vertex Array
	 * =========================================== */
	class OpenGL_VertexArray: public VertexArray {
		public:
			OpenGL_VertexArray() {
				glGenVertexArrays(1, &m_rendererID);
				glBindVertexArray(m_rendererID);
			}
			virtual void bind() override { glBindVertexArray(m_rendererID); }
			virtual void unbind() override { glBindVertexArray(0); }
			virtual void addVertexBuffer(VertexBuffer* vertexBuffer) override {
				unsigned int stride = vertexBuffer->getLayout()->getStride();
				MRC_CORE_ASSERT(stride, "Vertex Buffer has no layout!");
				unsigned int elementCount = vertexBuffer->getLayout()->getElementCount();
				BufferElement* elements = vertexBuffer->getLayout()->getElements();
				for (unsigned int i = 0 ; i < elementCount ; i++) {
					glEnableVertexAttribArray(i);
					glVertexAttribPointer(i, elements[i].getCount(), elements[i].getOpenGLType(), elements[i].m_normalized, stride, (const void*)(elements[i].m_offset));
					MRC_DEBUG("Layout(",i,") ", elements[i].getCount(),", ", elements[i].getOpenGLType(),", ", elements[i].m_normalized,", ", elements[i].m_size,", ", elements[i].m_offset);
				}
			}
			virtual void setIndexBuffer(IndexBuffer* indexBuffer) override {
				glBindVertexArray(m_rendererID);
				indexBuffer->bind();
				m_indexBuffer = indexBuffer;
			}
			virtual IndexBuffer* getIndexBuffer() override { return m_indexBuffer; }
		private:
			unsigned int m_rendererID;
			//VertexBuffer vector ?
			IndexBuffer* m_indexBuffer;
	};
}

#endif
