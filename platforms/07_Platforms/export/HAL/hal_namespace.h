/**
 * @file hal_namespace.h
 * 
 */
#ifndef BM_PLATFORM_HAL_NAMESPACE_H_
#define BM_PLATFORM_HAL_NAMESPACE_H_

#define NAMESPACE_HAL_BEGIN  \
  namespace bm { \
  namespace hal {
#define NAMESPACE_HAL_END \
  } \
  }
#define USING_NAMESPACE_HAL(n) using m = bm::hal

#endif /* BM_PLATFORM_HAL_NAMESPACE_H_ */
