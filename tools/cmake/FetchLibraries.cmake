cmake_minimum_required(VERSION 3.14)
include(FetchContent)

FetchContent_Declare(
  acutest
  #GIT_REPOSITORY https://github.com/mity/acutest.git
  #GIT_TAG        cce300734bfe5c3879b0449ac283a872633e615c
  URL      https://raw.githubusercontent.com/mity/acutest/cce300734bfe5c3879b0449ac283a872633e615c/include/acutest.h
  URL_HASH SHA256=6433ba0ffbed7e57647ed310242e60fd7e26abe52966524c63e82bdcb32c8e84
  DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/external/acutest/
  DOWNLOAD_NO_EXTRACT ON
)

FetchContent_Declare(
  CppUTest
  #GIT_REPOSITORY https://github.com/cpputest/cpputest.git
  #GIT_TAG        67d2dfd41e13f09ff218aa08e2d35f1c32f032a1
  URL      https://github.com/cpputest/cpputest/releases/download/v4.0/cpputest-4.0.tar.gz
  URL_HASH SHA256=21c692105db15299b5529af81a11a7ad80397f92c122bd7bf1e4a4b0e85654f7
  DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/external/cpputest/
)
set(LONGLONG ON  CACHE BOOL "Support long long")
set(C++11    ON  CACHE BOOL "Compile with C++11 support")
set(TESTS    OFF CACHE BOOL "Compile and make tests for the code?")

FetchContent_Declare(
  GoogleTest
  #GIT_REPOSITORY https://github.com/google/googletest.git
  #GIT_TAG        e2239ee6043f73722e7aa812a459f54a28552929
  URL      https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
  URL_HASH SHA256=b4870bf121ff7795ba20d20bcdd8627b8e088f2d1dab299a031c1034eddc93d5
  DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/external/googletest/
)

FetchContent_Declare(
  fff
  #GIT_REPOSITORY https://github.com/meekrosoft/fff.git
  #GIT_TAG        7e09f07e5b262b1cc826189dc5057379e40ce886
  URL      https://github.com/meekrosoft/fff/archive/refs/tags/v1.1.tar.gz
  URL_HASH SHA256=510efb70ab17a0035affd170960401921c9cc36ec81002ed00d2bfec6e08f385
  DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/external/fff/
)

FetchContent_Declare(
  newlib
  #GIT_REPOSITORY https://sourceware.org/git/newlib-cygwin.git
  #GIT_TAG        415fdd4279b85eeec9d54775ce13c5c412451e08
  URL      ftp://sourceware.org/pub/newlib/newlib-4.1.0.tar.gz
  URL_HASH SHA256=f296e372f51324224d387cc116dc37a6bd397198756746f93a2b02e9a5d40154
  DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/external/newlib/
)

FetchContent_MakeAvailable(acutest)
FetchContent_MakeAvailable(cpputest)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(fff)
FetchContent_MakeAvailable(newlib)
