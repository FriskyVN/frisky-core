#ifndef FRISKY_SDL2_FORWARD_SDL_CALL_H_
#define FRISKY_SDL2_FORWARD_SDL_CALL_H_

#include <utility>

namespace frisky::sdl2::internal {
  template<typename Pointer, typename Callable, typename... Arguments>
  auto forward_sdl_call(
    const Pointer  p,
    const Callable fn,
    Arguments&&... args
  ) {
    if (p == nullptr) {
      FRISKY_LOG_WARNING("Calling an SDL function on a nullptr");
    }

    return fn(p, std::forward<Arguments>(args)...);
  }
}

#endif  // FRISKY_SDL2_FORWARD_SDL_CALL_H_
