#pragma once

#include <cstdint>
#include <string>
#include <sys/types.h>
#include <unordered_map>
#include <type_traits>

struct SOP1_Base {
    virtual void run(uint32_t S0, uint32_t& D, bool& SCC) = 0;
    virtual ~SOP1_Base() = default;
};

struct SOP2_Base {
    virtual void run(uint32_t S0, uint32_t S1, uint32_t& D, bool& SCC) = 0;
    virtual ~SOP2_Base() = default;
};

extern std::unordered_map<std::string, SOP1_Base*> instruction_registry_sop1;
extern std::unordered_map<std::string, SOP2_Base*> instruction_registry_sop2;

template<typename T>
void call_execute_sop1(uint32_t S0, uint32_t& D, bool& SCC) {
    if constexpr (requires { T::execute(uint32_t{}, D, SCC); }) {
        T::execute(S0, D, SCC);
    }
    else if constexpr (requires { T::execute(uint32_t{}, D); }) {
        T::execute(S0, D);
    }
    else if constexpr (requires { T::execute(uint64_t{}, (uint32_t*)nullptr, uint8_t{}, SCC); }) {
        T::execute((uint64_t)S0, &D, 0, SCC); 
    }
    else if constexpr (requires { T::execute(uint64_t{}, (uint32_t*)nullptr, uint8_t{}); }) {
        T::execute((uint64_t)S0, &D, 0);
    }
}

// Вызов для SOP2 (2 источника)
template<typename T>
void call_execute_sop2(uint32_t S0, uint32_t S1, uint32_t& D, bool& SCC) {
    if constexpr (requires { T::execute(uint32_t{}, uint32_t{}, D); }) {
        T::execute(S0, S1, D);
    }
    else if constexpr (requires { T::execute(uint32_t{}, uint32_t{}, D, SCC); }) {
        T::execute(S0, S1, D, SCC);
    }
}


#define REGISTER_SOP1(CLASS_NAME) \
class CLASS_NAME##_Runner : public SOP1_Base { \
public: \
    void run(uint32_t S0, uint32_t& D, bool& SCC) override { \
        call_execute_sop1<CLASS_NAME>(S0, D, SCC); \
    } \
}; \
inline static bool CLASS_NAME##_registered = []() { \
    instruction_registry_sop1[#CLASS_NAME] = new CLASS_NAME##_Runner(); \
    return true; \
}();

#define REGISTER_SOP2(CLASS_NAME) \
class CLASS_NAME##_RunnerSOP2 : public SOP2_Base { \
public: \
    void run(uint32_t S0, uint32_t S1, uint32_t& D, bool& SCC) override { \
        call_execute_sop2<CLASS_NAME>(S0, S1, D, SCC); \
    } \
}; \
inline static bool CLASS_NAME##_registered = []() { \
    instruction_registry_sop2[#CLASS_NAME] = new CLASS_NAME##_RunnerSOP2(); \
    return true; \
}();

namespace vega
{
    namespace SOP2 // Base: 0x80000000
    {
        static constexpr uint32_t BASE = 0x80000000;

        struct S_ADD_U32 // Opcode: 0
        {
            static constexpr uint8_t  ID = 0;
            static constexpr int LATENCY = 1;
            static constexpr const char* NAME = "S_ADD_U32";
            static constexpr const char* DESK = "Add unsigned 32-bit integers.";

            static void execute(uint32_t S0, uint32_t S1, uint32_t& D, bool& SCC)
            {
                uint64_t temp = static_cast<uint64_t>(S0) + static_cast<uint64_t>(S1);
                D = static_cast<uint32_t>(temp);
                SCC = (temp >= 0x100000000ULL); 
            }
            static constexpr uint32_t hex() { return BASE | (ID << 23); }
        };

        struct S_SUB_U32 // Opcode: 1
        {
            static constexpr uint8_t  ID = 1;
            static constexpr int LATENCY = 1;
            static constexpr const char* NAME = "S_SUB_U32";
            static constexpr const char* DESK = "Sub unsigned 32-bit integers.";

            static void execute(uint32_t S0, uint32_t S1, uint32_t& D, bool& SCC)
            {
                D = S0 - S1;
                SCC = (S1 > S0); 
            }
            static constexpr uint32_t hex() { return BASE | (ID << 23); }
        };
    };

