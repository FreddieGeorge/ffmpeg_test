cmake_minimum_required(VERSION 3.10)

# set app name
set(APP_NAME ffmpeg_demo)

# set ffmpeg dir
set(FFMPEG_INC /home/flork/ffmpeg/build64/ffmpeg-4.4-ubuntu/include)
set(FFMPEG_LIB /home/flork/ffmpeg/build64/ffmpeg-4.4-ubuntu/lib)
# set(FFMPEG_INC /home/flork/ffmpeg/build64/ffmpeg-6.1.1/include)
# set(FFMPEG_LIB /home/flork/ffmpeg/build64/ffmpeg-6.1.1/lib)

project(${APP_NAME})

# cpp standard ver
# set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(include)
include_directories(${FFMPEG_INC})

# Add subdirectories
# add_subdirectory(src)

# Main executable
add_executable(${APP_NAME} main.c)

# add lib directories
# static lib
link_directories(${FFMPEG_LIB})

# Link the main executable with the library from src
# target_link_libraries(${APP_NAME} src_file)
target_link_libraries(${APP_NAME} ${FFMPEG_LIB}/libavformat.a ${FFMPEG_LIB}/libavcodec.a ${FFMPEG_LIB}/libavutil.a)
target_link_libraries(${APP_NAME} pthread m z swresample lzma)
