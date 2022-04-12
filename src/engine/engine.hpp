#ifndef _ENGINE_ENGINE_HPP_
#define _ENGINE_ENGINE_HPP_

#include <SDL2/SDL.h>

namespace flex {
namespace engine {

using draw_method_ptr = void(*)();
using input_handler_ptr = void(*)(SDL_Event* e);

/**
 * @brief engine initialization method.
 *
 * opens a window and initializes the OpenGL context.
 *
 * @param draw_method pointer to the rendering method, which is called each iteration of the main loop
 * @param input_handler pointer to the input handler, which is called each time an input event is registered
 */
void init(draw_method_ptr draw_method, input_handler_ptr input_handler);

/**
 * @brief engine de-initialization method.
 *
 * cleanly shutdowns the application.
 *
 */
void destroy();

/**
 * @brief main loop method.
 *
 * terminates when running is set to false.
 */
void loop();

/**
 * @brief internal method that is automatically called whenever the window is resized.
 *
 * @param w width
 * @param h height
 */
void engine_window_resized(unsigned w, unsigned h);

/**
 * @brief internal method that is called whenever an input event is registered
 *
 * @param e input event
 */
void engine_input_handler(SDL_Event* e);

/**
 * @brief SDL window of the engine.
 */
extern SDL_Window* window;

/**
 * @brief set to false to stop the engine.
 */
extern bool running;

} //namespace engine
} //namespace flex

#endif
