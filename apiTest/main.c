#include <stdio.h>
#include <stdlib.h>

#include "libavformat/avformat.h"
#include "libavutil/avutil.h"

int main(int argc, char* argv[])
{
    printf("FFmpeg version: %s\n", av_version_info());
    // av_log_set_level(AV_LOG_DEBUG);

    AVFormatContext *fmt_ctx = NULL;
    int type = 2;
    int err;

    if(argc != 2)
    {
        printf("Usage: %s <file_path>\n", argv[0]);
        return -1;
    }

    char *filename = argv[1];
    // char filename[] = "../resource/juren-30s.mp4";

    fmt_ctx = avformat_alloc_context();
    if(!fmt_ctx)
    {
        printf("error code %d \n", AVERROR(ENOMEM));
        return 1;
    }

    if (type == 1)
    {
        if((err = avformat_open_input(&fmt_ctx,filename,NULL,NULL)) < 0)
        {
            printf("%d: error : %s\n", __LINE__, av_err2str(err));
        }
        else
        {
            printf("open success\n");
            printf("filename : %s \n", fmt_ctx->url);
            printf("duration : %ld s\n", fmt_ctx->duration);
            printf("nb_streams : %u \n", fmt_ctx->nb_streams);
            for (int i = 0; i < fmt_ctx->nb_streams;i++)
            {
                printf("Stream codec type : %d \n", fmt_ctx->streams[i]->codecpar->codec_type);
            }
            printf("iformat name : %s \n", fmt_ctx->iformat->name);
            printf("iformat long name : %s \n", fmt_ctx->iformat->long_name);
        }
    }

    if(type == 2)
    {
        AVDictionary *format_opts = NULL;
        av_dict_set(&format_opts, "probesize", "32", 0);

        if ((err = avformat_open_input(&fmt_ctx, filename, NULL, &format_opts)) < 0)
        {
            printf("%d: error : %s\n", __LINE__, av_err2str(err));
        }
        else
        {
            printf("open success\n");
            avformat_find_stream_info(fmt_ctx, NULL);
            printf("filename : %s \n", fmt_ctx->url);
            printf("duration : %ld \n", fmt_ctx->duration / AV_TIME_BASE);
            printf("nb_streams : %u \n", fmt_ctx->nb_streams);
            for (int i = 0; i < fmt_ctx->nb_streams; i++)
            {
                printf("Stream codec type : %d \n", fmt_ctx->streams[i]->codecpar->codec_type);
            }
            printf("iformat name : %s \n", fmt_ctx->iformat->name);
            printf("iformat long name : %s \n", fmt_ctx->iformat->long_name);
        }
        av_dict_free(&format_opts);
    }

    return 0;
}
