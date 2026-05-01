# minimum 3.1, compatibility requires 3.5

cmake_minimum_required(VERSION 3.5)

# boot project

set(CMAKE_C_STANDARD 17)
project(chess C)

# let other instructors handle the rest

add_subdirectory(external)
add_subdirectory(src)
