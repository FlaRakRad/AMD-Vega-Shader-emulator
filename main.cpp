#include "libs/vega.hpp"
#include <iostream>
#include <string>
#include <bitset>

int main()
{
	std::string input_bits;
	uint32_t S0 = 0;
	uint32_t D = 0;
	bool SCC = true;

	std::cout << "Insert your number, uint32_t \ncurrent status: 0b" << std::bitset<32>(S0) << std::endl;
	std::cout << "Insert:		0b";
	std::cin >> input_bits;

	try 
	{
        S0 = static_cast<uint32_t>(std::bitset<32>(input_bits).to_ulong());
    }	
	catch (...) 
	{
        std::cerr << "Invalid bit string!" << std::endl;
        return 1;
	}
	vega::SOP1_instructions::S_NOT_B32::execute(S0, D, SCC);
	std::cout << "Midle unswer:   0b" << std::bitset<32>(D) << std::endl;
	vega::SOP1_instructions::S_MOV_B32::execute(D, S0);
	vega::SOP1_instructions::S_BCNT0_I32_B32::execute(S0, D, SCC);

	std::cout << "Your answer is: 0b" << std::bitset<32>(D) << std::endl;
	return 0;
}
