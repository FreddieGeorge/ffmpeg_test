# Add all source files in the src directory
file(GLOB SOURCES "*.c")

# Create a library named 'my_image' using all source files
add_library(src_file ${SOURCES})
