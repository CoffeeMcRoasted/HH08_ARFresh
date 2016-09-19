file (GLOB SRCS *.cpp)

add_executable(matrixtest ${SRCS})

target_link_libraries(matrixtest
  matrix
  libgtest
  libgmock
)

add_test(NAME matrixtest COMMAND matrixtest)
