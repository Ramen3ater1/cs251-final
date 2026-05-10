cmake_minimum_required(VERSION 3.1)
project(Dictionary)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -g -Wno-unused-function)  # insert warnings, and -g makes stuff look nicer in debugger
include_directories(/home/courses/include ../HaverfordCS/include)


add_executable(Dictionary
        main.cpp
        Dictionary_via_std_map.cpp
        Dictionary_pure_via_std_map.cpp
        Dictionary_examples.cpp
        AST.cpp
        ASD.cpp
        A_simpler_tree_and_dag.cpp A_simpler_tree_and_dag.h)

