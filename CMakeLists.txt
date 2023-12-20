cmake_minimum_required(VERSION 3.22)
project(GraphInterface)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp 
    ./src/Graph.hpp
    ./src/SortedSparseList.hpp
    ./src/EdgeList.hpp
    )
