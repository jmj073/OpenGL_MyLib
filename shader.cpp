#include "shader.h"

#include <fstream>

using namespace std;

Shader::Shader(GLenum type, const GLchar* source_path)
    : m_type{ type }, m_id{ MakeShaderFromFile(type, source_path) }
{
    GLint success;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE || !m_id)
        throw ShaderError(m_id, "ERROR::SHADER:COMPILE_FAILED", source_path);
}

Shader::Shader(Shader&& other) noexcept
    : m_type{ other.m_type }, m_id{ other.m_id }
{
    other.m_id = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept {
    auto temp_id = other.m_id;
    other.m_id = 0;
    glDeleteShader(m_id);

    m_id = temp_id;
    m_type = other.m_type;

    return *this;
}

GLuint Shader::MakeShaderFromSource(GLenum type, const GLchar* shader_source)
{
    // vertex shader
    GLuint vertexShader;
    vertexShader = glCreateShader(type);
    glShaderSource(vertexShader, 1, &shader_source, nullptr);
    glCompileShader(vertexShader);

    return vertexShader;
}

GLuint Shader::MakeShaderFromFile(GLenum type, const char* path)
{
    ifstream src_stream(path);
    if (!src_stream)
        throw path_exception("cannot open file", path);

    string source = gulp(src_stream);

    src_stream.close();

    return MakeShaderFromSource(type, source.c_str());
}

// ShaderError======================================================================

ShaderError::ShaderError(GLuint _shader_id, const char* _message, const char* _path)
    : runtime_error(_message), path_exception(_message, _path), GLObjectError(_shader_id, _message)
{

}