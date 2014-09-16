#ifndef _THREAD_TOOLS_HPP_
#define _THREAD_TOOLS_HPP_

#include "../base/basetypes.hpp"


namespace base { 

class Lockable : public NoCopy {
  public :
  virtual void lock() = 0;
  virtual void unlock() = 0;
};


class SpinLock : public Lockable {
  public : 
  SpinLock() : locked_(false) {}
  void lock();
  void unlock() {
    __sync_lock_release(&locked_);
  }

  private :
  volatile bool locked_ __attribute__((aligned(64)));
};



} // namespace base
#endif
