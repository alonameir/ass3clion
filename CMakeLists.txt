cmake_minimum_required(VERSION 3.6)
project(ass3clion)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include src bin)

file(GLOB SOURCES "src/*.cpp" "include/*.h")

add_executable(ass3clion ${SOURCES} include/DISC.h src/DISC.cpp include/ACK.h src/ACK.cpp include/DATA.h src/DATA.cpp src/BCAST.cpp include/BCAST.h include/ERROR.h src/ERROR.cpp)

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)
if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()