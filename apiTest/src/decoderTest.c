#include "decoderTest.h"

// ffmpeg解码功能测试demo

// int ffmpeg_decode_test(char* filename, FFMPEG_READ_TYPE type)
int ffmpeg_decode_test(char* filename)
{
    AVFormatContext *fmt_ctx = NULL;
    int ret = 0;
    int err;

    fmt_ctx = avformat_alloc_context();
    if(!fmt_ctx)
    {
        av_log(NULL, AV_LOG_ERROR, "%s(%d): error code %d\n", __FILE__, __LINE__, AVERROR(ENOMEM));
        return ENOMEM;
    }

    // open input
    if((err = avformat_open_input(&fmt_ctx,filename,NULL,NULL)) < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "%s(%d): avformat_open_input error : %s", __FILE__, __LINE__, av_err2str(err));
    }

    // if(type == 1)
    // {
        // 初始化上下文
    // if not NULL, will alloc a given codec
    AVCodecContext *avctx = avcodec_alloc_context3(NULL);

    // 把编码参数赋值到avctx中
    ret = avcodec_parameters_to_context(avctx, fmt_ctx->streams[0]->codecpar);
    if (ret < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "%s(%d): %s\n", __FILE__, __LINE__, av_err2str(ret));
        return ret;
    }

    av_log(NULL, AV_LOG_INFO, "get codec name :%s\n", avcodec_get_name(avctx->codec_id));

    // 根据视频流解析出来的编码类型获取AVCodec
    AVCodec *codec = avcodec_find_decoder(avctx->codec_id);
    // 开启解码器
    if ((ret = avcodec_open2(avctx, codec, NULL)) < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "%s(%d): %s\n", __FILE__, __LINE__, av_err2str(ret));
        return ret;
    }

    // AVPacket和AVFrame本身没有数据，只是管理/引用数据
    AVPacket *pkt = av_packet_alloc();
    AVFrame *frame = av_frame_alloc();

    int frame_num = 0;
    int read_end = 0;

    while (1)
    {
        if (read_end == 1)
            break;

        // 读取帧，实际读的是AVPacket，命名估计是历史原因导致的
        ret = av_read_frame(fmt_ctx, pkt);

        // 为什么1是音频流
        if (1 == pkt->stream_index)
        {
            // 如果是音频流，则擦包，并取消引用
            av_packet_unref(pkt);
            continue;
        }

        // 读取完文件,这时候 pkt 的 data 跟 size 应该是 null ？
        if (AVERROR_EOF == ret)
        {
            // 往AVCodecContext中发送一个AVPacket
            avcodec_send_packet(avctx, pkt);
            // 释放AVPacket
            av_packet_unref(pkt);

            // 不断从解码器中读取数据，直到没有数据
            while (1)
            {
                // read AVFrame
                ret = avcodec_receive_frame(avctx, frame);
                // 使用完后不需要调用av_frame_unref释放frame
                // 在avcodec_receive_frame中会自动释放

                if (ret == AVERROR(EAGAIN))
                {
                    // EGAIN表示需要更多AVPacket
                    // 跳出第一层循环继续获取AVPacket
                    break;
                }
                else if (ret == AVERROR_EOF)
                {
                    /* 提示 AVERROR_EOF 代表之前已经往 解码器发送了一个 data 跟 size 都是 NULL 的 AVPacket
                     * 发送 NULL 的 AVPacket 是提示解码器把所有的缓存帧全都刷出来。
                     * 通常只有在 读完输入文件才会发送 NULL 的 AVPacket，或者需要用现有的解码器解码另一个的视频流才会这么干。
                     */

                    // 跳出第二层for,文件解码完成
                    read_end = 1;
                    break;
                }
                else if (ret >= 0)
                {
                    // 解码出数据，打印信息

                    av_log(NULL, AV_LOG_INFO, "decode success --- \n");
                    av_log(NULL, AV_LOG_INFO, "width : %d , height : %d \n", frame->width, frame->height);
                    av_log(NULL, AV_LOG_INFO, "pts : %ld , duration : %ld \n", frame->pts, frame->pkt_duration);
                    av_log(NULL, AV_LOG_INFO, "format : %d\n", frame->format);
                    av_log(NULL, AV_LOG_INFO, "key_frame : %d\n", frame->key_frame);
                    av_log(NULL, AV_LOG_INFO, "AVPictureType : %c\n", av_get_picture_type_char(frame->pict_type));
                    int num = av_image_get_buffer_size(AV_PIX_FMT_YUV410P, 1920, 1080, 1);
                    av_log(NULL, AV_LOG_INFO, "num : %d\n", num);
                }
                else
                {
                    av_log(NULL, AV_LOG_ERROR, "other fail, ret = %d\n", ret);
                    return ret;
                }
            }
        } /* if(AVERROR_EOF == ret) */
        else if (ret == 0)
        {
        retry:
            if (avcodec_send_packet(avctx, pkt) == AVERROR(EAGAIN))
            {
                // 通常返回EAGAIN是因为ffmpeg内部的api有bug
                av_log(NULL, AV_LOG_ERROR, "Receive_frame and send_packet both returned EAGAIN, which is an API violation.\n");
                goto retry;
            }
            else
            {
                av_packet_unref(pkt);

                while (1)
                {
                    // read AVFrame
                    ret = avcodec_receive_frame(avctx, frame);
                    // 使用完后不需要调用av_frame_unref释放frame
                    // 在avcodec_receive_frame中会自动释放

                    if (ret == AVERROR(EAGAIN))
                    {
                        // EGAIN表示需要更多AVPacket
                        // 跳出第一层循环继续获取AVPacket
                        break;
                    }
                    else if (ret == AVERROR_EOF)
                    {
                        /* 提示 AVERROR_EOF 代表之前已经往 解码器发送了一个 data 跟 size 都是 NULL 的 AVPacket
                         * 发送 NULL 的 AVPacket 是提示解码器把所有的缓存帧全都刷出来。
                         * 通常只有在 读完输入文件才会发送 NULL 的 AVPacket，或者需要用现有的解码器解码另一个的视频流才会这么干。
                         */

                        // 跳出第二层for,文件解码完成
                        read_end = 1;
                        break;
                    }
                    else if (ret >= 0)
                    {
                        // 解码出数据，打印信息

                        av_log(NULL, AV_LOG_INFO, "decode success --- \n");
                        av_log(NULL, AV_LOG_INFO, "width : %d , height : %d \n", frame->width, frame->height);
                        av_log(NULL, AV_LOG_INFO, "pts : %ld , duration : %ld \n", frame->pts, frame->pkt_duration);
                        av_log(NULL, AV_LOG_INFO, "format : %d\n", frame->format);
                        av_log(NULL, AV_LOG_INFO, "key_frame : %d\n", frame->key_frame);
                        av_log(NULL, AV_LOG_INFO, "AVPictureType : %c\n", av_get_picture_type_char(frame->pict_type));
                        int num = av_image_get_buffer_size(AV_PIX_FMT_YUV410P, 1920, 1080, 1);
                        av_log(NULL, AV_LOG_INFO, "num : %d\n", num);

                        // 打印 yuv
                        // av_log(NULL, AV_LOG_INFO, " Y size : %d \n",frame->linesize[0]);
                        // av_log(NULL, AV_LOG_INFO, " U size : %d \n",frame->linesize[1]);
                        // av_log(NULL, AV_LOG_INFO, " V size : %d \n",frame->linesize[2]);

                        /*
                        //修改 yuv
                        for(int tt=0; tt < 5 ;tt++){
                            frame->data[0][tt] = 0xFF;
                        }
                        //拼接文件名
                        char yuv_pic_name[200] = "./yuv420p_";
                        char frame_num_str[10];
                        itoa(frame_num, frame_num_str, 10);
                        strcat(yuv_pic_name,frame_num_str);
                        //写入文件
                        FILE *fp = NULL;
                        fp = fopen(yuv_pic_name, "w+");
                        fwrite(frame->data[0] , 1, frame->width * frame->height, fp);
                        fwrite(frame->data[1] , 1, frame->width/2 * frame->height/2, fp);
                        fwrite(frame->data[2] , 1, frame->width/2 * frame->height/2, fp);
                        fclose(fp);

                        frame_num++;
                        if( frame_num > 10 ){
                            return 99;
                        }
                        */
                    }
                    else
                    {
                        av_log(NULL, AV_LOG_ERROR, "other fail, ret = %d\n", ret);
                        return ret;
                    }
                }
            }
        }
    }

    av_frame_free(&frame);
    av_packet_free(&pkt);

    avcodec_free_context(&avctx);
    avformat_close_input(&fmt_ctx);
    // }
}