#pragma once

#include <glad/glad.h>

#include "mylib1.h"

class Shader
{
public:
	explicit Shader(GLenum type = 0, GLuint shader_id = 0) : m_type{ type }, m_id{ shader_id } {}
	Shader(GLenum type, const GLchar* source_path);
	Shader(Shader&& other) noexcept;

	GLenum type() const {
		return m_type;
	}

	GLuint get_id() {
		return m_id;
	}

	Shader& operator=(Shader&& other) noexcept;

	~Shader() {
		glDeleteShader(m_id);
		m_id = 0;
	}

public:
	static GLuint MakeShaderFromSource(GLenum type, const GLchar* shader_source);
	static GLuint MakeShaderFromFile(GLenum type, const char* path);

private:
	GLenum m_type;
	GLuint m_id;
};

// ShaderError======================================================================

class ShaderError : public path_exception, public GLObjectError
{
public:
	ShaderError(GLuint _shader_id, const char* _message, const char* _path);
};