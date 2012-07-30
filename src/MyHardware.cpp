
#include <MyHardware.hpp>
#if defined (_MSC_VER) || defined (__INTEL_COMPILER)
#include <intrin.h>
#endif


static inline void cpuid( int functionnumber, unsigned long& a, unsigned long& b, unsigned long& c, unsigned long& d )
{
#if defined (_MSC_VER) || defined (__INTEL_COMPILER) // Microsoft or Intel compiler, intrin.h included
        int output[4] = { -1 };
	__cpuidex(output, functionnumber, 0); // intrinsic function for CPUID
	a = output[0];
	b = output[1];
	c = output[2];
	d = output[3];
#elif defined(__GNUC__) // use inline assembly, Gnu/AT&T syntax
	__asm("cpuid" : "=a"(a),"=b"(b),"=c"(c),"=d"(d) : "a"(functionnumber),"c"(0) : );
#else // unknown platform. try inline assembly with masm/intel syntax
	unsigned long output[4];
	__asm {
		mov eax, functionnumber
		xor ecx, ecx
		cpuid;
		mov esi, output
		mov [esi],    eax
		mov [esi+4],  ebx
		mov [esi+8],  ecx
		mov [esi+12], edx
	}
	a = output[0];
	b = output[1];
	c = output[2];
	d = output[3];
#endif
}
//#define cpuid(in, a, b, c, d) asm("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));
/*
#define CPUID_VENDOR_AMD       "AuthenticAMD"
#define CPUID_VENDOR_INTEL     "GenuineIntel"
#define CPUID_VENDOR_VIA       "CentaurHauls"
#define CPUID_VENDOR_TRANSMETA "GenuineTMx86"
#define CPUID_VENDOR_CYRIX     "CyrixInstead"
#define CPUID_VENDOR_CENTAUR   "CentaurHauls"
#define CPUID_VENDOR_NEXGEN    "NexGenDriven"
#define CPUID_VENDOR_UMC       "UMC UMC UMC "
#define CPUID_VENDOR_SIS       "SiS SiS SiS "
#define CPUID_VENDOR_NSC       "Geode by NSC"
#define CPUID_VENDOR_RISE      "RiseRiseRise"
*/

#define CPUID_VENDOR_AMD   0x68747541
#define CPUID_VENDOR_INTEL 0x756e6547

#define CPUID_FLAG_AVX2    1 << 5  /* in ebx function 2*/
#define CPUID_FLAG_SSE3    1 << 0  /* in ecx function 1*/
#define CPUID_FLAG_SSE4A   1 << 6  /* in ecx function 1*/
#define CPUID_FLAG_SSSE3   1 << 9  /* in ecx function 1*/
#define CPUID_FLAG_SSE41   1 << 19 /* in ecx function 1*/
#define CPUID_FLAG_SSE42   1 << 20 /* in ecx function 1*/
#define CPUID_FLAG_AVX     1 << 28 /* in ecx function 1*/
#define CPUID_FLAG_MMX     1 << 23 /* in edx function 1*/
#define CPUID_FLAG_EXT_MMX 1 << 24 /* in edx function 1*/
#define CPUID_FLAG_SSE     1 << 25 /* in edx function 1*/
#define CPUID_FLAG_SSE2    1 << 26 /* in edx function 1*/
#define CPUID_FLAG_HTT     1 << 28 /* in edx function 1*/

Cpu::Cpu()
{

}

Cpu::EVendor Cpu::getCpuVendor()
{
	EVendor vendor = eVendorUnknow;
	cpuid( 0, eax, ebx, ecx, edx );
	switch(ebx)
	{
		case CPUID_VENDOR_INTEL:
			vendor = eVendorIntel;
			break;
		case CPUID_VENDOR_AMD:
			vendor = eVendorAmd;
			break;
		default:
			vendor = eVendorUnknow;
			break;
	}
	return vendor;
}

bool Cpu::HasSimdMMX()
{
	cpuid( 1, eax, ebx, ecx, edx );
        return ( edx & CPUID_FLAG_MMX );
}

bool Cpu::HasSimdExtendedMMX()
{
	cpuid( 1, eax, ebx, ecx, edx );
	return ( edx & CPUID_FLAG_EXT_MMX );
}

bool Cpu::HasSimdSSE()
{
	cpuid( 1, eax, ebx, ecx, edx );
	return ( edx & CPUID_FLAG_SSE );
}

bool Cpu::HasSimdSSE2()
{
	cpuid( 1, eax, ebx, ecx, edx );
	return ( edx & CPUID_FLAG_SSE2 );
}

bool Cpu::HasSimdSSE3()
{
	cpuid( 1, eax, ebx, ecx, edx );
	return ( ecx & CPUID_FLAG_SSE3 );
}

bool Cpu::HasSimdSSSE3()
{
	cpuid( 1, eax, ebx, ecx, edx );
	return ( ecx & CPUID_FLAG_SSSE3 );
}

bool Cpu::HasSimdSSE4_1()
{
	cpuid( 1, eax, ebx, ecx, edx );
	return ( ecx & CPUID_FLAG_SSE41);
}

bool Cpu::HasSimdSSE4_2()
{
	cpuid( 1, eax, ebx, ecx, edx );
	return ( ecx & CPUID_FLAG_SSE42 );
}

bool Cpu::HasSimdSSE4a()
{
	if( ! ( getCpuVendor() == eVendorAmd ) )
		return false;
	cpuid( 1, eax, ebx, ecx, edx );
	return ( ecx & CPUID_FLAG_SSE4A );
}

bool Cpu::HasSimdAVX()
{
	cpuid( 1, eax, ebx, ecx, edx );
	return ( ecx & CPUID_FLAG_AVX );
}

bool Cpu::HasSimdAVX2()
{
	cpuid( 2, eax, ebx, ecx, edx );
	return ( ecx & CPUID_FLAG_AVX2 );
}

bool Cpu::HasHyperThreading()
{
	cpuid( 1, eax, ebx, ecx, edx );
	return ( edx & CPUID_FLAG_HTT );
}


