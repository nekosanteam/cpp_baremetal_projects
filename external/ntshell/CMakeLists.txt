cmake_minimum_required(VERSION 3.1)
project(ntshell-populate C)

add_library(ntshell STATIC
  lib/core/ntlibc.c lib/core/ntshell.c lib/core/text_editor.c lib/core/text_history.c
  lib/core/vtrecv.c lib/core/vtsend.c
  lib/util/ntopt.c  lib/util/ntstdio.c)

target_include_directories(ntshell
  PRIVATE lib/core
  PRIVATE lib/util)

# memo: ntshell-src にコピーしてビルドする設定。
