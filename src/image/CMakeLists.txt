set(image_SRCS
    image.h
    image.cpp
)

# Declare the library
add_library(image STATIC
    ${image_SRCS}
)
#Specify libraries needed by image
target_link_libraries(image matrix)
target_link_libraries(image lodepng)
# Specify here the include directories exported
# by this library
target_include_directories(image PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
