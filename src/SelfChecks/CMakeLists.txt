project(SRC_SelfChecks)

add_executable(selfchecks main.c selfchecks_main.cpp selfchecks_mem.cpp)
target_compile_definitions(selfchecks PRIVATE -D_GNU_SOURCE)
#target_link_libraries(selfchecks PRIVATE -lpthread -lrt)
