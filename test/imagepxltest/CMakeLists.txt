file (GLOB SRCS *.cpp)

add_executable(imagepxltest ${SRCS})

target_link_libraries(imagepxltest
  imgpxl
  libgtest
  libgmock
)

add_test(NAME imagepxltest COMMAND imagepxltest)
