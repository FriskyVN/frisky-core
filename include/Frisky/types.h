#ifndef FRISKY_TYPES_H_
#define FRISKY_TYPES_H_

#include <cstddef>
#include <cstdint>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;

namespace frisky {
  using size_t     = std::size_t;
  using uintptr_t  = std::uintptr_t;
  using uint32_t   = std::uint32_t;
  using sdlflags_t = std::uint32_t;

  using window_rptr_t   = SDL_Window*;
  using renderer_rptr_t = SDL_Renderer*;
  using texture_rptr_t  = SDL_Texture*;
  using rect_rptr_t     = SDL_Rect*;
}

#endif  // FRISKY_TYPES_H_
