#pragma once

#include "main.h"
#include "VideoFrameQueue.h"


class VideoPlayer {
public:
	VideoPlayer(char* filepath, player_stat_t* is);
	~VideoPlayer();
	int video_playing();

public:
	player_stat_t* is;

private:
	int video_play_thread();
	int video_refresh(double* remaining_time);
	void display_one_frame();
	int video_decode_thread();
	int decode_frame(AVFrame* pFrame);
	double compute_target_delay(double delay);
	//void forward_func(int second);

private:
	std::shared_ptr<std::thread> m_pPlay;
	std::shared_ptr<std::thread> m_pDecode;

	AVFormatContext* pFormatCtx; //解封装
	AVCodecContext* pCodecCtx; //解码
	AVStream* pStream;
	AVCodec* pCodec;
	AVFrame* pFrame, * pFrameYUV; //帧数据
	AVPacket* packet;	//解码前的压缩数据（包数据）
	int index;
	unsigned char* out_buffer;	//数据缓冲区
	struct SwsContext* img_convert_ctx;
	VideoFrameQueue fq = VideoFrameQueue();

	int screen_w = 0, screen_h = 0;
	SDL_Window* screen; //SDL弹出的窗口
	SDL_Renderer* sdlRenderer; //渲染器，渲染SDL_Texture至SDL_Window
	SDL_Texture* sdlTexture; //纹理
	SDL_Rect sdlRect;

	double refresh_rate;	//刷新率=每秒多少帧

};