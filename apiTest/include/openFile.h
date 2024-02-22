#ifndef OPEN_FILE_H
#define OPEN_FILE_H

#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#include "libavformat/avformat.h"
#include "libavutil/avutil.h"



int ffmpeg_open_file(char *filename, FFMPEG_READ_TYPE file_class);

#endif