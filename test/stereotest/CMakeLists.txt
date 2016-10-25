file (GLOB SRCS *.cpp)

#set(matrixtest_SRCS
#    matrixtest.h
#    matrixtest.cpp
#)

#add_library(matrixtest STATIC
#    ${matrixtest_SRCS}
#)

add_executable(stereotest ${SRCS})

target_link_libraries(stereotest
  sgbm
  libgtest
  libgmock
)

add_test(NAME stereotest COMMAND stereotest)
