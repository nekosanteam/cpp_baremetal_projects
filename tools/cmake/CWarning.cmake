set(CWARNING_GCC_Warning   -Wall -Wextra -Wpedantic)
set(CWARNING_Clang_Warning -Wall -Wextra -Wpedantic)
set(CWARNING_MSVC_Warning  /W4)

set(CWARNING_GCC_Warning_CXX   -Weffc++)
set(CWARNING_Clang_Warning_CXX )
set(CWARNING_MSVC_Warning_CXX  )

macro(target_compile_option_warning Target_)
  target_compile_options(${Target_}
    PRIVATE $<$<C_COMPILER_ID:GNU>:${CWARNING_GCC_Warning}>
    PRIVATE $<$<C_COMPILER_ID:Clang>:${CWARNING_Clang_Warning}>
    PRIVATE $<$<C_COMPILER_ID:MSVC>:${CWARNING_MSVC_Warning}>
    PRIVATE $<$<CXX_COMPILER_ID:GNU>:${CWARNING_GCC_Warning} ${CWARNING_GCC_Warning_CXX}>
    PRIVATE $<$<CXX_COMPILER_ID:Clang>:${CWARNING_Clang_Warning} ${CWARNING_Clang_Warning_CXX}>
    PRIVATE $<$<CXX_COMPILER_ID:MSVC>:${CWARNING_MSVC_Warning} ${CWARNING_MSVC_Warning_CXX}>
  )
endmacro()
