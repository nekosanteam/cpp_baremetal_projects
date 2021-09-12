set(CMAKE_C_COMPILER   "${GCC_CROSS_COMPILE}gcc${GCC_VERSION}")
set(CMAKE_CXX_COMPILER "${GCC_CROSS_COMPILE}g++${GCC_VERSION}")
set(CMAKE_ASM_COMPILER "${GCC_CROSS_COMPILE}as")
set(CMAKE_C_LINKER     "${GCC_CROSS_COMPILE}gcc${GCC_VERSION}")
set(CMAKE_CXX_LINKER   "${GCC_CROSS_COMPILE}g++${GCC_VERSION}")

if (DEFINED GCC_C_FLAGS_ADD)
  set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${GCC_C_FLAGS_ADD})
endif()
if (DEFINED GCC_ASM_FLAGS_ADD)
  set(CMAKE_ASM_FLAGS ${CMAKE_ASM_FLAGS} ${GCC_ASM_FLAGS_ADD})
endif()
if (DEFINED GCC_CXX_FLAGS_ADD)
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS_ADD})
endif()
if (DEFINED GCC_EXE_LINKER_FLAGS_ADD)
  set(CMAKE_LINK_LIBRARY_FLAG ${CMAKE_LINK_LIBRARY_FLAG} ${GCC_EXE_LINKER_FLAGS_ADD})
endif()
