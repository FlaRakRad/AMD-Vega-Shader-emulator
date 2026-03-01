#include "libs/vega.hpp"
#include <iostream>
#include <bitset>
#include <string>

int main()
{
	uint32_t D = vega::SOP1_instructions::S_WQM_B32::hex();
	std::cout << "0x" << std::hex << D << std::endl;
	std::cout << std::dec << D << std::endl;
	std::cout << "0b" << std::bitset<32>(D) << std::endl;


	return 0;
}
