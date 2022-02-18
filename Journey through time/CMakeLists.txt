cmake_minimum_required(VERSION 3.11)
project(WinterCup4)


#Put this in your CMakeLists.txt file (change any options from OFF to ON if you want):
set(CMAKE_CXX_STANDARD 20)
   
add_executable(TimeJourneyAttempt attempt.cpp )
add_executable(TimeJourneyAttempt2 attempt2.cpp )
add_executable(TimeJourneySolution Solution.cpp )
add_executable(TimeJourneyGenerator generator.cpp )