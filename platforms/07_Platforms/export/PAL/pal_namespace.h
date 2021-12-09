/**
 * @file pal_namespace.h
 * 
 */
#ifndef BM_PLATFORM_PAL_NAMESPACE_H_
#define BM_PLATFORM_PAL_NAMESPACE_H_

#define NAMESPACE_PAL_BEGIN  \
  namespace bm { \
  namespace pal {
#define NAMESPACE_PAL_END \
  } \
  }
#define USING_NAMESPACE_PAL(n) using m = bm::pal

#endif /* BM_PLATFORM_PAL_NAMESPACE_H_ */
