#include "GraphicsData.h"

/* =========================================== *
 * load headers
 * =========================================== */

namespace Maracas {
	unsigned int BufferElement::s_sizes[NB_SHADERDATA_TYPES] = {4, 2*4, 3*4, 4*4, 3*3*4, 4*4*4, 4, 2*4, 3*4, 4*4, 1};
	unsigned int BufferElement::s_counts[NB_SHADERDATA_TYPES] = {1, 2, 3, 4, 3*3, 4*4, 1, 2, 3, 4, 1};
	GLenum BufferElement::s_OpenGLTypes[NB_SHADERDATA_TYPES] = {GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_INT, GL_INT, GL_INT, GL_INT, GL_BOOL};

	/* =========================================== *
	 * BufferLayout
	 * =========================================== */
	BufferLayout::BufferLayout(BufferElement* elements, unsigned int elementCount): m_elements(elements), m_elementCount(elementCount), m_stride(0) { calculateOffsetAndStride(); }

	void BufferLayout::calculateOffsetAndStride() {
		m_stride = 0;
		for (unsigned int i = 0 ; i < m_elementCount ; i++) {
			m_elements[i].m_offset = m_stride;
			m_stride += m_elements[i].m_size;
			MRC_CORE_DEBUG(m_elements[i].m_name," ",m_stride);
		}
	}

	/* =========================================== *
	 * OpenGL VertexBuffer
	 * =========================================== */
	OpenGL_VertexBuffer::OpenGL_VertexBuffer(float data[], unsigned int size) {
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	
	/* =========================================== *
	 * OpenGL IndexBuffer
	 * =========================================== */
	OpenGL_IndexBuffer::OpenGL_IndexBuffer(unsigned int indices[], unsigned int size) {
		m_count = size/sizeof(unsigned int);
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	/* =========================================== *
	 * OpenGL VertexArray
	 * =========================================== */
	OpenGL_VertexArray::OpenGL_VertexArray() {
		glGenVertexArrays(1, &m_rendererID);
		glBindVertexArray(m_rendererID);
	}

	void OpenGL_VertexArray::addVertexBuffer(VertexBuffer* vertexBuffer) {
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

	void OpenGL_VertexArray::setIndexBuffer(IndexBuffer* indexBuffer) {
		glBindVertexArray(m_rendererID);
		indexBuffer->bind();
		m_indexBuffer = indexBuffer;
	}

	IndexBuffer* OpenGL_VertexArray::getIndexBuffer() { return m_indexBuffer; }
}
