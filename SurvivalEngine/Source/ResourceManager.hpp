#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <string>

#include <glad/glad.h>

#include "Renderer/Shader.hpp"
#include "Renderer/Texture2D.hpp"


// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined.
class ResourceManager
{
public:
    // Resource Storage
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;

    // Shaders
    static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    static Shader GetShader(std::string name);
    
    // Textures
    static Texture2D LoadTexture(const char* file, std::string name, bool alpha);
    static Texture2D GetTexture(std::string name);
    
    static void Clear();

private:
    static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    static Texture2D loadTextureFromFile(const char* file, bool alpha);
};

#endif