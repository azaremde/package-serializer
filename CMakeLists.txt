cmake_minimum_required(VERSION 3.12)

project(package-serializer VERSION 1.0)

add_executable(test src/main.cpp)

target_include_directories(test PUBLIC src)