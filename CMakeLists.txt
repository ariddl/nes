cmake_minimum_required(VERSION 3.15)

project(nes
  DESCRIPTION "NES emulator"
  LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/nes.h)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(src)
target_include_directories(${PROJECT_NAME} PRIVATE src)