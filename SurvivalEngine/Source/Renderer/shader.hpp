#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	unsigned int Id;

	Shader& Use();

	// Setters
	void SetInteger(const char* name, int value);
	void SetVector4f(const char* name, const glm::vec4& value);
	void SetMatrix4(const char* name, const glm::mat4& matrix);

	void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);

private:


};

#endif