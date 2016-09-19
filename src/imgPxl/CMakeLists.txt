set(imgPxl_SRCS
    imgpxl.h
    imgpxl.cpp
)

# Declare the library
add_library(imgpxl STATIC
    ${imgPxl_SRCS}
)
#Specify libraries needed by imgpxl
target_link_libraries(imgpxl matrix)
target_link_libraries(imgpxl lodepng)
# Specify here the include directories exported
# by this library
target_include_directories(imgpxl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
