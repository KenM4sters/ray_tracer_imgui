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
        Image(uint32_t width, uint32_t height, ImageFormat format, uint32_t* sceneData);
        ~Image();


        // Getters
        inline const uint32_t GetWidth() const { return m_width; }
        inline const uint32_t GetHeight() const { return m_height; }
        inline const char* GetData() const { return m_data; }
        // Setters
        void SetWidth(uint32_t width) { m_width = width; } 
        void SetHeight(uint32_t height) { m_height = height; }
        void SetData(char* data) {m_data = data; }
    private:
        char* m_data;
        uint32_t m_width;
        uint32_t m_height;
};