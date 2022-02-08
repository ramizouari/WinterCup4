cmake_minimum_required(VERSION 3.11)
project(WinterCup4)


#Put this in your CMakeLists.txt file (change any options from OFF to ON if you want):



include_directories("C:/local/boost_1_78_0")
find_package(Boost)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-z,stack-size=4294967296")
add_executable(PermutationDC solution_dc.cpp)
add_executable(PermutationDCMemoized solution_dc_memoized.cpp)
add_executable(PermutationGenerator generator.cpp)