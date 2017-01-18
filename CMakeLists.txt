cmake_minimum_required(VERSION 3.6)
project(ass3clion)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.58.0 COMPONENTS system filesystem thread REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(include src)

file(GLOB SOURCES "src/*.cpp" "include/*.h" "include/Packets/*.h" "src/Packets/*.cpp")
add_executable(ass3clion ${SOURCES})



TARGET_LINK_LIBRARIES( ass3clion ${Boost_LIBRARIES} )