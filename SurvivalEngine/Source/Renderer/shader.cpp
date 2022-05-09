#include "Shader.hpp"

#include <iostream>
#include <vector>

Shader& Shader::Use()
{
    glUseProgram(this->Id);
    return *this;
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
    unsigned int vs, fs, gs;

    // Vertex Shader
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexSource, NULL);
    glCompileShader(vs);

    GLint isCompiled = 0;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vs, maxLength, &maxLength, &infoLog[0]);

        // Delete shader
        glDeleteShader(vs);

        // Return for now until I get this error
        return;
    }

    // Fragment Shader
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentSource, NULL);
    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fs, maxLength, &maxLength, &infoLog[0]);

        // Delete both shaders because of leaking
        glDeleteShader(fs);
        glDeleteShader(vs);

        // Return for now until I get this error
        return;
    }

    // Check for Geometry Shader
    if (geometrySource != nullptr)
    {
        gs = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gs, 1, &geometrySource, NULL);
        glCompileShader(gs);
    }

    // Create shader program
    this->Id = glCreateProgram();
    glAttachShader(this->Id, vs);
    glAttachShader(this->Id, fs);
    if (geometrySource != nullptr)
        glAttachShader(this->Id, gs);

    // Links shaders
    glLinkProgram(this->Id);

    // Check for program linking error
    GLint isLinked = 0;
    glGetProgramiv(this->Id, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(this->Id, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(this->Id, maxLength, &maxLength, &infoLog[0]);

        // Delete program because we dont need it
        glDeleteProgram(this->Id);

        // Delete shaders
        glDeleteShader(vs);
        glDeleteShader(fs);

        // Return for now until I get this error
        return;
    }

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDetachShader(this->Id, vs);
    glDeleteShader(vs);

    glDetachShader(this->Id, fs);
    glDeleteShader(fs);

    if (geometrySource != nullptr)
        //glDetachShader(this->Id, gs);
        glDeleteShader(gs);
}

void Shader::SetInteger(const char* name, int value)
{
    glUniform1i(glGetUniformLocation(this->Id, name), value);
}

void Shader::SetVector4f(const char* name, const glm::vec4& value)
{
    glUniform4f(glGetUniformLocation(this->Id, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char* name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(this->Id, name), 1, false, glm::value_ptr(matrix));
}