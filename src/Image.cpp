#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <Stbi_image/stb_image.h>

Image::Image(uint32_t width, uint32_t height, ImageFormat format)
    : m_width(width), m_height(height), m_format(format)
{}

Image::~Image() {
    glDeleteTextures(1, &m_ID);
}

void Image::GenerateImage() 
{
    // OpenGL version - will enventually be graphics API agnostic.

    GLuint format;
    if(m_format == ImageFormat::RGBA) format = GL_RGBA;
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, this->m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_width, 0, format, GL_UNSIGNED_BYTE, m_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Image::LoadTextureFromFIle(const char* path)
{
    stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, &m_ID); 

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width , &height, &nrChannels, 0);
    m_height = height;
    m_width = width;

    GLuint format;
    if(m_format == ImageFormat::RGBA) format = GL_RGBA;

    if(data)
    {   
        glBindTexture(GL_TEXTURE_2D, this->m_ID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "ERROR::OpenGLTexture::Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
}

