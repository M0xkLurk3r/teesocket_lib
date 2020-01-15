cmake_minimum_required(VERSION 3.0)

project(teesocket_lib LANGUAGES C)
include_directories(./include/)
link_directories(./lib/)
add_library(teesocket SHARED main.c)
target_link_libraries(teesocket teesock)