	namespace SOP1 // Base: 0xBE800000
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
				uint32_t result = 0;
				for (int i = 0; i < 32; ++i) 
				{
					if ((S0 >> i) & 1) result |= (1U << (31 - i));
				}
				D = result;
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

        struct S_FF0_I32_B64 // Opcode: 15
        {
            static constexpr uint8_t  ID = 15;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_FF0_I32_B64";
			static constexpr const char* DESK = "Find First 0 (zero).";

            static void execute(uint64_t S0, uint32_t& D)
            {
                if (S0 == 0xFFFFFFFFFFFFFFFFULL) 
                {
                    D = 0xFFFFFFFF;
                }
                else 
                {
                    for (int i = 0; i < 64; ++i) 
                    {
                        if (((S0 >> i) & 1) == 0) 
                        {
                            D = static_cast<uint32_t>(i);
                            return;
                        }
                    }
                }
            }
            static constexpr uint32_t hex() { return BASE | (ID << 8); }
        };

        struct S_FF1_I32_B32 // Opcode: 16
        {
            static constexpr uint8_t  ID = 16;
			static constexpr int LATENCY = 1;
			static constexpr const char* NAME = "S_FF0_I32_B32";
			static constexpr const char* DESK = "Find First 1 (one).";

            static void execute(uint32_t S0, uint32_t& D)
            {
                if (S0 == 0) 
                {
                    D = 0xFFFFFFFF;
                }
                else 
                {
                    for (int i = 0; i < 32; ++i) 
                    {
                        if (((S0 >> i) & 1) == 1) 
                        {
                            D = static_cast<uint32_t>(i);
                            return;
                        }
                    }
                }
            }
            static constexpr uint32_t hex() { return BASE | (ID << 8); }
        };

        struct S_FF1_I32_B64 // Opcode: 17
        {
            static constexpr uint8_t  ID = 17;
            static constexpr int LATENCY = 1;
            static constexpr const char* NAME = "S_FF1_I32_B64";
            static constexpr const char* DESK = "Find first 1 (one).";

            static void execute(uint64_t S0, uint32_t& D)
            {
                if (S0 == 0) 
                {
                  D = 0xFFFFFFFF;
                }
                else 
                {
                    for (int i = 0; i < 64; ++i) 
                    {
                        if (((S0 >> i) & 1) == 1) 
                        {
                            D = static_cast<uint32_t>(i);
                            return;
                        }
                    }
                }
            }
            static constexpr uint32_t hex() { return BASE | (ID << 8); }
        };

        struct S_FLBIT_I32_B32 // Opcode: 18
        {
            static constexpr uint8_t  ID = 18;
            static constexpr int LATENCY = 1;
            static constexpr const char* NAME = "S_FLBIT_I32_B32";
            static constexpr const char* DESK = "Find last bit (count leading zeros) in 32-bit value.";

            static void execute(uint32_t S0, uint32_t& D)
            {
                if (S0 == 0) 
                {
                    D = 0xFFFFFFFF;
                }
                else 
                {
                    for (int i = 31; i >= 0; --i) 
                    {
                        if (((S0 >> i) & 1) == 1) 
                        {
                            D = static_cast<uint32_t>(31 - i);
                            return;
                        }
                    }
                }
            }
            static constexpr uint32_t hex() { return BASE | (ID << 8); }
        };

        struct S_FLBIT_I32_B64 // Opcode: 19
        {
            static constexpr uint8_t  ID = 19;
            static constexpr int LATENCY = 1;
            static constexpr const char* NAME = "S_FLBIT_I32_B64";
            static constexpr const char* DESK = "Find last bit (count leading zeros) in 64-bit value.";

            static void execute(uint64_t S0, uint32_t& D)
            {
                if (S0 == 0) 
                {
                    D = 0xFFFFFFFF;
                }
                else 
                {
                    for (int i = 63; i >= 0; --i) 
                    {
                        if (((S0 >> i) & 1ULL) == 1) 
                        {
                            D = static_cast<uint32_t>(63 - i);
                            return;
                        }
                    }
                }
            }
            static constexpr uint32_t hex() { return BASE | (ID << 8); }
        };
    };	    
}
