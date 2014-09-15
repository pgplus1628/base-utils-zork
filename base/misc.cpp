#include "misc.hpp"

void time_now_str(char *now) {
  time_t t_now = time(NULL);
  struct tm stm_now ;
  localtime_r(&t_now, &stm_now);

  char raw_now[80];
  strftime(raw_now, 80, "%Y-%m-%d %H:%M:%S", &stm_now);
  
  struct timeval tmv_now;
  gettimeofday(&tmv_now, NULL);
  int now_ms = tmv_now.tv_usec / 1000;
  sprintf(now, "%s:%d", raw_now, now_ms);
}
