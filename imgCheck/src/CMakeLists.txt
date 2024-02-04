# Add all source files in the src directory
file(GLOB SOURCES "*.cpp")

# Create a library named 'my_image' using all source files
add_library(my_image ${SOURCES})
