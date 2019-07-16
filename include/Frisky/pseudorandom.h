#ifndef FRISKY_PSEUDORANDOM_H_
#define FRISKY_PSEUDORANDOM_H_

/**
 * The pseudorandom number generator in this class is Based on Bob Jenkins's
 * Small Noncryptographic PRNG, which has been released to the public domain.
 * See: http://www.burtleburtle.net/bob/rand/smallprng.html
 */

#include <ctime>

#include "Frisky/types.h"

namespace frisky {
  namespace internal {
    struct context {
      uint32_t a;
      uint32_t b;
      uint32_t c;
      uint32_t d;
    };

    constexpr const uint32_t rot(const uint32_t x, const uint32_t k) {
      return (x << k) | (x >> (32 - k));
    }
  }

  class PseudoRandom final {
  public:
    PseudoRandom();
    PseudoRandom(const uint32_t seed);

    const uint32_t next_value();
    const uint32_t in_range(const uint32_t min, const uint32_t max);

  private:
    internal::context ctx;
  };

  inline PseudoRandom::PseudoRandom()
    : PseudoRandom(static_cast<uint32_t>(std::time(nullptr))) {

  }

  inline PseudoRandom::PseudoRandom(const uint32_t seed)
    : ctx({ 0xf1ea5eed, seed, seed, seed }) {
    for (int i = 0; i <= 20; ++i) {
      this->next_value();
    }
  }

  inline const uint32_t PseudoRandom::next_value() {
    const uint32_t e = this->ctx.a - internal::rot(this->ctx.b, 27);

    this->ctx.a = this->ctx.b ^ internal::rot(this->ctx.c, 17);
    this->ctx.b = this->ctx.c + this->ctx.d;
    this->ctx.c = this->ctx.d + e;
    this->ctx.d = this->ctx.a + e;

    return this->ctx.d;
  }

  inline const uint32_t PseudoRandom::in_range(const uint32_t min, const uint32_t max) {
    return min + (this->next_value() % (max - min + 1));
  }
}

#endif  // FRISKY_PSEUDORANDOM_H_
