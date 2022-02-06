#include "shader_program.h"

#include <algorithm>

using namespace std;

GLSLProgram& GLSLProgram::operator=(GLSLProgram&& other) noexcept
{
    auto temp_id = other.m_id;
    other.m_id = 0;
    glDeleteProgram(m_id);

    m_id = temp_id;

    return *this;
}