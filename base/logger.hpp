#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <sstream>
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include "misc.hpp"
#include "debugging.hpp"

/**
 * 1. Log output constraint ? 
 * log will output if and only if 
 *    * log_level >= LL_OUTPUT  : at compile time
 *    * log_level >= global_lm.get_log_level() : at run time 
 *
 * 2. When will log be flushed ?
 * log will flush only when the ~Log() is called.
 *
 */

#define LL_DEBUG 0
#define LL_INFO  1
#define LL_WARN  2
#define LL_ERROR 3
#define LL_FATAL 4
#define LL_ALL   5

/* LL_OUTPUT hard output level */
#ifndef LL_OUTPUT 
#define LL_OUTPUT LL_DEBUG
#endif

#define LOG(lvl) \
  if (lvl >= ::base::global_lm().get_log_level()) ::base::log_dispatch<(lvl >= LL_OUTPUT)>::exec(lvl, __FILE__, __func__, __LINE__)

#define LOG_INFO  LOG(LL_INFO)
#define LOG_WARN  LOG(LL_WARN)
#define LOG_ERROR LOG(LL_ERROR)
#define LOG_FATAL LOG(LL_FATAL)


#ifndef likely
#define likely(x) __builtin_expect(!!(x), 1)
#endif // likely


#ifndef unlikely
#define unlikely(x) __builtin_expect(!!(x), 0)
#endif // unlikely


/**
 * Use assert() when the test is only intended for debugging.
 * Use verify() when the test is crucial for both debug and release library.
 */

#ifndef NDEBUG
#define verify(inv) \
  !(unlikely(!(inv))) ? void(0) : LOG(LL_FATAL) << \
  "verify(" << (#inv) << ") failed at " << __FILE__ << " : " << __LINE__ << " in function " << __FUNCTION__
#else 
#define verify(inv) assert(inv)
#endif  


namespace base {

extern const char *ll_header[LL_ALL];

/*
class BaseLog {
  public : 
  template<typename T>
  virtual BaseLog& operator<<(T);
  virtual BaseLog& operator<<(const char *);
};
*/


class NullLog { 
  public : 
  template<typename T>
  NullLog operator<<(T);
  NullLog operator<<(const char *);
};


class LogManager;

LogManager& global_lm();

class Log {
  Log operator= (const Log&) = delete;

  public :
  Log(const Log& other);
  Log(LogManager *lm_in, int level_in, const char *file_in, const char *func_in, int line_in);
  template<typename T>  
  Log& operator<< (T a);
  Log& operator<< (const char *a);
  void log_console(const char *fmt, ...);
  void log_file(const char *fmt, ...);
  ~Log();

  private :
  struct log_content {
    LogManager *lm;
    std::stringstream *ss;
    int level;
    const char *file;
    const char *func;
    int line;
    int ref;
    log_content() : lm(nullptr), ss(nullptr), level(0), file(nullptr), func(nullptr), line(0), ref(1) {
    }
  };

  struct log_content *lc;



};


/*
template<bool dostuff>
struct log_dispatch {};

template<>
struct log_dispatch<true> {
  inline static Log& exec(int level, const char *file, const char *func, int line) {
    if (global_lm().get_log_level() <= level ) {
      return global_lm().new_log(level, file, func, line);
    } else  {
      return NullLog();
    }
  }
};


template<>
struct log_dispatch<false> {
  inline static NullLog exec(const char *file, const char*func, int line) {
    return NullLog();
  }
};
*/



class LogManager {
  LogManager(const LogManager&) = delete;
  LogManager operator= (const LogManager&) = delete;

  public :
  LogManager();
  void set_log_level(int lvl); /* soft log level, may change at run time */
  int get_log_level();
  void set_log_to_console(bool ltc);
  bool get_log_to_console();
  
  Log new_log(int level, const char *file, const char *func, int line);

  private : 
  int log_level;
  bool log_to_console;
  std::string log_file;

};

template<bool dostuff>
struct log_dispatch {};

template<>
struct log_dispatch<true> {
  inline static Log exec(int level, const char *file, const char *func, int line) {
    return global_lm().new_log(level, file, func, line);
  }
};


template<>
struct log_dispatch<false> {
  inline static NullLog exec(int level, const char *file, const char*func, int line) {
    return NullLog();
  }
};




} // namespace base

#endif
