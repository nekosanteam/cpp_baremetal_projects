/**
 * @file fal_namespace.h
 * 
 */
#ifndef BM_PLATFORM_FAL_NAMESPACE_H_
#define BM_PLATFORM_FAL_NAMESPACE_H_

#define NAMESPACE_FAL_BEGIN  \
  namespace bm { \
  namespace fal {
#define NAMESPACE_FAL_END \
  } /* namespace fal */ \
  } /* namespace bm */
#define USING_NAMESPACE_FAL(m) namespace m = bm::fal

#endif /* BM_PLATFORM_FAL_NAMESPACE_H_ */
