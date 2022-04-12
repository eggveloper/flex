#include "fps.hpp"
#include <cmath>
#include <SDL2/SDL.h>

namespace flex {
namespace util {

void FrameCounter::frame() {
    unsigned frame_timestamp = SDL_GetTicks();
    unsigned frame_length = frame_timestamp - lastframe_timestamp;

    if (frame_length <= 1) {
        frame_length = 1;
    }

    lastframe_timestamp = frame_timestamp;

    float previous_frames_weight_adjustment = exp((-0.001 / 0.5) * frame_length);

    frame_length_sum_weighted *= previous_frames_weight_adjustment;
    frame_length_sum_weighted += frame_length;

    frame_count_weighted *= previous_frames_weight_adjustment;
    frame_count_weighted += 1;

    if (frame_length_sum_weighted <= 0 || frame_count_weighted <= 0) {
        fps = 0.0;
    } else {
        fps = 1000.0 * frame_count_weighted / frame_length_sum_weighted;
    }

    count += 1;
}

} // namespace util
} // namespace flex