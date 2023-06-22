cmake_minimum_required(VERSION 3.16)
include(FetchContent)

# acutest
FetchContent_Declare(
  acutest
  DOWNLOAD_DIR ${EXTERNAL_DIR}/acutest/
  DOWNLOAD_NO_EXTRACT ON
  URL      https://raw.githubusercontent.com/mity/acutest/cce300734bfe5c3879b0449ac283a872633e615c/include/acutest.h
  URL_HASH SHA256=6433ba0ffbed7e57647ed310242e60fd7e26abe52966524c63e82bdcb32c8e84
  #GIT_REPOSITORY https://github.com/mity/acutest.git
  #GIT_TAG        cce300734bfe5c3879b0449ac283a872633e615c
)

# CppUTest
FetchContent_Declare(
  CppUTest
  DOWNLOAD_EXTRACT_TIMESTAMP false
  DOWNLOAD_DIR ${EXTERNAL_DIR}/cpputest/
  URL      https://github.com/cpputest/cpputest/releases/download/v4.0/cpputest-4.0.tar.gz
  URL_HASH SHA256=21c692105db15299b5529af81a11a7ad80397f92c122bd7bf1e4a4b0e85654f7
  #GIT_REPOSITORY https://github.com/cpputest/cpputest.git
  #GIT_TAG        67d2dfd41e13f09ff218aa08e2d35f1c32f032a1
)
set(LONGLONG ON  CACHE BOOL "")
set(C++11    ON  CACHE BOOL "")
set(TESTS    OFF CACHE BOOL "")

# GoogleTest
FetchContent_Declare(
  GoogleTest
  DOWNLOAD_EXTRACT_TIMESTAMP false
  DOWNLOAD_DIR ${EXTERNAL_DIR}/googletest/
  URL      https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
  URL_HASH SHA256=b4870bf121ff7795ba20d20bcdd8627b8e088f2d1dab299a031c1034eddc93d5
  #GIT_REPOSITORY https://github.com/google/googletest.git
  #GIT_TAG        e2239ee6043f73722e7aa812a459f54a28552929
)

# fff
FetchContent_Declare(
  fff
  DOWNLOAD_EXTRACT_TIMESTAMP false
  DOWNLOAD_DIR ${EXTERNAL_DIR}/fff/
  URL      https://github.com/meekrosoft/fff/archive/refs/tags/v1.1.tar.gz
  URL_HASH SHA256=510efb70ab17a0035affd170960401921c9cc36ec81002ed00d2bfec6e08f385
  #GIT_REPOSITORY https://github.com/meekrosoft/fff.git
  #GIT_TAG        7e09f07e5b262b1cc826189dc5057379e40ce886
)

# NT-Shell
FetchContent_Declare(
  ntshell
  DOWNLOAD_EXTRACT_TIMESTAMP false
  DOWNLOAD_DIR ${EXTERNAL_DIR}/ntshell/
  URL      https://cubeatsystems.com/ntshell/resources/ntshell-v0.3.1.tar.gz
  URL_HASH SHA256=ea1497ce208cf9e3d02c161fd5d72e0e785b34074e31dca34fe855ba8fd89c74
)

# Trusted Firmware-A
file(DOWNLOAD
  https://github.com/ARM-software/arm-trusted-firmware/archive/refs/tags/v2.6.zip
  ${EXTERNAL_DIR}/atf/v2.6.zip
  EXPECTED_HASH SHA256=d64312a67b6a21df298f0c9ee2514c7948821d70d6bcf01ab15dd8aca5d4a003
  #GIT_REPOSITORY https://github.com/ARM-software/arm-trusted-firmware.git
  #GIT_TAG        a1f02f4f3daae7e21ee58b4c93ec3e46b8f28d15
)

# u-boot
file(DOWNLOAD
  https://github.com/u-boot/u-boot/archive/refs/tags/v2022.01.zip
  ${EXTERNAL_DIR}/uboot/v2022.01.zip
  EXPECTED_HASH SHA256=6ca0c4754f2da3d35e9688c455814585105a93eb33c228ffe3b7a8abd471c759
  #GIT_REPOSITORY https://github.com/u-boot/u-boot.git
  #GIT_TAG        d637294e264adfeb29f390dfc393106fd4d41b17
)

# qemu
file(DOWNLOAD
  https://download.qemu.org/qemu-6.2.0.tar.xz
  ${EXTERNAL_DIR}/qemu/qemu-6.2.0.tar.xz
  EXPECTED_HASH SHA256=68e15d8e45ac56326e0b9a4afa8b49a3dfe8aba3488221d098c84698bca65b45
)

# open62541
file(DOWNLOAD
  https://github.com/open62541/open62541/archive/refs/tags/v1.3.tar.gz
  ${EXTERNAL_DIR}/open62541/v1.3.tar.gz
  EXPECTED_HASH SHA256=1227384bedbe9174a4ec91f302b336afba4234f8558a08e7b10b64e4bce6cb52
)

# sqlite3
file(DOWNLOAD
  https://www.sqlite.org/2022/sqlite-amalgamation-3380500.zip
  ${EXTERNAL_DIR}/sqlite3/sqlite-amalgamation-3380500.zip
  EXPECTED_HASH SHA256=bebb039b748441e3d25d71d11f7a4a33f5df11f318ec18fa7f343d2083755e2c
)

FetchContent_MakeAvailable(cpputest)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(fff)

FetchContent_GetProperties(acutest)
if (NOT acutest_POPULATED)
  FetchContent_Populate(acutest)
endif()

FetchContent_GetProperties(ntshell)
if (NOT ntshell_POPULATED)
  FetchContent_Populate(ntshell)
  file(COPY ${EXTERNAL_DIR}/ntshell/CMakeLists.txt DESTINATION ${ntshell_SOURCE_DIR}/ )
  add_subdirectory(${ntshell_SOURCE_DIR} ${ntshell_BINARY_DIR})
endif()
