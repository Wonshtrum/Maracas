#ifndef MRC_SHADER_H
#define MRC_SHADER_H
#pragma once

/* =========================================== *
 * load headers
 * =========================================== */
#include "Core.h"
//ENDHEAD
namespace Maracas {
	/* =========================================== *
	 * basic GLSL shader class (without api)
	 * =========================================== */
	class Shader {
		public:
			Shader(const char* vertexShaderSrc, const char* fragmentShaderSrc);
			~Shader();
			void bind();
			void unbind();
			static unsigned int compileShader(unsigned int type, const char* source);
		private:
			unsigned int m_program;
	};
}

#endif
