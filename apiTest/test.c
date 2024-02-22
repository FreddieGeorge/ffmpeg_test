#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum API_TEST
{
    API_TEST_OPEN_INPUT = 0,
    API_TEST_SET_DEMUXER,
    API_TEST_DECODER_TEST,
    API_TEST_BUTT,

};

#define DEMO_PART API_TEST_SET_DEMUXER

#include "openFile.h"
#include "setDemuxer.h"
#include "decoderTest.h"

const char *get_file_extension(const char *filename)
{
    const char *dot = strrchr(filename, '.'); // 找到最后一个点的位置
    if (!dot || dot == filename)
        return "";  // 没有点或者点在开头，返回空字符串
    return dot + 1; // 返回点之后的字符串，即后缀
}

int main(int argc, char *argv[])
{
    printf("FFmpeg version: %s\n", av_version_info());
    // av_log_set_level(AV_LOG_DEBUG);

    if (argc != 2)
    {
        printf("Usage: %s <file_path>\n", argv[0]);
        return -1;
    }

    char *filename = argv[1];

    // get ext
    const char *extension = get_file_extension(filename);

#ifndef DEMO_PART
    av_log(NULL, AV_LOG_ERROR, "DEMO_PART macro is needed\n");
    return -1;
#endif

    printf("DEMO_PART: %d\n", DEMO_PART);

#if DEMO_PART == API_TEST_OPEN_INPUT
    ffmpeg_open_file(filename, FFMPEG_READ_TYPE_MP4);
#elif DEMO_PART == API_TEST_SET_DEMUXER
    ffmpeg_set_demuxer_arg(filename);
#else
    av_log(NULL, AV_LOG_ERROR, "DEMO_PART macro is undefined\n");
#endif

    return 0;
}
