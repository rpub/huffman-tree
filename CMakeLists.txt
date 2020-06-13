cmake_minimum_required(VERSION 3.10)
project(huffman-Ramiisaac)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(huffman
        main.cpp tree.cpp tree.h)