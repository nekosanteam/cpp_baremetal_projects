project(BareMetal00_Startup C)
enable_language(ASM)

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "AArch64")
  set(STARTUP_ASM_SRC src/startup_a64.S)
elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "Arm")
  set(STARTUP_ASM_SRC src/startup_a32.S)
endif()

add_library(lib00_startup OBJECT src/startup.c
  $<$<PLATFORM_ID:Generic>: $STARTUP_ASM_SRC>)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(lib00_startup)
endif()

add_executable(00_startup app/main.c)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(00_startup)
endif()
target_link_libraries(00_startup
  $<$<PLATFORM_ID:Generic>:lib00_startup>)
if(COMMAND target_link_option_baremetal)
  target_link_option_baremetal(00_startup ${BareMetal00_Startup_SOURCE_DIR}/src/ldscript_a64.ld)
endif()
