cmake_minimum_required(VERSION 3.0.0)
project(templates-problem VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(target_name ${PROJECT_NAME})

set(source_list
    src/main.cpp
    src/dynamic-array.cpp
)

add_executable(${target_name} ${source_list})

target_include_directories(${target_name} 
    PRIVATE
        include)