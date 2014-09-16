#include "logger.hpp"
#include <pthread.h>


namespace base {

static pthread_mutex_t log_rmutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

const char *ll_header[LL_ALL]{
  "D",
  "I",
  "W",
  "E",
  "F"
};


LogManager& global_lm(){
  static LogManager lm;
  return lm;
}

template<typename T>
NullLog NullLog::operator<<(T a) {
  return NullLog();
}


NullLog NullLog::operator<<(const char* a) {
  return NullLog();
}


Log::Log(const Log& other) :
  lc(other.lc) {
  lc->ref ++;
}
  
Log::Log(LogManager *lm_in, int level_in, const char *file_in, const char *func_in, int line_in){
  lc = new struct log_content();
  lc->lm = lm_in;
  lc->level = level_in;
  lc->file = file_in;
  lc->func = func_in;
  lc->line = line_in;
}

template<typename T>
Log& Log::operator<<(T a) {
  if (lc->ss == nullptr) {
    lc->ss = new std::stringstream;
  }
  *(lc->ss) << a;
  return *this;
}



Log& Log::operator<<(const char *a) {
  if (lc->ss == nullptr) {
    lc->ss = new std::stringstream;
  }

  *(lc->ss) << a;
  return *this;
}

void Log::log_console(const char *fmt, ...) {
  va_list va;
  va_start(va, fmt);
  char now_str[TIME_NOW_STR_SIZE];
  time_now_str(now_str);
  
  pthread_mutex_lock(&log_rmutex);
  printf("%s %s %s %s:%d | ", ::base::ll_header[lc->level], now_str, lc->file, lc->func, lc->line);
  vprintf(fmt, va);
  printf("\n");
  pthread_mutex_unlock(&log_rmutex);
   
  va_end(va);

}


void Log::log_file(const char *fmt, ...) {
  //TODO

}


Log::~Log() {
  lc->ref --;
  if(lc->ref == 0) {
    if (lc->ss != nullptr) {
      log_console("%s", lc->ss->str().c_str());
      delete lc->ss;
    }
    delete lc;
  }
}


LogManager::LogManager() {
  log_level = LL_DEBUG;
  log_to_console = true;
  log_file = "";
}


void LogManager::set_log_level(int level){
  log_level = level;
}

int LogManager::get_log_level(){
  return log_level;
}

void LogManager::set_log_to_console(bool ltc) {
  log_to_console = ltc;
}

bool LogManager::get_log_to_console(){
  return log_to_console;
}

Log LogManager::new_log(int level, const char *file, const char *func, int line) {
  return Log(this, level, file, func, line);

}



} // namespace base

