cmake_minimum_required(VERSION 3.11)
project(WinterCup4)


#Put this in your CMakeLists.txt file (change any options from OFF to ON if you want):

set(BOOST_ROOT C:/local/boost_1_78_0)
include_directories("C:/local/boost_1_78_0")
find_package(Boost)

set(CMAKE_CXX_STANDARD 20)
   
add_executable(SimulationSolution solution.cpp "modular_arithmetic.h")
add_executable(SimulationSolutionDP solution_dp.cpp "modular_arithmetic.h")
add_executable(SimulationSolutionBoost solution_boost.cpp "modular_arithmetic.h")
