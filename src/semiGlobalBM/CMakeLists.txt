set(sgbm_SRCS
    semiglobalbm.h
    semiglobalbm.cpp
    saturatecast.h
)

# Declare the library
add_library(sgbm STATIC
    ${sgbm_SRCS}
)

target_link_libraries(sgbm image)

# Specify here the include directories exported
# by this library
target_include_directories(sgbm PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
