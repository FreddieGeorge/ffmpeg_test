# ffmpeg_test

ffmpeg learning project, which contains several demos.

The code and tutorials are based on [FFmpeg-Principle](https://github.com/lokenetwork/FFmpeg-Principle/tree/main) and [FFmpeg原理介绍](https://ffmpeg.xianwaizhiyin.net/)

1. `imgCheck`, T.B.D
2. `demoTemplate`, ffmpeg project template based on cmake
3. `apiTest`, ffmpeg basic api learning demo

# Env

ubuntu18.04

gcc 8.4.0

cmake 3.25.1

ffmpeg-n4.4.11

ffmpeg configure param

```shell
./configure --prefix=/home/flork/ffmpeg/build64/ffmpeg-4.4-ubuntu \
--enable-gpl \
--enable-nonfree \
--enable-debug=3 \
--disable-optimizations \
--disable-asm \
--disable-stripping 
```
