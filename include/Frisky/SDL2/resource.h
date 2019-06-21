#ifndef FRISKY_SDL2_RESOURCE_H_
#define FRISKY_SDL2_RESOURCE_H_

#include <utility>

namespace frisky::sdl2 {
  template<class RawPointer, class Handle>
  class Resource {
  protected:
    const Handle resource;
  public:
    Resource(Handle resource);
    virtual ~Resource() = 0;

    const RawPointer get() const;
    const bool       has() const;
  };

  template<typename RawPointer, typename Handle>
  inline Resource<RawPointer, Handle>::Resource(Handle resource)
    : resource(std::move(resource)) {

  }

  template<typename RawPointer, typename Handle>
  inline Resource<RawPointer, Handle>::~Resource() {}

  template<typename RawPointer, typename Handle>
  inline const RawPointer Resource<RawPointer, Handle>::get() const {
    return this->has()
      ? this->resource.value().get()
      : nullptr;
  }

  template<typename RawPointer, typename Handle>
  inline const bool Resource<RawPointer, Handle>::has() const {
    return this->resource.has_value()
      ? this->resource.value().get() != nullptr
      : false;
  }
}

#endif  // FRISKY_SDL2_RESOURCE_H_
