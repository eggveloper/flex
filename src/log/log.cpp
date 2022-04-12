#include "log.hpp"

#include <cstdio>
#include <cstdarg>

namespace flex {
namespace log {

constexpr LogLevel loglevels[] {
    {"FATAL", "31;1"},
    {"ERROR", "31"},
    {"WARN ", "34"},
    {"IMP  ", "38"},
    {"MSG  ", ""},
    {"DBG2 ", ""},
    {"DBG1 ", ""},
    {"DBG0 ", ""}
};

template<int lvl>
void log(const char* fmt, ...) {
	const char* name = loglevels[lvl].name;
	const char* col = loglevels[lvl].col;

	printf("\x1b[%sm%s\x1b[m ", col, name);

	va_list vl;
	va_start(vl, fmt);
	vprintf(fmt, vl);
	va_end(vl);

    printf("\n");

    // TODO: Store messages in an array which can be read by the engine to then be rendered in an overlay
}

} // namespace log
} // namespace flex
