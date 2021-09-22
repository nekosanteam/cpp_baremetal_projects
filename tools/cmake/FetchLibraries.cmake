cmake_minimum_required(VERSION 3.14)
include(FetchContent)

FetchContent_Declare(
    acutest
    GIT_REPOSITORY https://github.com/mity/acutest.git
    GIT_TAG        cce300734bfe5c3879b0449ac283a872633e615c
    #URL https://raw.githubusercontent.com/mity/acutest/cce300734bfe5c3879b0449ac283a872633e615c/include/acutest.h
    #URL_HASH
)
FetchContent_MakeAvailable(acutest)

FetchContent_Declare(
    CppUTest
    URL      https://github.com/cpputest/cpputest/releases/download/v4.0/cpputest-4.0.tar.gz
    URL_HASH SHA256=21c692105db15299b5529af81a11a7ad80397f92c122bd7bf1e4a4b0e85654f7
)
FetchContent_MakeAvailable(cpputest)
