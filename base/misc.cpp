#include "misc.hpp"

namespace base { 

void time_now_str(char *now) {
  time_t t_now = time(nullptr);
  struct tm stm_now ;
  localtime_r(&t_now, &stm_now);

  char raw_now[80];
  strftime(raw_now, 80, "%Y-%m-%d %H:%M:%S", &stm_now);
  
  struct timeval tmv_now;
  gettimeofday(&tmv_now, nullptr);
  int now_ms = tmv_now.tv_usec / 1000;
  sprintf(now, "%s:%d", raw_now, now_ms);
}

std::string getline(FILE *fp, char delim) {
  char *buf = nullptr;
  size_t n = 0;
  ssize_t n_read = ::getdelim(&buf, &n, delim, fp);
  if (n_read > 0 && buf[n_read - 1] == delim) {
    n_read --;
  }
  std::string line(buf, n_read);
  free(buf);
  return line;
}


} // namespace base
