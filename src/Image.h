#pragma once
#include "Core.h"

enum ImageFormat {
    R,
    RG,
    RGB,
    RGBA,
};

class Image {
    public:
        Image(uint32_t width, uint32_t height, ImageFormat format);
        ~Image();

        void LoadTextureFromFIle(const char* path);

        // Getters
        inline uint32_t GetWidth() const { return m_width; }
        inline uint32_t GetHeight() const { return m_height; }
        inline uint32_t* GetData() const { return m_data; }
        inline GLuint* GetImageID() { return &m_ID; }
        // Setters
        void SetWidth(uint32_t width) { m_width = width; } 
        void SetHeight(uint32_t height) { m_height = height; }
        void SetData(uint32_t* data) {m_data = data; GenerateImage(); }
        GLuint m_ID = 0;
    private:
        void GenerateImage();
        ImageFormat m_format = ImageFormat::RGBA;

        uint32_t* m_data = nullptr;
        uint32_t m_width = 0;
        uint32_t m_height = 0;
};