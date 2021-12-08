macro(target_compile_option_baremetal Target_)
  target_compile_options(${Target_}
    PRIVATE $<$<COMPILE_LANGUAGE:C,CXX>:-ffreestanding>
    PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions -fno-unwind-tables -fno-non-call-exceptions -fno-use-cxa-atexit -fno-rtti> )
endmacro()

macro(target_link_option_baremetal Target_ LdScript_)
  set_target_properties(${Target_}
    PROPERTIES LINK_DEPENDS $<$<PLATFORM_ID:Generic>:${LdScript_}> )
  target_link_options(${Target_}
    PRIVATE -nostdlib
    PRIVATE $<$<PLATFORM_ID:Generic>:-T ${LdScript_}> )
endmacro()
