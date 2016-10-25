cmake_minimum_required(VERSION 2.8.12)

project(HH08_project)

#in order to append the compiler flags so it doesn't give trouble
set(GXX_COMPILER_FLAGS "-std=c++14 -O3 -Wall -pedantic")

set (CMAKE_C_COMPILER /usr/bin/gcc-6)
set (CMAKE_CXX_COMPILER  /usr/bin/g++-6)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GXX_COMPILER_FLAGS}" )

enable_testing()

#SET(CMAKE_INCLUDE_CURRENT_DIR ON)
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(lodepng)
ADD_SUBDIRECTORY(data)

#add_executable (${PROJECT_NAME} ${SOURCE_LIST})
