#ifndef _UTIL_FPS_H
#define _UTIL_FPS_H

namespace flex {
namespace util {

class FrameCounter {
public:
    /** to be called each time a frame has been completed */
    void frame();
    
    /** auto-updated to always contain the current fps value */
    float fps;

    /** contains the number of completed frames */
    unsigned count;

private:
    float frame_count_weighted;
    float frame_length_sum_weighted;
    int lastframe_timestamp;
};

} // namespace util
} // namespace flex

#endif