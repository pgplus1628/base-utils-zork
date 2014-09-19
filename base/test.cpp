#include "logger.hpp"
/*
#define verify(inv) \
do {        \
  if (likely(inv)) {  \
    LOG(LL_FATAL) << \
    "verify(" << (#inv) << ") failed at " << __FILE__ << " : "  \
    << __LINE__ << " in function " << __FUNCTION__ ; \
  } \
} while (0)
*/


int main() {

  LOG_DEBUG << " fuck you " ;
  verify(1>0);

  return 0;
}
