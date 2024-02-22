#include "openFile.h"

int ffmpeg_open_file(char *filename, FFMPEG_READ_TYPE file_class)
{
    int err = 0;
    AVFormatContext *fmt_ctx = NULL;

    fmt_ctx = avformat_alloc_context();
    if (!fmt_ctx)
    {
        printf("error code %d \n", AVERROR(ENOMEM));
        return -1;
    }

    if (file_class == FFMPEG_READ_TYPE_MP4)
    {
        if ((err = avformat_open_input(&fmt_ctx, filename, NULL, NULL)) < 0)
        {
            printf("%d: error : %s\n", __LINE__, av_err2str(err));
        }
        else
        {
            printf("open success\n");
            printf("filename : %s \n", fmt_ctx->url);
            printf("duration : %ld sec\n", fmt_ctx->duration / AV_TIME_BASE);
            printf("nb_streams : %u \n", fmt_ctx->nb_streams);
            for (int i = 0; i < fmt_ctx->nb_streams; i++)
            {
                // printf("Stream codec type : %d \n", fmt_ctx->streams[i]->codecpar->codec_type); // num
                printf("Stream codec type : %s \n", av_get_media_type_string(fmt_ctx->streams[i]->codecpar->codec_type)); // string
            }
            printf("iformat name : %s \n", fmt_ctx->iformat->name);
            printf("iformat long name : %s \n", fmt_ctx->iformat->long_name);
        }
    }

    if (file_class == FFMPEG_READ_TYPE_FLV)
    {
        AVDictionary *format_opts = NULL;
        // 设置dict
        // AVDictionary是为了命令行的字符串传参这个需求而设计出来的
        av_dict_set(&format_opts, "probesize", "32", 0);
        // 设置fmt_ctx中的probesize为32
        // fmt_ctx->probesize = 32
        if ((err = avformat_open_input(&fmt_ctx, filename, NULL, &format_opts)) < 0)
        {
            printf("%d: error : %s\n", __LINE__, av_err2str(err));
        }
        else
        {
            printf("open success\n");
            avformat_find_stream_info(fmt_ctx, NULL);
            printf("filename : %s \n", fmt_ctx->url);
            printf("duration : %ld sec\n", fmt_ctx->duration / AV_TIME_BASE);
            printf("nb_streams : %u \n", fmt_ctx->nb_streams);
            for (int i = 0; i < fmt_ctx->nb_streams; i++)
            {
                // printf("Stream codec type : %d \n", fmt_ctx->streams[i]->codecpar->codec_type); // num
                printf("Stream codec type : %s \n", av_get_media_type_string(fmt_ctx->streams[i]->codecpar->codec_type)); // string
            }
            printf("iformat name : %s \n", fmt_ctx->iformat->name);
            printf("iformat long name : %s \n", fmt_ctx->iformat->long_name);
        }
        av_dict_free(&format_opts);
    }

    return err;
}