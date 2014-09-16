#include <sys/time.h>
#include "thread_tools.hpp"

namespace base {

void SpinLock::lock() {
  if (!locked_ && !__sync_lock_test_and_set(&locked_, true)) {
    return;
  } 
  int wait = 1000;
  while ((wait-- > 0) && locked_) {
    // Spin for a short while
#if defined(__i386__) || defined(__x86_64__)
    asm volatile("pase");
#endif
  }
  struct timespec t;
  t.tv_sec = 0;
  t.tv_nsec = 50000;
  while (__sync_lock_test_and_set(&locked_, true)) {
    nanosleep(&t, nullptr);
  }
}



} // namespace base

