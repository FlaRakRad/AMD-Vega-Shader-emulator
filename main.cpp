#include <iostream>
#include <cstdint>
#include <bitset>
#include <string>

namespace vega
{
	namespace SOP1_instructions // Base: 0xBE800000
	{
		static constexpr uint32_t BASE = 0xBE800000;
		
		struct S_MOV_B32 // Opcode: 0
		{
			static constexpr uint8_t  ID = 0;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_MOV_B32";
			static void execute(uint32_t S0, uint32_t& D) 
			{
				D = S0;
			}
			static constexpr uint32_t hex() { return BASE | (ID << 8); }
		};

		struct S_MOV_B64 // Opcode: 1
		{
			static constexpr uint8_t  ID = 1;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_MOV_B64";
			static void execute(uint64_t S0, uint32_t* SGPR, uint8_t SDST) 
			{
				SGPR[SDST]     = static_cast<uint32_t>(S0 & 0xFFFFFFFF);
			
				SGPR[SDST + 1] = static_cast<uint32_t>(S0 >> 32);
			}
			static constexpr uint32_t hex() { return BASE | (ID << 8); }
		};

		struct S_CMOV_B32 // Opcode 2
		{
			static constexpr uint8_t  ID = 2;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_CMOV_B32";
			static void execute(uint32_t S0, uint32_t& D, bool SCC)
			{
				if (SCC)
				{
					D = S0;
				}
			}

			static constexpr uint32_t hex() { return BASE | (ID << 8); }
		};

		struct S_CMOV_B64 // Opcode 3
		{
			static constexpr uint8_t  ID = 3;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_CMOV_B64";
			static void execute(uint64_t S0, uint32_t* SGPR, uint8_t SDST, bool SCC)
			{
				if (SCC)
				{
					SGPR[SDST]     = static_cast<uint32_t>(S0 & 0xFFFFFFFF);
					SGPR[SDST + 1] = static_cast<uint32_t>(S0 >> 32);
				}
			}
			static constexpr uint32_t hex() { return BASE | (ID << 8); }
		};
		
		struct S_BREV_B32 // Opcode: 8
		{
			static constexpr uint8_t  ID = 8;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_BREV_B32";
			static constexpr const char* DESC = "Reverse bits.";

			static void execute(uint32_t S0, uint32_t& D) 
			{
			 #if defined (__GNUC__) || defined (__clang__)
				D = __builtin_bitreverse32(S0);
			 #else
				uint32_t result = 0;
				for (int i = 0; i < 32; ++i) 
				{
					if ((S0 >> i) & 1) result |= (1U << (31 - i));
				}
				D = result;
			 #endif
			}
			static constexpr uint32_t hex() { return BASE | (ID << 8); }
		};
	};
}
int main() 
{
	// Just for debuging!
    std::string binary_input;
    std::cout << "Set input (32 bits): ";
    std::cin >> binary_input;

    uint32_t S0 = std::bitset<32>(binary_input).to_ulong();
    uint32_t D = 0;

	vega::SOP1_instructions::S_BREV_B32::execute(S0, D);

    std::cout << "Instruction: " << vega::SOP1_instructions::S_BREV_B32::NAME << std::endl;
    std::cout << "Opcode HEX:  0x" << std::hex << vega::SOP1_instructions::S_BREV_B32::hex() << std::dec << std::endl;
    std::cout << "Input:  " << std::bitset<32>(S0) << " (" << S0 << ")" << std::endl;
    std::cout << "Output: " << std::bitset<32>(D) << " (" << D << ")" << std::endl;
    return 0;
}
