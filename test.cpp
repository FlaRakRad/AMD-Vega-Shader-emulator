#include "libs/vega1.hpp"
#include <iostream>
#include <bitset>

int main()
{
	/*int D = vega::SOP1_instructions::S_WQM_B64::ID;
	std::cout << D << std::endl;*/
	
	uint32_t S0 = 0b100101101000000001111011101101; 
    uint32_t D = 0;
    bool SCC = false;

	vega::SOP1_instructions::S_WQM_B32::execute(S0, D, SCC);
	std::cout << std::bitset<32>(D) << std::endl;


	return 0;
}
