
class CDemosaic
{
	private:
		short *bBuffer;
		short *gBuffer;
		short *rBuffer;

		int image_width, image_height;

		void interpolateLuminance(short *src);
		void interpolateChrominance(short *src);

	public:
		CDemosaic();
		~CDemosaic();
		void demosaic(unsigned char *src, unsigned char *dst, int w, int h);
};

#define V_OFFSET 0
