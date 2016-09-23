set(main_SRCS main.cpp)

add_executable(HH08_App ${main_SRCS})

target_link_libraries(HH08_App
  lodepng
  matrix
  imgpxl
  imgchannel
)

install(TARGETS HH08_App DESTINATION bin)
