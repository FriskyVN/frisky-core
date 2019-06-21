#ifndef FRISKY_SDL2_WINDOW_H_
#define FRISKY_SDL2_WINDOW_H_

#include <SDL2/SDL_video.h>

#include "Frisky/SDL2/forward_sdl_call.h"
#include "Frisky/SDL2/make_resource.h"
#include "Frisky/SDL2/resource.h"
#include "Frisky/log.h"
#include "Frisky/types.h"

namespace frisky::sdl2 {
  namespace internal {
    using window_ctor_t = decltype(&SDL_CreateWindow);
    using window_dtor_t = decltype(&SDL_DestroyWindow);
    using window_uptr_t = std::unique_ptr<SDL_Window, window_dtor_t>;
    using window_hdlr_t = std::optional<window_uptr_t>;
  }

  class Window final
    : public Resource<window_rptr_t, internal::window_hdlr_t> {
  public:
    Window(
      const char* title,
      const int x,
      const int y,
      const int w,
      const int h,
      const frisky::sdlflags_t flags,
      const internal::window_ctor_t ctor,
      const internal::window_dtor_t dtor
    );

    ~Window();

    void setTitle(const char*) const;
  };

  inline Window::Window(
    const char* title,
    const int x = SDL_WINDOWPOS_UNDEFINED,
    const int y = SDL_WINDOWPOS_UNDEFINED,
    const int w = 1280,
    const int h = 720,
    const frisky::sdlflags_t flags = SDL_WINDOW_SHOWN,
    const internal::window_ctor_t ctor = SDL_CreateWindow,
    const internal::window_dtor_t dtor = SDL_DestroyWindow
  ) : Resource(
      frisky::sdl2::internal::make_resource(
        ctor, dtor, title, x, y, w, h, flags
      )
    ) {
    if (this->has()) {
      FRISKY_LOG_INFO("Created SDL_Window");
    } else {
      FRISKY_LOG_ERROR("Failed to create SDL_Window");
      FRISKY_LOG_ERROR("SDL Error: %s", SDL_GetError());
    }
  }

  inline Window::~Window() {
    FRISKY_LOG_INFO("Destroyed SDL_Window");
  }

  inline void Window::setTitle(const char* title) const {
    return frisky::sdl2::internal::forward_sdl_call(
      this->get(),
      &SDL_SetWindowTitle,
      title
    );
  }
}

#endif  // FRISKY_SDL2_WINDOW_H_
