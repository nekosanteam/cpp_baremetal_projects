cmake_minimum_required(VERSION 3.14)
include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckLibraryExists)
include(FetchContent)

CHECK_INCLUDE_FILE_CXX(acutest.h ACUTEST_H_FOUND)
if (NOT ACUTEST_H_FOUND)
  FetchContent_Declare(
    acutest
    #GIT_REPOSITORY https://github.com/mity/acutest.git
    #GIT_TAG        cce300734bfe5c3879b0449ac283a872633e615c
    URL      https://raw.githubusercontent.com/mity/acutest/cce300734bfe5c3879b0449ac283a872633e615c/include/acutest.h
    URL_HASH SHA256=6433ba0ffbed7e57647ed310242e60fd7e26abe52966524c63e82bdcb32c8e84
    DOWNLOAD_NO_EXTRACT ON
  )
  FetchContent_MakeAvailable(acutest)
endif()

FetchContent_Declare(
    CppUTest
    #GIT_REPOSITORY https://github.com/cpputest/cpputest.git
    #GIT_TAG        67d2dfd41e13f09ff218aa08e2d35f1c32f032a1
    URL      https://github.com/cpputest/cpputest/releases/download/v4.0/cpputest-4.0.tar.gz
    URL_HASH SHA256=21c692105db15299b5529af81a11a7ad80397f92c122bd7bf1e4a4b0e85654f7
)
set(TESTS OFF CACHE BOOL "Switch off CppUTest Test build")
FetchContent_MakeAvailable(cpputest)
