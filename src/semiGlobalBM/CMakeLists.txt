set(sgbm_SRCS
    sgbm.h
    sgbm.cpp
)

# Declare the library
add_library(sgbm STATIC
    ${sgbm_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(sgbm PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
