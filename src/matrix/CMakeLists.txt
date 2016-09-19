set(matrix_SRCS
    matrix.h
    matrix.cpp
)

# Declare the library
add_library(matrix STATIC
    ${matrix_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(matrix PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
