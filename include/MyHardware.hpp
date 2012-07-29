#ifndef _MY_HARDAWARE_HPP_
#define _MY_HARDAWARE_HPP_

class Cpu
{
public:
	enum EVendor {
		eVendorUnknow = 0,
		eVendorIntel,
		eVendorAmd
	};

	enum ESimd {
		eSimdUnknown = 0,
		eSimdNone,
		eSimdMMX,
		eSimdExtendedMMX,
		eSimd3DNow,
		eSimd3DNow2, //3DNowProfessional 3DNow+
		eSimdSSE,
		eSimdSSE2,
		eSimdSSE3,
		eSimdSSSE3,
		eSimdSSE41,
		eSimdSSE42,
		eSimdSSE4a
	};

public:
	Cpu();

	EVendor getCpuVendor();

	bool HasSimdMMX();
	bool HasSimdExtendedMMX();
	bool HasSimdSSE();
	bool HasSimdSSE2();
	bool HasSimdSSE3();
	bool HasSimdSSSE3();
	bool HasSimdSSE4_1();
	bool HasSimdSSE4_2();
	bool HasSimdSSE4a();

	bool HasSimdAVX();
	bool HasSimdAVX2();

	bool HasHyperThreading();

private:
	unsigned long eax, ebx, ecx, edx;
};



#endif
