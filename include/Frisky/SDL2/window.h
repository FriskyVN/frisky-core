#ifndef FRISKY_SDL2_WINDOW_H_
#define FRISKY_SDL2_WINDOW_H_

#include <SDL2/SDL_video.h>

#include "Frisky/SDL2/make_resource.h"
#include "Frisky/log.h"
#include "Frisky/types.h"

namespace frisky::sdl2 {
  using window_rptr_t = SDL_Window*;

  namespace internal {
    using window_ctor_t = decltype(&SDL_CreateWindow);
    using window_dtor_t = decltype(&SDL_DestroyWindow);
    using window_uptr_t = std::unique_ptr<SDL_Window, window_dtor_t>;
    using window_hdlr_t = std::optional<window_uptr_t>;
  }

  class Window final {
  private:
    const internal::window_hdlr_t window;
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

    const window_rptr_t get() const;
    const bool has() const;

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
  ) : window(
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

  inline const window_rptr_t Window::get() const {
    return this->has()
      ? this->window.value().get()
      : nullptr;
  }

  inline const bool Window::has() const {
    return this->window.has_value()
      ? this->window.value().get() != nullptr
      : false;
  }

  inline void Window::setTitle(const char* title) const {
    const window_rptr_t w = this->get();

    if (w != nullptr) {
      FRISKY_LOG_INFO("Set title of window to: %s", title);
      return SDL_SetWindowTitle(w, title);
    }

    FRISKY_LOG_ERROR("Cannot set title of nullptr SDL_Window*");
  }
}

#endif  // FRISKY_SDL2_WINDOW_H_
