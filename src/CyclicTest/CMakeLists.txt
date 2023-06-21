project(SRC_CyclicTest)

add_executable(cyclictest main.c cyclictest_main.cpp cyclictest_itimer.cpp)
target_compile_definitions(cyclictest PRIVATE -D_GNU_SOURCE)
target_link_libraries(cyclictest PRIVATE -lpthread -lrt)
