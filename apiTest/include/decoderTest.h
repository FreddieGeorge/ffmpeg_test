#ifndef DECODE_TEST_H
#define DECODE_TEST_H

#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#include "libavformat/avformat.h"
#include "libavutil/avutil.h"

int ffmpeg_decode_test(char *filename);

#endif