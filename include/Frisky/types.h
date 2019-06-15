#ifndef FRISKY_TYPES_H_
#define FRISKY_TYPES_H_

#include <cstddef>
#include <cstdint>

struct SDL_Renderer;
struct SDL_Window;

namespace Frisky {
  typedef std::size_t    size_t;
  typedef std::uintptr_t uintptr_t;
  typedef std::uint32_t  sdl_flags_t;

  typedef SDL_Window*    window_ptr;
  typedef SDL_Renderer*  renderer_ptr;
}

#endif  // FRISKY_TYPES_H_
