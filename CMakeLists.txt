project(calculatevelocity)

add_definitions(-std=gnu++0x)

list(APPEND CMAKE_MODULE_PATH $ENV{ROOTSYS}/etc/cmake)

find_package(ROOT REQUIRED COMPONENTS Hist Gpad Graf MathCore) 

include_directories(${ROOT_INCLUDE_DIRS})

add_library(velocityCalculator SHARED velocityCalculator.cpp)

target_link_libraries(velocityCalculator ${ROOT_LIBRARIES})

add_executable(calculatevelocity main.cpp)

target_link_libraries(calculatevelocity velocityCalculator)
