/*
	Copyright (c) 2012-2024 EasyDarwin.org  All rights reserved.
	Github: https://github.com/easydarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
#include <stdio.h>
#include <string.h>
#include "getopt.h"
#include "EasyStreamClientAPI.h"

FILE* fVideo = NULL;
FILE* fAudio = NULL;

char* fStreamURL = NULL;	//stream source addrs
int fTransType = 0;			//0 : TCP    1 : UDP
bool fSaveFile = true;		//true : save file     false : don't save

Easy_Handle fStreamHandle = 0;

int Easy_APICALL __StreamClientCallBack(void* _channelPtr, int _frameType, void* pBuf, EASY_FRAME_INFO* _frameInfo)
{
	if (_frameType == EASY_SDK_VIDEO_FRAME_FLAG)
	{
		if(_frameInfo->codec == EASY_SDK_VIDEO_CODEC_H264)
		{
			if(fSaveFile)
			{
				if(fVideo == NULL)
				{
					char filename[100] = {0};
					sprintf(filename, "./video_%s.H264", fTransType?"udp":"tcp");
					fVideo = ::fopen(filename,"wb");
				}

				::fwrite(pBuf, 1, _frameInfo->length, fVideo);
			}
			/* 
				|H.264 SPS+PPS+IDR|
				|---------------------|----------------|-------------------------------------|
				|                     |                |                                     |
				0-----------------reserved1--------reserved2-------------------------------length
			*/
			if (_frameInfo->type == EASY_SDK_VIDEO_FRAME_I)
			{
				unsigned int spsLen,ppsLen,iFrameLen = 0;
				spsLen = _frameInfo->reserved1;							// SPS
				ppsLen = _frameInfo->reserved2 - _frameInfo->reserved1;	// PPS
				iFrameLen = _frameInfo->length - _frameInfo->reserved2;	// IDR

				printf("Get I H264(%d * %d) SPS/PPS/IDR Len:%d/%d/%d \ttimestamp:%u.%u\n",_frameInfo->width, _frameInfo->height, spsLen, ppsLen, iFrameLen, _frameInfo->timestamp_sec, _frameInfo->timestamp_usec);
			}
			else if (_frameInfo->type == EASY_SDK_VIDEO_FRAME_P)
			{
				printf("Get P H264(%d * %d) Len:%d \ttimestamp:%u.%u\n",_frameInfo->width, _frameInfo->height, _frameInfo->length, _frameInfo->timestamp_sec, _frameInfo->timestamp_usec);
			}
		}
		/*
			|H.265 VPS+SPS+PPS+IDR|
			|-----vps-----|-----sps-----|-----pps-----|-----I Frame-----|
			|             |             |             |                 |
			0--------reserved1-----reserved2------reserved3-----------length
		*/
		else if(_frameInfo->codec == EASY_SDK_VIDEO_CODEC_H265)
		{
			if(fSaveFile)
			{
				if(fVideo == NULL)
				{
					char filename[100] = {0};
					sprintf(filename, "./video_%s.H265", fTransType?"udp":"tcp");
					fVideo = ::fopen(filename,"wb");
				}

				::fwrite(pBuf, 1, _frameInfo->length, fVideo);
			}
			if (_frameInfo->type == EASY_SDK_VIDEO_FRAME_I)
			{

				unsigned int vpsLen,spsLen,ppsLen,iFrameLen = 0;
				vpsLen = _frameInfo->reserved1;							// VPS
				spsLen = _frameInfo->reserved2 - _frameInfo->reserved1;	// SPS
				ppsLen = _frameInfo->reserved3 - _frameInfo->reserved2;	// PPS
				iFrameLen = _frameInfo->length - _frameInfo->reserved3;	// IDR

				printf("Get I H265(%d * %d) VPS/SPS/PPS/IDR Len:%d/%d/%d/%d \ttimestamp:%u.%u\n",_frameInfo->width, _frameInfo->height, vpsLen, spsLen, ppsLen, iFrameLen, _frameInfo->timestamp_sec, _frameInfo->timestamp_usec);
			}
			else if (_frameInfo->type == EASY_SDK_VIDEO_FRAME_P)
			{
				printf("Get P H265(%d * %d) Len:%d \ttimestamp:%u.%u\n",_frameInfo->width, _frameInfo->height, _frameInfo->length, _frameInfo->timestamp_sec, _frameInfo->timestamp_usec);
			}
		}
		else if (_frameInfo->codec == EASY_SDK_VIDEO_CODEC_MJPEG)
		{
			if(fSaveFile)
			{
				if(fVideo == NULL)
				{
					char filename[100] = {0};
					sprintf(filename, "./video_%s.mjpeg", fTransType?"udp":"tcp");
					fVideo = ::fopen(filename,"wb");
				}

				::fwrite(pBuf, 1, _frameInfo->length, fVideo);
			}

			printf("Get MJPEG Len:%d \ttimestamp:%u.%u\n", _frameInfo->length, _frameInfo->timestamp_sec, _frameInfo->timestamp_usec);
		}
		else if (_frameInfo->codec == EASY_SDK_VIDEO_CODEC_MPEG4)
		{
			if(fSaveFile)
			{
				if(fVideo == NULL)
				{
					char filename[100] = {0};
					sprintf(filename, "./video_%s.mpeg4", fTransType?"udp":"tcp");
					fVideo = ::fopen(filename,"wb");
				}

				::fwrite(pBuf, 1, _frameInfo->length, fVideo);
			}

			printf("Get MPEG4 Len:%d \ttimestamp:%u.%u\n", _frameInfo->length, _frameInfo->timestamp_sec, _frameInfo->timestamp_usec);
		}
	}
	else if (_frameType == EASY_SDK_AUDIO_FRAME_FLAG)
	{
		if (_frameInfo->codec == EASY_SDK_AUDIO_CODEC_AAC)
		{
			if(fSaveFile)
			{
				if(fAudio == NULL)
				{
					char filename[100] = {0};
					sprintf(filename, "./audio_%s.aac", fTransType?"udp":"tcp");
					fAudio = ::fopen(filename,"wb");
				}
			}
			printf("Get AAC Len:%d \ttimestamp:%u.%u\n", _frameInfo->length, _frameInfo->timestamp_sec, _frameInfo->timestamp_usec);
		}
		else if (_frameInfo->codec == EASY_SDK_AUDIO_CODEC_G711A)
		{
			if(fSaveFile)
			{
				if(fAudio == NULL)
				{
					char filename[100] = {0};
					sprintf(filename, "./audio_%s.pcma", fTransType?"udp":"tcp");
					fAudio = ::fopen(filename,"wb");
				}
			}
			printf("Get PCMA Len:%d \ttimestamp:%u.%u\n", _frameInfo->length, _frameInfo->timestamp_sec, _frameInfo->timestamp_usec);
		}
		else if (_frameInfo->codec == EASY_SDK_AUDIO_CODEC_G711U)
		{
			if(fSaveFile)
			{
				if(fAudio == NULL)
				{
					char filename[100] = {0};
					sprintf(filename, "./audio_%s.pcmu", fTransType?"udp":"tcp");
					fAudio = ::fopen(filename,"wb");
				}
			}
			printf("Get PCMU Len:%d \ttimestamp:%u.%u\n", _frameInfo->length, _frameInfo->timestamp_sec, _frameInfo->timestamp_usec);
		}
		else if (_frameInfo->codec == EASY_SDK_AUDIO_CODEC_G726)
		{
			if(fSaveFile)
			{
				if(fAudio == NULL)
				{
					char filename[100] = {0};
					sprintf(filename, "./audio_%s.g726", fTransType?"udp":"tcp");
					fAudio = ::fopen(filename,"wb");
				}
			}

			printf("Get G.726 Len:%d \ttimestamp:%u.%u\n", _frameInfo->length, _frameInfo->timestamp_sec, _frameInfo->timestamp_usec);
		}

		if(fSaveFile)
			::fwrite(pBuf, 1, _frameInfo->length, fAudio);
	}

	//EASY_STREAM_CLIENT_STATE_CONNECTING = 1,		 /* 连接中 */
	//EASY_STREAM_CLIENT_STATE_CONNECTED,              /* 连接成功 */
	//EASY_STREAM_CLIENT_STATE_CONNECT_FAILED,         /* 连接失败 */
	//EASY_STREAM_CLIENT_STATE_CONNECT_ABORT,          /* 连接中断 */
	//EASY_STREAM_CLIENT_STATE_PUSHING,                /* 推流中 */
	//EASY_STREAM_CLIENT_STATE_DISCONNECTED,           /* 断开连接 */
	//EASY_STREAM_CLIENT_STATE_EXIT,					 /* 退出连接 */
	//EASY_STREAM_CLIENT_STATE_ERROR

	else if (_frameType == EASY_SDK_EVENT_FRAME_FLAG)
	{
		if (_frameInfo->codec == EASY_STREAM_CLIENT_STATE_CONNECTING)
		{
			printf("Connecting:%s, %s ...\n", fStreamURL, pBuf?pBuf:"null" );
		}

		if (_frameInfo->codec == EASY_STREAM_CLIENT_STATE_CONNECTED)
		{
			printf("Connected:%s, %s ...\n", fStreamURL, pBuf?pBuf:"null" );
		}

		else if (NULL != _frameInfo && _frameInfo->codec == EASY_STREAM_CLIENT_STATE_CONNECT_FAILED)
		{
			printf("ConnectFail:%s, %s ...\n", fStreamURL, pBuf?pBuf:"null" );
		}

		else if (NULL != _frameInfo && _frameInfo->codec == EASY_STREAM_CLIENT_STATE_CONNECT_ABORT)
		{
			printf("ConnectAbord:%s, %s ...\n", fStreamURL, pBuf?pBuf:"null" );
		}

		else if (NULL != _frameInfo && _frameInfo->codec == EASY_STREAM_CLIENT_STATE_DISCONNECTED)
		{
			printf("Disconnected:%s, %s ...\n", fStreamURL, pBuf?pBuf:"null" );
		}

		else if (NULL != _frameInfo && _frameInfo->codec == EASY_STREAM_CLIENT_STATE_EXIT)
		{
			printf("Exit:%s, %s ...\n", fStreamURL, pBuf?pBuf:"null" );
		}
	}
	else if (_frameType == EASY_SDK_MEDIA_INFO_FLAG)
	{
		if(pBuf != NULL)
		{
			EASY_MEDIA_INFO_T mediainfo;
			memset(&mediainfo, 0x00, sizeof(EASY_MEDIA_INFO_T));
			memcpy(&mediainfo, pBuf, sizeof(EASY_MEDIA_INFO_T));
			printf("Get Media Info: video:%u fps:%u audio:%u channel:%u sampleRate:%u \n", 
				mediainfo.u32VideoCodec, mediainfo.u32VideoFps, mediainfo.u32AudioCodec, mediainfo.u32AudioChannel, mediainfo.u32AudioSamplerate);
		}
	}
	return 0;
}

