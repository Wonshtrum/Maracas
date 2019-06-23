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
		inline unsigned int getCount() { return s_counts[m_type]; }
		inline GLenum getOpenGLType() { return s_OpenGLTypes[m_type]; }
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
			BufferLayout(BufferElement* elements, unsigned int elementCount);
			~BufferLayout() {}
			inline BufferElement* getElements() { return m_elements; }
			inline unsigned int getElementCount() { return m_elementCount; }
			inline unsigned int getStride() { return m_stride; }
		private:
			void calculateOffsetAndStride();
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
			inline BufferLayout* getLayout() { return m_layout; }
			inline virtual void setLayout(BufferLayout* layout) { m_layout = layout; }
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
			inline unsigned int getCount() { return m_count; }
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
			OpenGL_VertexBuffer(float data[], unsigned int size);
			inline virtual void bind() override { glBindBuffer(GL_ARRAY_BUFFER, m_rendererID); }
			inline virtual void unbind() override { glBindBuffer(GL_ARRAY_BUFFER, 0); }
		private:
			unsigned int m_rendererID;
	};

	/* =========================================== *
	 * OpenGL implementation of Index Buffer
	 * =========================================== */
	class OpenGL_IndexBuffer: public IndexBuffer {
		public:
			OpenGL_IndexBuffer(unsigned int indices[], unsigned int size);
			inline virtual void bind() override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID); }
			inline virtual void unbind() override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
		private:
			unsigned int m_rendererID;
	};
	
	/* =========================================== *
	 * OpenGL implementation of Vertex Array
	 * =========================================== */
	class OpenGL_VertexArray: public VertexArray {
		public:
			OpenGL_VertexArray();
			inline virtual void bind() override { glBindVertexArray(m_rendererID); }
			inline virtual void unbind() override { glBindVertexArray(0); }
			virtual void addVertexBuffer(VertexBuffer* vertexBuffer) override;
			virtual void setIndexBuffer(IndexBuffer* indexBuffer) override;
			inline virtual IndexBuffer* getIndexBuffer() override;
		private:
			unsigned int m_rendererID;
			//VertexBuffer vector ?
			IndexBuffer* m_indexBuffer;
	};
}

#endif
