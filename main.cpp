#include "libs/vega.hpp"
#include <iostream>
#include <string>
#include <bitset>

int main()
{
using namespace vega;

	std::string input_bitsS0;
    std::string input_bitsS1;
	uint32_t S0 = 0;
    uint32_t S1 = 0;
	uint32_t D = 0;
	bool SCC = true;

	std::cout << "Insert your number, uint32_t \ncurrent status: 0b" << std::bitset<32>(S0) << std::endl;
	std::cout << "Insert:		0b";
	std::cin >> input_bitsS0;

	std::cout << "Insert your number, uint32_t \ncurrent status: 0b" << std::bitset<32>(S1) << std::endl;
	std::cout << "Insert:		0b";
    std::cin >> input_bitsS1;

	try 
	{
        S0 = static_cast<uint32_t>(std::bitset<32>(input_bitsS0).to_ulong());
    }	
	catch (...) 
	{
        std::cerr << "Invalid bit string!" << std::endl;
        return 1;
	}

	try 
	{
        S1 = static_cast<uint32_t>(std::bitset<32>(input_bitsS1).to_ulong());
    }	
	catch (...) 
	{
        std::cerr << "Invalid bit string!" << std::endl;
        return 1;
	}

 /*   SOP1::S_FLBIT_I32_B32::execute(S0, D);
        std::cout << "Midle unswer:   0b" << std::bitset<32>(D) << std::endl;
    SOP1::S_MOV_B32::execute(D, S0); */

    SOP2::S_ADD_U32::execute(S0, S1, D);


	std::cout << "Your answer is: 0b" << std::bitset<32>(D) << std::endl;
	std::cout << "Your answer is: 0d" << std::dec << D << std::endl;
	return 0;
}
