file (GLOB SRCS *.cpp)

#set(matrixtest_SRCS
#    matrixtest.h
#    matrixtest.cpp
#)

#add_library(matrixtest STATIC
#    ${matrixtest_SRCS}
#)

add_executable(matrixtest ${SRCS})

target_link_libraries(matrixtest
  matrix
  libgtest
  libgmock
)

add_test(NAME matrixtest COMMAND matrixtest)
