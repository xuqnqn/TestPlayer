//
// Created by DMing on 2019/9/14.
//

#ifndef TESTPLAYER_FFAV_H
#define TESTPLAYER_FFAV_H


#include "log.h"
#include <pthread.h>
#include <list>
#include <android/native_window.h>
#include <android/native_window_jni.h>

extern "C" {
#include <libavutil/log.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/timestamp.h>
#include <libavutil/samplefmt.h>
#include <libavutil/time.h>
#include <libavcodec/avcodec.h>
}

struct Clock {
    double pts;           /* clock base */
    double last_updated;
};

struct FPacket{
    AVPacket* avPacket;
    bool is_seek;
    bool checkout_time;
};

extern FPacket* alloc_packet();

extern void free_packet(FPacket* packet);

extern int startPlayer(const char *src_filename, ANativeWindow *window);

extern int open_codec_context(int *stream_idx, AVCodecContext **dec_ctx,
                              AVFormatContext *fmt_ctx, AVMediaType type);

extern double get_master_clock();

extern double get_video_pts_clock();

extern void set_video_clock(double pts);

extern double get_video_clock();

extern double get_audio_clock();

extern double get_audio_pts_clock();

extern void set_audio_clock(double pts);

extern void seek_frame(float percent);

extern AVFormatContext *fmt_ctx;

extern int video_stream_id;
extern int audio_stream_id;

extern AVStream *video_stream;
extern AVStream *audio_stream;

extern pthread_cond_t c_cond;
extern pthread_mutex_t c_mutex;

extern std::list<FPacket *> audio_pkt_list;
extern std::list<FPacket *> video_pkt_list;

extern bool check_video_is_seek();

extern bool check_audio_is_seek();

extern void decode_packet(AVPacket *pkt);

extern FPacket *audio_packet;

extern FPacket *video_packet;

extern bool want_audio_seek;
extern bool want_video_seek;

extern void seek_frame_if_need(AVPacket *pkt);

#endif //TESTPLAYER_FFAV_H
