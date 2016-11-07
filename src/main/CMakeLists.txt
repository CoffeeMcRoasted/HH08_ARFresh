set(main_SRCS main.cpp)

add_executable(HH08_App ${main_SRCS})

configure_file(left1.png left1.png COPYONLY)
configure_file(right1.png right1.png COPYONLY)

target_link_libraries(HH08_App
  lodepng
  matrix
  imgpxl
  imgchannel
  sgbm
)

install(TARGETS HH08_App DESTINATION bin)