void usage(char const* progName) 
{
  printf("Usage: %s <stream-url> \n", progName);
}

void PrintUsage(char const* progName)
{
	printf("Usage:\n");
	printf("--------------------------------------------------------------\n");
	printf("%s -d <stream-url>[ -m <transport-mode> -s <save-file>]\n", progName);
	printf("Help Mode:   %s -h \n", progName );
	printf("stream-url : source address\ntransport-mode : tcp or udp, default is tcp\nsave-file : yes or no, default is yes\n");
	printf("For example: %s -d \"http://devimages.apple.com/iphone/samples/bipbop/gear3/prog_index.m3u8\" -m tcp -s yes\n", progName); 
	printf("--------------------------------------------------------------\n");
}

int main(int argc, char** argv)
{
	printf("\n*****************EasyStreamClient-v3.1.240724*******************\n");

	int ch;
	// We need at least one "rtsp://" or "http://" or "rtmp://" or "tcp://" or "udp://" URL argument:
	if (argc < 2)
	{
		PrintUsage(argv[0]);
		printf("Press Enter exit...\n");
		getchar();
		return 1;
	}

	while ((ch = getopt(argc,argv, "h:d:m:s:")) != EOF) 
	{
		switch(ch)
		{
		case 'h':
			PrintUsage(argv[0]);
			return 0;
			break;
		case 'd':
			fStreamURL = optarg;
			break;
		case 'm':
			if((strlen(optarg) == 3) && ((0 == strcmp(optarg, "UDP"))|| (0 == strcmp(optarg, "udp"))))
			{
				fTransType = 1;
			}
			else
			{
				fTransType = 0;
			}

			break;
		case 's':
			if((strlen(optarg) == 2) && ((0 == strcmp(optarg, "NO"))|| (0 == strcmp(optarg, "no"))))
			{
				fSaveFile = false;
			}
			else
			{
				fSaveFile = true;
			}
			break;
		default:
			break;
		}
	}


	int init= EasyStreamClient_Init(&fStreamHandle, 0);

	if (NULL == fStreamHandle) return 0;
	
	EasyStreamClient_SetCallback(fStreamHandle, __StreamClientCallBack);

	if(fTransType == 0)
		EasyStreamClient_OpenStream(fStreamHandle, fStreamURL, EASY_RTP_OVER_TCP, NULL, 1000, 8, 0x00);
	else
		EasyStreamClient_OpenStream(fStreamHandle, fStreamURL, EASY_RTP_OVER_UDP, NULL, 1000, 8, 0x00);
		
	EasyStreamClient_SetAudioEnable(fStreamHandle, 1);

	printf("Press Enter exit...\n");
	getchar();
   
	EasyStreamClient_Deinit(fStreamHandle);
	fStreamHandle = NULL;


	getchar();
    return 0;
}
