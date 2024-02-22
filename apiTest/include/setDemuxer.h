#ifndef SET_DEMUXER_H
#define SET_DEMUXER_H

#include <stdio.h>
#include <stdlib.h>

#include "libavformat/avformat.h"
#include "libavutil/avutil.h"

int ffmpeg_set_demuxer_arg(char *filename);

#endif