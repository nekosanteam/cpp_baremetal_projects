cmake_minimum_required(VERSION 3.13)

set(CWARNING_GCC_Warning   -Wall -Wextra -Wpedantic)
set(CWARNING_Clang_Warning -Wall -Wextra -Wpedantic)
set(CWARNING_MSVC_Warning  /W4)

set(CWARNING_GCC_Warning_CXX   -Weffc++)
set(CWARNING_Clang_Warning_CXX -Weffc++)
set(CWARNING_MSVC_Warning_CXX  )

macro(target_compile_option_warning Target_)
  target_compile_options(${Target_}
    PRIVATE $<$<COMPILE_LANG_AND_ID:C,GNU>:${CWARNING_GCC_Warning}>
    PRIVATE $<$<COMPILE_LANG_AND_ID:C,Clang>:${CWARNING_Clang_Warning}>
    PRIVATE $<$<COMPILE_LANG_AND_ID:C,MSVC>:${CWARNING_MSVC_Warning}>
    PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,GNU>:${CWARNING_GCC_Warning} ${CWARNING_GCC_Warning_CXX}>
    PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,Clang>:${CWARNING_Clang_Warning} ${CWARNING_Clang_Warning_CXX}>
    PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:${CWARNING_MSVC_Warning} ${CWARNING_MSVC_Warning_CXX}>
  )
endmacro()
