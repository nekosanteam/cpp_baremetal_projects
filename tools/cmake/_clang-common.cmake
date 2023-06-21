set(CMAKE_C_COMPILER   "clang${CLANG_VERSION}")
set(CMAKE_CXX_COMPILER "clang++${CLANG_VERSION}")
set(CMAKE_ASM_COMPILER "clang${CLANG_VERSION}")
set(CMAKE_C_LINKER     "clang${CLANG_VERSION}")
set(CMAKE_CXX_LINKER   "clang++${CLANG_VERSION}")
set(CMAKE_AR           "llvm-ar${CLANG_VERSION}" CACHE FILEPATH "Archiver")
set(CMAKE_RANLIB       "llvm-ranlib${CLANG_VERSION}" CACHE FILEPATH "Ranlib")
set(CMAKE_NM           "llvm-nm${CLANG_VERSION}")
set(CMAKE_OBJCOPY      "llvm-objcopy${CLANG_VERSION}")
set(CMAKE_OBJDUMP      "llvm-objdump${CLANG_VERSION}")

if(DEFINED CLANG_TRIPLE)
  set(CMAKE_C_COMPILER_TARGET   ${CLANG_TRIPLE})
  set(CMAKE_CXX_COMPILER_TARGET ${CLANG_TRIPLE})
  set(CMAKE_ASM_COMPILER_TARGET ${CLANG_TRIPLE})
endif()
