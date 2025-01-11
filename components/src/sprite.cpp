#include "../include/sprite.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

components::image2d components::gen_img(std::string path) {
    image2d n_img;

    int width, height, nrChannels;

    n_img.pixels = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    n_img.width = width;
    n_img.height = height;
    n_img.nrChannels = nrChannels;

    return n_img;
}

components::sprite::sprite() {}
components::sprite::~sprite() {}

components::sprite::sprite(int width, int height) {
    this->img.width = width;
    this->img.height = height;
    this->img.pixels = new unsigned char[width * height * 4];
    for (int i = 0; i < width * height * 4; i++)
        this->img.pixels[i] = 255;
    this->generateGpuTexture();
}

components::sprite::sprite(int width, int height, unsigned char* pixels) {
    this->img.width = width;
    this->img.height = height;
    this->img.pixels = pixels;
    this->generateGpuTexture();
}

void components::sprite::generateGpuTexture() {
    glCreateTextures(GL_TEXTURE_2D, 1, &gpuTexture);

    glTextureParameteri(gpuTexture, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTextureParameteri(gpuTexture, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTextureParameteri(gpuTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(gpuTexture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureStorage2D(gpuTexture, 1, GL_RGBA8, img.width, img.height);
    glTextureSubImage2D(gpuTexture, 0, 0, 0, img.width, img.height, GL_RGBA, GL_UNSIGNED_BYTE, img.pixels);
}

void components::sprite::updateGpuTexture() {
    glTextureSubImage2D(gpuTexture, 0, 0, 0, img.width, img.height, GL_RGBA, GL_UNSIGNED_BYTE, img.pixels);
}

void components::sprite::from_img(image2d n_img) {
    if (this->img.width == n_img.width && this->img.height == n_img.height) {
        this->img = n_img;
        this->updateGpuTexture();
    }
    else {
        this->img = n_img;
        this->generateGpuTexture();
    }
}

components::image2d components::sprite::from_png(std::string path) {
    int width, height, nrChannels;

    image2d n_img;

    n_img.pixels = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    n_img.width = width;
    n_img.height = height;
    n_img.nrChannels = nrChannels;

    if (this->img.width == width && this->img.height == height) {
        this->img = n_img;
        this->updateGpuTexture();
    }
    else {
        this->img = n_img;
        this->generateGpuTexture();
    }

    return n_img;
}