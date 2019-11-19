cmake_minimum_required(VERSION 3.15)
project(active_modules)

set(CMAKE_CXX_STANDARD 14)

file(GLOB objects
        src/objects/*.hpp src/objects/*.cpp)
file(GLOB mcmc
        src/mcmc/*.hpp src/mcmc/*.cpp)

add_executable(active_modules src/main/main.cpp ${objects} ${mcmc})