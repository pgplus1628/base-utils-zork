#ifndef _WORKER_FIBER_HPP_
#define _WORKER_FIBER_HPP_

#include "thread_tools.hpp"
#include <ucontext.h>
#include <unistd.h>
#include <bitset>

namespace base { 
namespace xfiber {

class worker_fiber { 

  public :  
  typedef std::bitset<64> affinity_t;

  private : 
  enum state_t {
    READY = 0;
    RUNNING,
    WAITING,
    TERMINATED
  };

  SpinLock        lock_;
  fiber_manager * fib_mgr_;
  ucontext_t    * context_;
  void          * stack_;
  size_t          id_;
  affinity_t      aff_;
  std::vector<unsigned char> aff_list_;
  void          * fls_; // fiber local storage
  fiber         * next_;
  state_t         state_;
  bool            priority_; // if set, this fiber will  be placed
                             // at the head of the queue.
  
  
  


};









} // namespace xfiber
} // namespace base

#endif
