file (GLOB SRCS *.cpp)

#allows testing img file to be copied to the build directory
configure_file(left1.png left1.png COPYONLY)

add_executable(imagepxltest ${SRCS})

target_link_libraries(imagepxltest
  imgpxl
  libgtest
  libgmock
)

add_test(NAME imagepxltest COMMAND imagepxltest)
