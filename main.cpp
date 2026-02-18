#include <iostream>
#include <cstdint>
#include <bitset>
#include <string>

class SOP1_instructions 
{
public:
    static constexpr uint32_t BASE = 0xBE800000;

    struct S_BREV_B32 
    {
        static constexpr uint8_t  ID   = 8;
        static constexpr const char* NAME = "S_BREV_B32";
        static constexpr const char* DESC = "Reverse bits.";

        static void execute(uint32_t src, uint32_t& dest) 
        {
            uint32_t result = 0;
            for (int i = 0; i < 32; ++i) 
            {
                if ((src >> i) & 1) result |= (1U << (31 - i));
            }
            dest = result;
        }
        
        static constexpr uint32_t hex() { return BASE | (ID << 8); }
    };
};

int main() 
{
    std::string binary_input;
    std::cout << "Set input (32 bits): ";
    std::cin >> binary_input;

    uint32_t S0 = std::bitset<32>(binary_input).to_ulong();
    uint32_t D = 0;

    SOP1_instructions::S_BREV_B32::execute(S0, D);

    std::cout << "Instruction: " << SOP1_instructions::S_BREV_B32::NAME << std::endl;
    std::cout << "Opcode HEX:  0x" << std::hex << SOP1_instructions::S_BREV_B32::hex() << std::dec << std::endl;
    std::cout << "Input:  " << std::bitset<32>(S0) << " (" << S0 << ")" << std::endl;
    std::cout << "Output: " << std::bitset<32>(D) << " (" << D << ")" << std::endl;

    return 0;
}
