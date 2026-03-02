#include "vega.hpp"

std::unordered_map<std::string, SOP1_Base*> instruction_registry_sop1;
std::unordered_map<std::string, SOP2_Base*> instruction_registry_sop2;

namespace vega
{
    namespace SOP2 
    {
        REGISTER_SOP2(S_ADD_U32)
    }

    namespace SOP1 
    {
        REGISTER_SOP1(S_MOV_B32)
        REGISTER_SOP1(S_MOV_B64)
        REGISTER_SOP1(S_CMOV_B32)
        REGISTER_SOP1(S_CMOV_B64)
        REGISTER_SOP1(S_NOT_B32)
        REGISTER_SOP1(S_NOT_B64)
        REGISTER_SOP1(S_WQM_B32)
        REGISTER_SOP1(S_WQM_B64)
        REGISTER_SOP1(S_BREV_B32)
        REGISTER_SOP1(S_BREV_B64)
        REGISTER_SOP1(S_BCNT0_I32_B32)
        REGISTER_SOP1(S_BCNT0_I32_B64)
        REGISTER_SOP1(S_BCNT1_I32_B32)
        REGISTER_SOP1(S_BCNT1_I32_B64)
        REGISTER_SOP1(S_FF0_I32_B32)
        REGISTER_SOP1(S_FF0_I32_B64)
        REGISTER_SOP1(S_FF1_I32_B32)
        REGISTER_SOP1(S_FF1_I32_B64)
        REGISTER_SOP1(S_FLBIT_I32_B32)
    }
}
