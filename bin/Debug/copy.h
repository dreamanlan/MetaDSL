@@ifndef("PRORES_DECODER_H")@@define("PRORES_DECODER_H")@@ifdef("__cplusplus")extern "C"
{
	@@endif()@@ifndef("PR_PIXEL_FORMAT_DEFINED")typedef enum
	{
		kPRFormat_2vuy "=" "2vuy";
		kPRFormat_v210 "=" "v210";
		kPRFormat_v216 "=" "v216";
		kPRFormat_y416 "=" "y416";
		kPRFormat_r4fl "=" "r4fl";
		kPRFormat_R10k "=" "R10k";
		kPRFormat_r210 "=" "r210";
		kPRFormat_b64a "=" "b64a";
	}
	PRPixelFormat;
	@@define("PR_PIXEL_FORMAT_DEFINED")@@endif()typedef enum
	{
		kPRFullSize;
		kPRHalfSize;
		kPRQuarterSize;
	}
	PRDownscaleMode;
	typedef struct PRDecoder "*" PRDecoderRef;
	struct PRPixelBuffer
	{
		unsigned char "*" baseAddr;
		int rowBytes;
		PRPixelFormat format;
		int width;
		int height;
	};
	typedef struct PRPixelBuffer PRPixelBuffer;
	int PRBytesPerRowNeededInPixelBuffer(int frameWidth, PRPixelFormat pixelFormat, PRDownscaleMode downscaleMode);
	PRDecoderRef PROpenDecoder(int numThreads, void("*" threadStartupCallback)());
	int PRDecodeFrame(PRDecoderRef decoder, const void "*" compressedFrame, int compressedFrameSize, PRPixelBuffer "*" destinationBuffer, PRDownscaleMode downscaleMode, bool ignoreAlpha);
	void PRCloseDecoder(PRDecoderRef decoder);
	@@ifdef("__cplusplus");
}
@@endif()@@endif();
