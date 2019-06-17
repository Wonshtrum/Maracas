#include "Shader.h"

namespace Maracas {
	unsigned int Shader::compileShader(unsigned int type, const char* source) {
		unsigned int id = glCreateShader(type);
		glShaderSource(id, 1, &source, nullptr);
		glCompileShader(id);
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length*sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			glDeleteShader(id);
			MRC_ASSERT(false,"Failed to compile ", (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"), " shader:\n", message);
		}
		return id;
	}
	Shader::Shader(const char* vertexShaderSrc, const char* fragmentShaderSrc) {
		m_program = glCreateProgram();
		unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
		unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
		glAttachShader(m_program, vs);
		glAttachShader(m_program, fs);
		glLinkProgram(m_program);
		glValidateProgram(m_program);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}
	Shader::~Shader() { glDeleteProgram(m_program); }
	void Shader::bind() { glUseProgram(m_program); }
	void Shader::unbind() { glUseProgram(0); }
}
