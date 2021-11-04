#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>

enum class Filtering
{
    NearestNeighbor,
    Bilinear
};

class Texture2D
{
public:
    // Holds the Id of the texture object, used for all texture operations to reference to this particlar texture
    unsigned int Id;

    // Texture image dimensions
    unsigned int Width; // Pixel width
    unsigned int Height; // Pixel height

    // Texture Format
    unsigned int Internal_Format; // format of texture object
    unsigned int Image_Format; // format of loaded image

    // Texture configuration
    unsigned int Wrap_S; // wrapping mode on S axis
    unsigned int Wrap_T; // wrapping mode on T axis
    unsigned int Filter_Min; // filtering mode if texture pixels < screen pixels
    unsigned int Filter_Max; // filtering mode if texture pixels > screen pixels

    // Constructors
    Texture2D();

    // generates texture from image data
    void Generate(unsigned int width, unsigned int height, unsigned char* data);

    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
};

#endif