file (GLOB SRCS *.cpp)
configure_file(left1.png left1.png COPYONLY)

add_executable(imagepxltest ${SRCS})

target_link_libraries(imagepxltest
  imgpxl
  libgtest
  libgmock
)

add_test(NAME imagepxltest COMMAND imagepxltest)
