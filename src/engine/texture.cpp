#include <SDL2/SDL.h>
#include <stdio.h>

#include "texture.hpp"
#include "../log/log.hpp"

namespace flex {
namespace engine {

Texture::Texture(const char* filename) {
    SDL_Surface* surface;
    GLuint textureid;
    int mode;

    surface = SDL_LoadBMP(filename);

    if (!surface) {
        log::warn("failed generating texture %s\n", filename);

        return;
    } else {
        log::msg("loaded texture from '%s'\n", filename);
    }

    // glTexImage2D format determination
    if (surface->format->BytesPerPixel == 3) {
        mode = GL_RGB;
    } else if (surface->format->BytesPerPixel == 4) {
        mode = GL_RGBA;
    } else {
        return;
    }

    this->w = surface->w;
    this->h = surface->h;

    glGenTextures(1, &textureid);
    glBindTexture(GL_TEXTURE_2D, textureid);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surface);

    this->gl_id = textureid;
}

Texture::~Texture() {
    // TODO: Free OpenGL resources..
}

void Texture::draw(int x, int y) {
    glBindTexture(GL_TEXTURE_2D, gl_id);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    glTexCoord2i(0, 1);
    glVertex3f(x, y, 0);

    glTexCoord2i(1, 1);
    glVertex3f(x + w, y, 0);

    glTexCoord2i(1, 0);
    glVertex3f(x + w, y + h, 0);

    glTexCoord2i(0, 0);
    glVertex3f(x, y + h, 0);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

} //namespace engine
} //namespace flex
