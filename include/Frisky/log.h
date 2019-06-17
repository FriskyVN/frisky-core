#ifndef FRISKY_LOG_H_
#define FRISKY_LOG_H_

#include <cstdio>

#ifdef DEBUG
  namespace frisky::log::internal {
    enum LOG_LEVEL {
      LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR, LOG_FATAL
    };
  }

  #define FRISKY_LOG(level, fmt, ...) \
    do { \
      if (DEBUG) { \
        fprintf(stderr, "%s\r\n    [%s][Line %d]: " fmt "\r\n\r\n", \
          __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__); \
      } \
    } while (false)

  #define FRISKY_LOG_DEBUG(fmt, ...)   \
    FRISKY_LOG(frisky::log::internal.LOG_DEBUG,   fmt, __VA_ARGS__)
  #define FRISKY_LOG_INFO(fmt, ...)    \
    FRISKY_LOG(frisky::log::internal.LOG_INFO,    fmt, __VA_ARGS__)
  #define FRISKY_LOG_WARNING(fmt, ...) \
    FRISKY_LOG(frisky::log::internal.LOG_WARNING, fmt, __VA_ARGS__)
  #define FRISKY_LOG_ERROR(fmt, ...)   \
    FRISKY_LOG(frisky::log::internal.LOG_ERROR,   fmt, __VA_ARGS__)
  #define FRISKY_LOG_FATAL(fmt, ...)   \
    FRISKY_LOG(frisky::log::internal.LOG_FATAL,   fmt, __VA_ARGS__)
#else
  #define FRISKY_LOG_DEBUG(...)
  #define FRISKY_LOG_INFO(...)
  #define FRISKY_LOG_WARNING(...)
  #define FRISKY_LOG_ERROR(...)
  #define FRISKY_LOG_FATAL(...)
#endif

#endif  // FRISKY_LOG_H_
