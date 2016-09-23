set(imgChannel_SRCS
    imgchannel.h
    imgchannel.cpp
)

# Declare the library
add_library(imgchannel STATIC
    ${imgChannel_SRCS}
)
#Specify libraries needed by imgpxl
target_link_libraries(imgchannel matrix)
target_link_libraries(imgchannel lodepng)
# Specify here the include directories exported
# by this library
target_include_directories(imgchannel PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
