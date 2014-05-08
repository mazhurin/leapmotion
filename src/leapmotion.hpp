#include "core.hpp"
#include "v8_core.hpp"
#include "async_queue.hpp"
#include "events.hpp"
#include "runtime.hpp"
#include "v8_main_loop.hpp"

#include <iostream>
#include <vector>

#if OS(WINDOWS)
//	#pragma warning ( disable : 4251 )
#if defined(LEAPMOTION_EXPORTS)
#define LEAPMOTION_API __declspec(dllexport)
#else
#define LEAPMOTION_API __declspec(dllimport)
#endif
#elif __GNUC__ >= 4
# define LEAPMOTION_API __attribute__((visibility("default")))
#else
#define LEAPMOTION_API // nothing, symbols in a shared library are exported by default
#endif

#if OS(WINDOWS)
#elif OS(LINUX)
#endif
