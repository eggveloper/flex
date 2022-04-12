#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP

#include "GL/gl.h"

namespace flex {
namespace engine {

class Texture {
public:
    int w;
    int h;

    Texture(const char* filename);
    ~Texture();

    void draw(int posx, int posy);
private:
    GLuint gl_id;
};

} // namespace engine
} // namespace flex

#endif
