#ifndef FRISKY_SDL2_MAKE_RESOURCE_H_
#define FRISKY_SDL2_MAKE_RESOURCE_H_

#include <memory>
#include <optional>

namespace frisky::sdl2::internal {
  template<typename Creator, typename Destroyer, typename... Arguments>
  auto make_resource(
    const Creator   ctor,
    const Destroyer dtor,
    Arguments&&...  args
  ) {
    auto resource = ctor(std::forward<Arguments>(args)...);

    using resource_t = std::decay_t<decltype(*resource)>;
    using return_t   = std::unique_ptr<resource_t, decltype(dtor)>;

    return std::optional<return_t>{ return_t(resource, dtor) };
  }
}

#endif  // FRISKY_SDL2_MAKE_RESOURCE_H_
