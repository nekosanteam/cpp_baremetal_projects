project(BareMetal00_Startup C)
enable_language(ASM)

add_library(lib00_startup OBJECT src/startup.c
  $<$<PLATFORM_ID:Generic>:src/startup_a64.S>)
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
