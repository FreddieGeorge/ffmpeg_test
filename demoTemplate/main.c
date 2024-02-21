#include <stdio.h>
#include <stdlib.h>

#include "libavformat/avformat.h"
#include "libavutil/avutil.h"

int main(int argc, char* argv[])
{
    printf("FFmpeg lib version: %s\n", av_version_info());
    av_log_set_level(AV_LOG_DEBUG);
    return 0;
}
