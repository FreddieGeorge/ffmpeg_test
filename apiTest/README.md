# apiTest

ffmpeg api test demo base on FFmpeg 4.4.1


# Compile

1. Change the `FFMPEG_INC` and `FFMPEG_LIB` in `CMakeLists.txt` to your ffmpeg lib dir

2.
```shell
mkdir build

cmake ..

make
```

# Usage

`./apiTest <mp4_file_path>`

This project contain several demo

You can switch between different demo by changing the value of the `DEMO_PART` macro in `main.c`

# Update log

2024-2-21: Configuring the compile environment, add `openFile` demo

2024-2-22: Add `setDemuxer` and `decoderTest` demo