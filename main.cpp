#include <iostream>
#include <cstdint>
#include <bitset>

class SOP1_instructions
{
public:
                                                  // upcode: 8
	void S_BREV_B32(uint32_t src, uint32_t& dest) // description: Reverse bits.
	{
    	uint32_t result = 0;
    
    	for (int i = 0; i < 32; ++i) 
		{
        	if ((src >> i) & 1) 
			{
            	result |= (1U << (31 - i));
        	}
		}
    
		dest = result;
	}
};

int main() 
{
    SOP1_instructions Vega;
    std::string binary_input;

    std::cout << "set input ";
    std::cin >> binary_input;

    uint32_t S0 = std::bitset<32>(binary_input).to_ulong();
    uint32_t D = 0;

    Vega.S_BREV_B32(S0, D);

    std::cout << "Input: " << std::bitset<32>(S0) << std::endl;
    std::cout << "Output:  " << std::bitset<32>(D) << std::endl;

    return 0;
}
