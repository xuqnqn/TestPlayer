//
// Created by Administrator on 2019/9/12.
//
//类的静态成员变量需要在类外分配内存空间

#ifndef TESTPLAYER_AUDIO_H
#define TESTPLAYER_AUDIO_H

#include "FFmpeg.h"
#include "OpenSL.h"
#include "AV.h"

class Audio : AV {
public:
    Audio(UpdateTimeFun *updateTimeFun);

    int synchronize_audio(int nb_samples);

    static void slBufferCallback();

    int open_stream();

    void pause();

    void resume();

    void release();

    static bool must_feed;
    static pthread_mutex_t a_mutex;
    static pthread_cond_t a_cond;

private:
    static void *audioProcess(void *arg);
    OpenSL openSL;
    SwrContext *swr_context;
    uint8_t *dst_data;
    pthread_t p_audio_tid;
    bool thread_finish = false;
    UpdateTimeFun *updateTimeFun = NULL;
    pthread_cond_t pause_cond;
    pthread_mutex_t pause_mutex;
    bool is_pause = false;
};


#endif //TESTPLAYER_AUDIO_H
