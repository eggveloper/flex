#include "engine.hpp"
#include "texture.hpp"
#include "../log/log.hpp"

#include <stdio.h>
#include <GL/gl.h>

namespace flex {
namespace engine {

// global engine variables; partially accesible via engine.hpp

SDL_GLContext glcontext;
SDL_Window *window;

draw_method_ptr draw_method;
input_handler_ptr input_handler;

bool running;

void init(draw_method_ptr draw_method, input_handler_ptr input_handler) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        log::fatal("SDL Initialization: %s\n", SDL_GetError());

        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow("flex", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

    if (window == nullptr) {
        log::fatal("SDL Window Creation: %s\n", SDL_GetError());

        return;
    }

    glcontext = SDL_GL_CreateContext(window);

    // vsync on
    SDL_GL_SetSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    engine::draw_method = draw_method;
    engine::input_handler = input_handler;
}

void destroy() {
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void engine_window_resized(unsigned w, unsigned h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);

    // left, right, bottom, top, nearVal, farVal
    glOrtho(0, w, 0, h, 9001, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    log::dbg("engine window has been resized to %ux%u\n", w, h);
}

void engine_input_handler(SDL_Event* e) {
    switch (e->type) {
    case SDL_WINDOWEVENT:
        switch (e->window.event) {
        case SDL_WINDOWEVENT_RESIZED:
            engine_window_resized(e->window.data1, e->window.data2);

            break;
        }

        break;
    }
}

void loop() {
    running = true;

    while (running) {
        SDL_Event e;

        if (SDL_PollEvent(&e)) {
            engine_input_handler(&e);
            input_handler(&e);
        }

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        draw_method();

        SDL_GL_SwapWindow(window);
    }
}

} // namespace engine
} // namespace flex
