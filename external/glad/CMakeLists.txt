cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

set(LIBRARY_NAME glad)

project(${LIBRARY_NAME})

add_library(${LIBRARY_NAME} STATIC include/glad/glad.h src/glad.c)
target_include_directories(${LIBRARY_NAME} PUBLIC include/)
