//
// Created by Administrator on 2019/9/12.
//
//类的静态成员变量需要在类外分配内存空间

#ifndef TESTPLAYER_AUDIO_H
#define TESTPLAYER_AUDIO_H

//#include "FPlayer.h"
#include "FFmpeg.h"
#include "OpenSL.h"

class Audio {
public:
    static double get_audio_clock();

    static double get_audio_pts_clock();

    static void set_audio_clock(double pts);

    int synchronize_audio(int nb_samples);

    static void slBufferCallback();

    int open_stream();

    void release();

    static bool must_feed;
    static pthread_mutex_t a_mutex;
    static pthread_cond_t a_cond;

private:
    static Clock audio_clk;

    static void *audioProcess(void *arg);
    AVStream *audio_stream = NULL;
    AVCodecContext *audio_dec_ctx = NULL;
    OpenSL openSL;
    SwrContext *swr_context;
    uint8_t *dst_data;
    pthread_t p_audio_tid;
    bool thread_flag = true;
};


#endif //TESTPLAYER_AUDIO_H