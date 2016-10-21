cmake_minimum_required (VERSION 2.6)
project (Graphics_Project3)

include_directories(include)

file(GLOB SOURCES "src/*.c")
file(GLOB HEADERS "include/*.h")

add_executable(raycast ${SOURCES} ${HEADERS})
