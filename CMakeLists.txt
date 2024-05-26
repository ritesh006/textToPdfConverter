cmake_minimum_required(VERSION 3.5)

project(txt_to_pdf_converter)

# Find libHaru
find_library(LIBHARU_LIBRARY NAMES hpdf libhpdf PATHS /usr/local/lib /opt/lib /opt/local/lib)

if(NOT LIBHARU_LIBRARY)
    message(FATAL_ERROR "libHaru library not found")
endif()

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.c
    src/input.c
    src/txtToPdf.c
    src/interface.c  
    # Add more source files here if you have them
)

# Executable
add_executable(txt_to_pdf ${SOURCES})

# Link the libHaru library
target_link_libraries(txt_to_pdf ${LIBHARU_LIBRARY})

# If you have headers that you're installing, you might also want to add an install command
# install(TARGETS txt_to_pdf DESTINATION bin)