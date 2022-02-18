cmake_minimum_required(VERSION 3.11)
project(WinterCup4)


#Put this in your CMakeLists.txt file (change any options from OFF to ON if you want):

set(CMAKE_CXX_STANDARD 20)      
add_executable(Co-Sortable solution.cpp )
add_executable(Co-SortableGenerator generator.cpp )
