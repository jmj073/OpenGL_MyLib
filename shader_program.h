#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <initializer_list>

#include "shader.h"

class GLSLProgram
{
public:
	explicit GLSLProgram(GLuint program_id = 0)
		: m_id{ program_id } {}

	GLSLProgram(std::initializer_list<Shader> shaders)
		: GLSLProgram(const_cast<Shader*>(shaders.begin()), 
			const_cast<Shader*>(shaders.end())) {}

	explicit GLSLProgram(size_t N, Shader* shaders);

	template <typename Iter>
	GLSLProgram(Iter begin, Iter end);

	GLSLProgram(GLSLProgram&& other) noexcept;

	GLSLProgram& operator=(GLSLProgram&& other) noexcept;
	
	GLuint get_id() { 
		return m_id;
	}
	GLint get_uni_loc(const GLchar* name) {
		return glGetUniformLocation(m_id, name);
	}

	void use() { 
		glUseProgram(m_id); 
	}

	~GLSLProgram() {
		glDeleteProgram(m_id);
		m_id = 0;
	}

public:
	template <typename Iter>
	static GLuint MakeShaderProgram(Iter begin, Iter end);

private:
	GLuint m_id;
};


inline GLSLProgram::GLSLProgram(size_t N, Shader* shaders)
	: GLSLProgram(shaders, shaders + N)
{

}

template <typename Iter>
GLSLProgram::GLSLProgram(Iter begin, Iter end)
	: m_id{ MakeShaderProgram(begin, end) }
{
	GLint success;
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);

	if (success == GL_FALSE || !m_id)
		throw std::runtime_error("ERROR::SHADER::PROGRAM::LINK_FAILED");
}

inline GLSLProgram::GLSLProgram(GLSLProgram&& other) noexcept
	: m_id{ other.m_id } 
{
	other.m_id = 0;
}

template <typename Iter>
GLuint GLSLProgram::MakeShaderProgram(Iter begin, Iter end)
{
	GLuint shader_program = glCreateProgram();

	for (;begin != end; ++begin)
		glAttachShader(shader_program, (*begin).get_id());
	glLinkProgram(shader_program);

	return shader_program;
}

#endif // SHADER_PROGRAM_H