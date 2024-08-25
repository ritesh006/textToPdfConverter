cmake_minimum_required(VERSION 3.5)
project(txt_to_pdf_converter)

# Set the library directory
set(LIBHARU_DIR /home/ritesh/Desktop/Project/c_Projects/textToPdfConverter/lib)

# Check if the library file exists
if(NOT EXISTS ${LIBHARU_DIR}/libhpdf.a)
    message(FATAL_ERROR "libHaru static library not found in ${LIBHARU_DIR}")
endif()

# Include directories
include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.c
    src/input.c
    src/txtToPdf.c
    src/interface.c  
)

# Executable
add_executable(txt_to_pdf ${SOURCES})

# Find and link zlib
find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
    target_link_libraries(txt_to_pdf
        ${LIBHARU_DIR}/libhpdf.a
        m  # This links against the math library
        ${ZLIB_LIBRARIES}  # This links against the zlib library
    )
else()
    message(FATAL_ERROR "ZLIB library not found")
endif()

# Set the RPATH to include the directory where the library is located
set_target_properties(txt_to_pdf PROPERTIES
    INSTALL_RPATH_USE_LINK_PATH TRUE
)
