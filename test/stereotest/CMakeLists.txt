file (GLOB SRCS *.cpp)

#set(matrixtest_SRCS
#    matrixtest.h
#    matrixtest.cpp
#)

#add_library(matrixtest STATIC
#    ${matrixtest_SRCS}
#)

add_executable(stereotest ${SRCS})

configure_file(left1.png left1.png COPYONLY)
configure_file(right1.png right1.png COPYONLY)

target_link_libraries(stereotest
  sgbm
  libgtest
  libgmock
)

add_test(NAME stereotest COMMAND stereotest)
