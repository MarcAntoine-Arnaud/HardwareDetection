#include <MyHardware.hpp>

#include <iostream>

int main( int argc, char** argv )
{
	Cpu cpu;
	Cpu::EVendor vendor = cpu.getCpuVendor();
	switch( vendor )
	{
		case Cpu::eVendorUnknow: std::cout << "unknown cpu" << std::endl; break;
		case Cpu::eVendorIntel: std::cout << "Intel cpu" << std::endl; break;
		case Cpu::eVendorAmd:  std::cout << "Amd cpu" << std::endl; break;
	}

	std::cout << "has mmx : " << ( cpu.HasSimdMMX() ? " yes" : "no" ) << std::endl;
	std::cout << "has extended mmx : " << ( cpu.HasSimdExtendedMMX() ? " yes" : "no" ) << std::endl;
	std::cout << "has SSE : " << ( cpu.HasSimdSSE() ? " yes" : "no" ) << std::endl;
	std::cout << "has SSE 2 : " << ( cpu.HasSimdSSE2() ? " yes" : "no" ) << std::endl;
	std::cout << "has SSE 3 : " << ( cpu.HasSimdSSE3() ? " yes" : "no" ) << std::endl;
	std::cout << "has SSSE 3 : " << ( cpu.HasSimdSSSE3() ? " yes" : "no" ) << std::endl;
	std::cout << "has SSE 4.1 : " << ( cpu.HasSimdSSE4_1() ? " yes" : "no" ) << std::endl;
	std::cout << "has SSE 4.2 : " << ( cpu.HasSimdSSE4_2() ? " yes" : "no" ) << std::endl;
	std::cout << "has SSE 4a : " << ( cpu.HasSimdSSE4a() ? " yes" : "no" ) << std::endl;
	std::cout << "has AVX : " << ( cpu.HasSimdAVX() ? " yes" : "no" ) << std::endl;
	std::cout << "has AVX2 : " << ( cpu.HasSimdAVX2() ? " yes" : "no" ) << std::endl;
	std::cout << "has hyper threading : " << ( cpu.HasHyperThreading()  ? " yes" : "no" ) << std::endl;

	cpu.HasHyperThreading();

	return 0;
}
