cmake_minimum_required(VERSION 3.11)
project(WinterCup4)


#Put this in your CMakeLists.txt file (change any options from OFF to ON if you want):

set(CMAKE_CXX_STANDARD 20)


        
add_executable(RamiSchemeRingExtension linear_algebra.h modular_arithmetic.h number_theory.h
        ring_extension.h polynomial.h solution_ring_extension.cpp )
        
add_executable(RamiSchemeMatrix linear_algebra.h modular_arithmetic.h number_theory.h
        ring_extension.h polynomial.h solution_matrix.cpp )
                
add_executable(RamiSchemePatternMatching linear_algebra.h modular_arithmetic.h number_theory.h
        ring_extension.h polynomial.h solution_pattern_matching.cpp )

add_executable(RamiSchemeHeuristic linear_algebra.h modular_arithmetic.h number_theory.h
        ring_extension.h polynomial.h solution_heuristic.cpp )

add_executable(RamiSchemeHashing linear_algebra.h modular_arithmetic.h number_theory.h
ring_extension.h polynomial.h solution_hashing.cpp )

add_executable(RamiSchemeDiff linear_algebra.h modular_arithmetic.h number_theory.h
ring_extension.h polynomial.h solution_diff.cpp )


add_executable(RamiSchemeExhaustiveGenerator linear_algebra.h modular_arithmetic.h number_theory.h
        ring_extension.h polynomial.h exhaustive_generator.cpp )

add_executable(RamiSchemeGenerator linear_algebra.h modular_arithmetic.h number_theory.h
ring_extension.h polynomial.h generator.cpp )