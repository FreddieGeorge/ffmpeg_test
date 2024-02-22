#include "setDemuxer.h"


int ffmpeg_set_demuxer_arg(char* filename)
{
    AVFormatContext *fmt_ctx = NULL;
    int err;

    fmt_ctx = avformat_alloc_context();
    if(!fmt_ctx)
    {
        av_log(NULL, AV_LOG_ERROR, "%s(%d): error code: %d", __FILE__, __LINE__, AVERROR(ENOMEM));
        return -1;
    }

    // 设置多个参数
    // AVDictionary只能以指针指向堆内存的方式来使用
    // 因为 AVDictionary 这个类型的定义放在 dict.c 文件里面了，而这个 c 文件已经被编译器编译进库了
    // 编译器看不到这个结构体的实现了
    AVDictionary *fmt_opts = NULL;
    AVDictionaryEntry *t;
    // fmt_ctx->format_probesize:number of bytes to read maximally to identify format. just useful when decoding
    // 如果传NULL给av_dict_set，函数会自动给AVDictionary分配一个内存
    av_dict_set(&fmt_opts, "formatprobesize", "10485760", AV_DICT_MATCH_CASE);
    // export_all:Export unrecognized metadata entries
    av_dict_set(&fmt_opts, "export_all", "1", AV_DICT_MATCH_CASE);
    // 预留一个用不到的属性
    av_dict_set(&fmt_opts, "export_666", "1", AV_DICT_MATCH_CASE);

    av_log(NULL, AV_LOG_INFO, "AVdictionary num is %d\n", av_dict_count(fmt_opts));
    // 获取第一个属性
    if((t = av_dict_get(fmt_opts,"", NULL, AV_DICT_IGNORE_SUFFIX)))
    {
        av_log(NULL, AV_LOG_INFO, "Option key:%s , valueL %s \n", t->key, t->value);
    }

    if((err = avformat_open_input(&fmt_ctx,filename,NULL,&fmt_opts)) < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "%s(%d): avformat_open_input error : %s", __FILE__, __LINE__, av_err2str(err));
    }
    else
    {
        av_log(NULL, AV_LOG_INFO, "Open Success\n");
        av_log(NULL, AV_LOG_INFO, "duration: %ld s\n",fmt_ctx->duration / AV_TIME_BASE);
    }

    // 属性被用掉会从字典中删除,只剩下一个
    av_log(NULL, AV_LOG_INFO, "after avformat_open_input,AVdictionary num is %d\n", av_dict_count(fmt_opts));
    if ((t = av_dict_get(fmt_opts, "", NULL, AV_DICT_IGNORE_SUFFIX)))
    {
        av_log(NULL, AV_LOG_INFO, "Option key:%s , valueL %s \n", t->key, t->value);
    }

    av_dict_free(&fmt_opts); // 手动释放
}