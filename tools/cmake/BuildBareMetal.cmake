cmake_minimum_required(VERSION 3.15)

set(CFreestanding_GCC   -ffreestanding)
set(CFreestanding_Clang -ffreestanding)
set(CFreestanding_MSVC  )

set(CFreestanding_GCC_CXX
  -fno-exceptions -fno-unwind-tables -fno-non-call-exceptions -fno-use-cxa-atexit -fno-rtti)
set(CFreestanding_Clang_CXX
  -fno-exceptions -fno-unwind-tables -fno-non-call-exceptions -fno-use-cxa-atexit -fno-rtti)
set(CFreestanding_MSVC_CXX
  )

macro(target_compile_option_baremetal Target_)
  target_compile_options(${Target_}
    PRIVATE $<$<COMPILE_LANG_AND_ID:C,GNU>:${CFreestanding_GCC}>
    PRIVATE $<$<COMPILE_LANG_AND_ID:C,Clang>:${CFreestanding_Clang}>
    PRIVATE $<$<COMPILE_LANG_AND_ID:C,MSVC>:${CFreestanding_MSVC}>
    PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,GNU>:${CFreestanding_GCC} ${CFreestanding_GCC_CXX}>
    PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,Clang>:${CFreestanding_Clang} ${CFreestanding_Clang_CXX}>
    PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:${CFreestanding_MSVC} ${CFreestanding_GCC_MSVC}>
  )
endmacro()

macro(target_link_option_baremetal Target_ LdScript_)
  set_target_properties(${Target_}
    PROPERTIES LINK_DEPENDS $<$<PLATFORM_ID:Generic>:${LdScript_}> )
  target_link_options(${Target_}
    PRIVATE -nostdlib
    PRIVATE $<$<PLATFORM_ID:Generic>:-T ${LdScript_}> )
endmacro()
