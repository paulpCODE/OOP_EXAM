cmake_minimum_required(VERSION 3.12)
project(OOP_EXAM)

set(CMAKE_CXX_STANDARD 17)

include_directories(../includes)

set(SOURCES "../src/linkedlists.cpp")

set(HEADERS "../includes/linkedlists.h")

add_executable(OOP_EXAM main.cpp ${SOURCES} ${HEADERS})
