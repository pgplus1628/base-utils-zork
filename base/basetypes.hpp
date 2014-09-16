#ifndef _BASETYPES_HPP_
#define _BASETYPES_HPP_

namespace base { 


class NoCopy {
  NoCopy(const NoCopy&) = delete;
  NoCopy& operator= (const NoCopy&) = delete;  
  protected : 
  NoCopy() {}
  virtual ~NoCopy() = 0;
};
inline NoCopy::~NoCopy() {}


} // namespace base

#endif
