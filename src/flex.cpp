#include "flex.hpp"

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "engine/engine.hpp"
#include "engine/texture.hpp"
#include "log/log.hpp"
#include "util/fps.hpp"

namespace flex {

engine::Texture* gaben;
util::FrameCounter fpscounter;

void input_handler(SDL_Event* e) {
    if (e->type == SDL_QUIT) {
        engine::running = false;
    }
}

void draw_method() {
    gaben->draw(0, 0);

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    {
        glVertex3f(0, 0, 0);
        glVertex3f(0, 10, 0);
        glVertex3f(10, 10, 0);
        glVertex3f(10, 0, 0);
    }
    glEnd();

    fpscounter.frame();

    log::msg("fps: %f", fpscounter.fps);
}

int mainmethod() {
    engine::init(draw_method, input_handler);

    gaben = new engine::Texture("gaben.bmp");

    engine::loop();
    engine::destroy();

    return 0;
}

} // namespace flex

int main() {
    return flex::mainmethod();
}
