#ifndef _DEBUGGING_HPP_
#define _DEBUGGING_HPP_

#include <stdio.h>

namespace base {

void print_stack_trace(FILE *fp = stderr) __attribute__((noinline)); 


} // namespace base


#endif
