#pragma once

class CDemosaic
{
	private:
		unsigned short *bBuffer;
		unsigned short *gBuffer;
		unsigned short *rBuffer;

		int image_width, image_height;

		void interpolateLuminance(unsigned short *src);
		void interpolateChrominance(unsigned short *src);

	public:
		CDemosaic();
		~CDemosaic();
		void demosaic(unsigned char *src, unsigned char *dst, int w, int h);
};

#define V_OFFSET 0
