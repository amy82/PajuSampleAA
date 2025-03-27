
#define BGGR	1//4
#define RGGB	2//1
#define GRBG	4//2
#define GBRG	3//3

#define RCCC	5
#define CRCC	6
#define CCRC	7
#define CCCR	8

class CDemosaicRGGB
{
	private:
		unsigned short *bBuf_2B;// = NULL;
		unsigned short *gBuf_2B;// = NULL;
		unsigned short *rBuf_2B;// = NULL;

		BYTE *bBuf;// = NULL;
		BYTE *gBuf;// = NULL;
		BYTE *rBuf;// = NULL;

		int rows, cols;
		int colorOrder;

		void interpolateLuminance(const unsigned short *src);
		void interpolateChrominance(const unsigned short *src);
		void interpolateLuminance(const BYTE *src);
		void interpolateChrominance(const BYTE *src);

	public:
		CDemosaicRGGB();
		~CDemosaicRGGB();

		void Bayer2BGR(const unsigned short *pBayer, unsigned short *pBGR, int image_height, int image_width, int bayerPattern);
		void Bayer2BGR(const BYTE *pBayer, BYTE *pBGR, int image_height, int image_width, int bayerPattern);
};


