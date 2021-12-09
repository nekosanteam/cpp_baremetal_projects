/**
 * @file mal_namespace.h
 * 
 */
#ifndef BM_PLATFORM_MAL_NAMESPACE_H_
#define BM_PLATFORM_MAL_NAMESPACE_H_

#define NAMESPACE_MAL_BEGIN  \
  namespace bm { \
  namespace mal {
#define NAMESPACE_MAL_END \
  } \
  }
#define USING_NAMESPACE_MAL(n) using m = bm::mal

#endif /* BM_PLATFORM_MAL_NAMESPACE_H_ */
