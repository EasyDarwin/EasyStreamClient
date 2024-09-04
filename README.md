# EasyStreamClient

EasyStreamClient是一款支持File、RTSP、RTMP、HTTP等各种流媒体协议的音视频提取功能组件，支持H.264、H.265、PCM、AAC等各种音视频编码格式输出，支持Windows、Linux、Android、iOS、ARM等各种平台。EasyStreamClient support all kinds of streaming protocol, callback video & audio data，you can use this as easy ffmpeg !

## 编译与运行

- **EasyStreamClient**：以客户端的形式，从流地址URL将音视频获取到本地；
	
	Windows编译方法，

    	Visual Studio 2010 编译：./EasyStreamClient-master/win/EasyStreamClient.sln

	Linux编译方法，
		
		chmod +x ./Buildit
		./Buildit

	Usage，
		
		--------------------------------------------------------------
		EasyStreamClient.exe -d <rtsp-url>[ -m <transport-mode> -s <save-file>]
		Help Mode:   EasyStreamClient.exe -h
		rtsp-url : source rtsp address
		transport-mode : tcp or udp, default is tcp
		save-file : yes or no, default is yes
		For example: EasyStreamClient.exe -d rtsp://admin:admin@192.168.2.100/11 -m tcp -s yes
		--------------------------------------------------------------


### RTSPSourceCallBack数据回调说明
EasyStreamClient可以回调出多种类型的数据：

	#define EASY_SDK_VIDEO_FRAME_FLAG			/* 视频帧数据 */
	#define EASY_SDK_AUDIO_FRAME_FLAG			/* 音频帧数据 */
	#define EASY_SDK_EVENT_FRAME_FLAG			/* 事件帧数据 */
	#define EASY_SDK_RTP_FRAME_FLAG				/* RTP帧数据 */
	#define EASY_SDK_SDP_FRAME_FLAG				/* SDP帧数据 */
	#define EASY_SDK_MEDIA_INFO_FLAG			/* 媒体类型数据 */

EASY\_SDK\_VIDEO\_FRAME\_FLAG数据可支持多种视频格式：
		
	#define EASY_SDK_VIDEO_CODEC_H265			/* H265  */
	#define EASY_SDK_VIDEO_CODEC_H264			/* H264  */
	#define	EASY_SDK_VIDEO_CODEC_MJPEG			/* MJPEG */
	#define	EASY_SDK_VIDEO_CODEC_MPEG4			/* MPEG4 */

视频帧标识支持

	#define EASY_SDK_VIDEO_FRAME_I				/* I帧 */
	#define EASY_SDK_VIDEO_FRAME_P				/* P帧 */
	#define EASY_SDK_VIDEO_FRAME_B				/* B帧 */
	#define EASY_SDK_VIDEO_FRAME_J				/* JPEG */


> ***当回调出RTSP_FRAME_INFO->codec为EASY\_SDK\_VIDEO\_CODEC\_H264数据，EASY_FRAME_INFO->type为EASY\_SDK\_VIDEO\_FRAME\_I关键帧时，我们输出的数据结构为SPS+PPS+I的组合***：
		
		|-----sps-----|-----pps-----|-----I Frame-----|
		|             |             |                 |
		0--------reserved1------reserved2-----------length


> ***当回调出EASY_FRAME_INFO->codec为EASY\_SDK\_VIDEO\_CODEC\_H265数据，EASY_FRAME_INFO->type为EASY\_SDK\_VIDEO\_FRAME\_I关键帧时，我们输出的数据结构为VPS+SPS+PPS+I的组合***：
		
		|-----vps-----|-----sps-----|-----pps-----|-----I Frame-----|
		|             |             |             |                 |
		0--------reserved1-----reserved2------reserved3-----------length


EASY\_SDK\_AUDIO\_FRAME\_FLAG数据可支持多种音频格式：
	
	#define EASY_SDK_AUDIO_CODEC_AAC			/* AAC */
	#define EASY_SDK_AUDIO_CODEC_G711A			/* G711 alaw*/
	#define EASY_SDK_AUDIO_CODEC_G711U			/* G711 ulaw*/
	#define EASY_SDK_AUDIO_CODEC_G726			/* G726 */

## 更多流媒体音视频资源

EasyDarwin开源流媒体服务器：<a href="https://www.easydarwin.org" target="_blank" title="EasyDarwin开源流媒体服务器">www.EasyDarwin.org</a>
