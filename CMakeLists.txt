cmake_minimum_required(VERSION 3.5)
project(spiral-flap VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add core libraries first
add_subdirectory(core)

# Then add your application
add_subdirectory(src)
