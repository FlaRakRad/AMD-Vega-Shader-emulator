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

		struct S_CMOV_B32 // Opcode: 2
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

		struct S_CMOV_B64 // Opcode: 3
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

		struct S_NOT_B32 // Opcode: 4
		{
			static constexpr uint8_t  ID = 4;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_NOT_B32";
			static void execute(uint32_t S0, uint32_t& D, bool& SCC)
			{
				D = ~S0;
				SCC = (D != 0);
			}
			static constexpr uint32_t hex() { return BASE | (ID << 8); }
		};

		struct S_NOT_B64 // Opcode: 5
		{
			static constexpr uint8_t  ID = 5;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_NOT_B64";
			static void execute(uint64_t S0, uint32_t* SGPR, uint8_t SDST, bool& SCC)
			{
				uint64_t result = ~S0;
				SGPR[SDST]     = static_cast<uint32_t>(result & 0xFFFFFFFF);
			   SGPR[SDST + 1] = static_cast<uint32_t>(result >> 32);
				SCC = (result != 0);
			}
			static constexpr uint32_t hex() { return BASE | (ID << 8); }
		};

		struct S_WQM_B32 // Opcode: 6
		{
			static constexpr uint8_t  ID = 6;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_WQM_B32";

			static void execute(uint32_t S0, uint32_t& D, bool& SCC) 
			{
				uint32_t result = 0;
				for (int q = 0; q < 8; ++q) 
				{
					uint32_t quad_mask = (0xF << (q * 4)); 
					if (S0 & quad_mask) 
					{
						result |= quad_mask;
					}
				}
				D = result;
				SCC = (D != 0);
			}
			static constexpr uint32_t hex() { return BASE | (ID << 8); }
		};

		struct S_WQM_B64 // Opcode: 7
		{
			static constexpr uint8_t  ID = 7;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_WQM_B64";

			static void execute(uint64_t S0, uint32_t* SGPR, uint8_t SDST, bool& SCC) 
			{
				uint64_t result = 0;
				for (int q = 0; q < 16; ++q) 
				{
					uint64_t quad_mask = (0xFULL << (q * 4));
					if (S0 & quad_mask) 
					{
						result |= quad_mask;
					}
				}
				SGPR[SDST]     = static_cast<uint32_t>(result & 0xFFFFFFFF);
				SGPR[SDST + 1] = static_cast<uint32_t>(result >> 32);
				SCC = (result != 0);
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

		struct S_BREV_B64 // Opcode: 9
		{
			static constexpr uint8_t  ID = 9;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_BREV_B64";
			static constexpr const char* DESC = "Reverse bits.";

			static void execute(uint64_t S0, uint32_t* SGPR, uint8_t SDST)
			{
				uint64_t result = 0;
				for (int i = 0; i < 64; ++i)
				{
					if ((S0 >> i) & 1ULL)
					{	
						result |= (1ULL << (63 - i));
					}
				}
				SGPR[SDST]	   = static_cast<uint32_t>(result & 0xFFFFFFFF);
				SGPR[SDST + 1] = static_cast<uint32_t>(result >> 32);
			}
			static constexpr uint32_t hex() { return BASE | (ID << 8); }
		};

		struct S_BCNT0_I32_B32 // Opcode: 10
		{
			static constexpr uint8_t  ID = 10;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_BCNT0_I32_B32";
			static constexpr const char* DESC = "Bit Count 0 (zero).";

			static void execute(uint32_t S0, uint32_t& D, bool& SCC)
			{
				uint32_t result = 0;
				for (int i = 0; i < 32; ++i)
				{
					if (((S0 >> i) & 1) ==0)
					{
						result++;
					}
				}
				D	= result;
				SCC = (D != 0);
			}
			static constexpr uint32_t hex() { return BASE | (ID << 8); }
		};

		struct S_BCNT0_I32_B64 // Opcode: 11
		{
			static constexpr uint8_t  ID = 11;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_BCNT0_I32_B64";
			static constexpr const char* DESC = "Bit Count 0 (zero).";

			static void execute(uint64_t S0, uint32_t& D, bool& SCC)
            {
                uint32_t result = 0;
                for (int i = 0; i < 64; ++i)
                {
                    if (((S0 >> i) & 1ULL) == 0)
                    {
                        result++;
                    }
                }
                D = result;
                SCC = (D != 0);
            }
			static constexpr uint32_t hex() { return BASE | (ID << 8); }
		};

		struct S_BCNT1_I32_B32 // Opcode: 12
		{
			static constexpr uint8_t  ID = 12;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_BCNT1_I32_B32";
			static constexpr const char* DESC = "Bit Count 1 (ones).";

			static void execute(uint32_t S0, uint32_t& D, bool& SCC)
			{
				uint32_t result = 0;
				for (int i = 0; i < 32; ++i)
				{
					if (((S0 >> i) & 1) ==1)
					{
						result++;
					}
				}
				D  = result;
				SCC = (D != 0);
			}
			static constexpr uint32_t hex() { return BASE | (ID << 8); }
		};

		struct S_BCNT1_I32_B64 // Opcode: 13
		{
			static constexpr uint8_t  ID = 13;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_BCNT1_I32_B64";
			static constexpr const char* DESC = "Bit Count 1 (ones).";

			static void execute(uint64_t S0, uint32_t& D, bool& SCC)
            {
                uint32_t result = 0;
                for (int i = 0; i < 64; ++i)
                {
                    if (((S0 >> i) & 1ULL) == 1)
                    {
                        result++;
                    }
                }
                D = result;
                SCC = (D != 0);
            }
			static constexpr uint32_t hex() { return BASE | (ID << 8); }
		};

		struct S_FF0_I32_B32 // Opcode: 14
		{
			static constexpr uint8_t  ID = 14;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_FF0_I32_B32";
			static constexpr const char* DESK = "Find First 0 (zero).";

			static void execute(uint32_t S0, uint32_t& D, bool SCC);
			static void execute(uint32_t S0, uint32_t& D) 
            {
                if (S0 == 0xFFFFFFFF) 
                {
                    D = 0xFFFFFFFF;
                }
                else 
                {
                  #if defined (__GNUC__) || defined (__clang__)
                    D = static_cast<uint32_t>(__builtin_ctz(~S0));
                  #else
                    uint32_t result = 0;
                    for (int i = 0; i < 32; ++i) 
                    {
                        if (((S0 >> i) & 1) == 0) 
                        {
                            result = i;
                            break;
                        }
                    }
                    D = result;
				  #endif
                }
            }
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
