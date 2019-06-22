#include "GraphicsData.h"

namespace Maracas {
	unsigned int BufferElement::s_sizes[NB_SHADERDATA_TYPES] = {4, 2*4, 3*4, 4*4, 3*3*4, 4*4*4, 4, 2*4, 3*4, 4*4, 1};
	unsigned int BufferElement::s_counts[NB_SHADERDATA_TYPES] = {1, 2, 3, 4, 3*3, 4*4, 1, 2, 3, 4, 1};
	GLenum BufferElement::s_OpenGLTypes[NB_SHADERDATA_TYPES] = {GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_INT, GL_INT, GL_INT, GL_INT, GL_BOOL};
}
