cmake_minimum_required(VERSION 3.0.0)
project(static-array-2 VERSION 0.1.0 LANGUAGES C CXX)

# set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_COMPILER "MSVC")
set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(target_name ${PROJECT_NAME})

set(source_list
    main.cpp
)

add_executable(${target_name} ${source_list})

