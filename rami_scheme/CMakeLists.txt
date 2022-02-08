cmake_minimum_required(VERSION 3.11)
project(WinterCup4)


#Put this in your CMakeLists.txt file (change any options from OFF to ON if you want):



include_directories("C:/local/boost_1_78_0")
find_package(Boost)

set(CMAKE_CXX_STANDARD 20)


        
add_executable(RamiSchemeRingExtension linear_algebra.h modular_arithmetic.h number_theory.h
        ring_extension.h polynomial.h solution_ring_extension.cpp )
        
add_executable(RamiSchemeMatrix linear_algebra.h modular_arithmetic.h number_theory.h
        ring_extension.h polynomial.h solution_matrix.cpp )
                
add_executable(RamiSchemePatternMatching linear_algebra.h modular_arithmetic.h number_theory.h
        ring_extension.h polynomial.h solution_pattern_matching.cpp )

add_executable(RamiSchemeExhaustiveGenerator linear_algebra.h modular_arithmetic.h number_theory.h
        ring_extension.h polynomial.h exhaustive_generator.cpp )

add_executable(RamiSchemeGenerator linear_algebra.h modular_arithmetic.h number_theory.h
ring_extension.h polynomial.h generator.cpp )

target_include_directories(RamiSchemeMatrix PUBLIC "C:/local/boost_1_78_0/boost")
target_include_directories(RamiSchemeRingExtension PUBLIC "C:/local/boost_1_78_0/boost")
target_include_directories(RamiSchemePatternMatching PUBLIC "C:/local/boost_1_78_0/boost")
target_include_directories(RamiSchemeExhaustiveGenerator PUBLIC "C:/local/boost_1_78_0/boost")

