#ifndef FRISKY_SDL2_RENDERER_H_
#define FRISKY_SDL2_RENDERER_H_

#include <SDL2/SDL_video.h>

#include "Frisky/SDL2/forward_sdl_call.h"
#include "Frisky/SDL2/make_resource.h"
#include "Frisky/SDL2/resource.h"
#include "Frisky/log.h"
#include "Frisky/types.h"

namespace frisky::sdl2 {
  namespace internal {
    using renderer_ctor_t = decltype(&SDL_CreateRenderer);
    using renderer_dtor_t = decltype(&SDL_DestroyRenderer);
    using renderer_uptr_t = std::unique_ptr<SDL_Renderer, renderer_dtor_t>;
    using renderer_hdlr_t = std::optional<renderer_uptr_t>;
  }

  class Renderer final
    : public Resource<renderer_rptr_t, internal::renderer_hdlr_t> {
  public:
    Renderer(
      const frisky::window_rptr_t window,
      const int index,
      const frisky::sdlflags_t flags,
      const internal::renderer_ctor_t ctor,
      const internal::renderer_dtor_t dtor
    );

    ~Renderer();

    const int clear() const;
    const int copy(
      frisky::texture_rptr_t* texture,
      const frisky::rect_rptr_t* src,
      const frisky::rect_rptr_t* dest
    ) const;
    const void present() const;
  };

  inline Renderer::Renderer(
    const window_rptr_t window,
    const int index = -1,
    const frisky::sdlflags_t flags = SDL_RENDERER_ACCELERATED,
    const internal::renderer_ctor_t ctor = SDL_CreateRenderer,
    const internal::renderer_dtor_t dtor = SDL_DestroyRenderer
  ) : Resource(
      frisky::sdl2::internal::make_resource(
        ctor, dtor, window, index, flags
      )
    ) {
    if (this->has()) {
      FRISKY_LOG_INFO("Created SDL_Renderer");
    } else {
      FRISKY_LOG_ERROR("Failed to create SDL_Renderer");
      FRISKY_LOG_ERROR("SDL Error: %s", SDL_GetError());
    }
  }

  inline Renderer::~Renderer() {
    FRISKY_LOG_INFO("Destroyed SDL_Renderer");
  }

  inline const int Renderer::clear() const {
    return frisky::sdl2::internal::forward_sdl_call(
      this->get(),
      &SDL_RenderClear
    );
  }

  inline const int Renderer::copy(
    frisky::texture_rptr_t* texture,
    const frisky::rect_rptr_t* src,
    const frisky::rect_rptr_t* dest
  ) const {
    return frisky::sdl2::internal::forward_sdl_call(
      this->get(),
      &SDL_RenderCopy,
      reinterpret_cast<SDL_Texture*>(texture),
      reinterpret_cast<const SDL_Rect*>(src),
      reinterpret_cast<const SDL_Rect*>(dest)
    );
  }

  inline const void Renderer::present() const {
    return frisky::sdl2::internal::forward_sdl_call(
      this->get(),
      &SDL_RenderPresent
    );
  }
}

#endif  // FRISKY_SDL2_RENDERER_H_
