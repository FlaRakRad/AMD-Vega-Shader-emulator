#include "libs/vega.hpp"
#include <iostream>
#include <string>
#include <bitset>

struct Debug 
{
    uint32_t S0 = 0;
    uint32_t S1 = 0;
    uint32_t D = 0;
    bool SCC = false;

    void ask_S0() 
    {
        std::string input;
        std::cout << "Insert S0 current: \n0b" << std::bitset<32>(S0) << "\n0b";
        std::cin >> input;
        try { S0 = static_cast<uint32_t>(std::bitset<32>(input).to_ulong()); }
        catch (...) { std::cerr << "Invalid bits!\n"; }
    }

    void ask_S1() 
    {
        std::string input;
        std::cout << "Insert S1 current: \n0b" << std::bitset<32>(S1) << "\n0b";
        std::cin >> input;
        try { S1 = static_cast<uint32_t>(std::bitset<32>(input).to_ulong()); }
        catch (...) { std::cerr << "Invalid bits!\n"; }
    }

    void echo_D() 
    {
        std::cout << "\n--- [" << "] ---" << std::endl;
        std::cout << "D (bin): 0b" << std::bitset<32>(D) << std::endl;
        std::cout << "D (hex): 0x" << std::hex << D << std::endl;
        std::cout << "D (dec): " << std::dec << D << std::endl;

    }
    
    void echo_SCC()
    {
        std::string SCC_STRING;
        if (SCC == 1) { SCC_STRING = "true"; }
        else { SCC_STRING = "false"; }
        std::cout << "SCC:     " << SCC_STRING << std::endl;
        std::cout << "----------------------\n" << std::endl;
    }
};

int main() 
{
    using namespace vega;
    using namespace SOP2;
    using namespace SOP1;
    Debug a;

    a.ask_S0(); a.ask_S1();
    S_ADD_U32::execute(a.S0, a.S1, a.D, a.SCC); S_JUMP_B32::execute([0x00000001]);
    a.echo_D(); a.echo_SCC();
    S_MOV_B32::execute(a.D, a.S0);
    a.ask_S1();
    S_SUB_U32::execute(a.S0, a.S1, a.D, a.SCC);
    a.echo_D(); a.echo_SCC();
    S_MOV_B32::execute(a.D, a.S0);
    a.ask_S1();
    S_XNOR_B32::execute(a.S0, a.S1, a.D, a.SCC);
    a.echo_D(); a.echo_SCC();
    S_MOV_B32::execute(a.D, a.S0);
    S_BREV_B32::execute(a.S0, a.D);
    a.echo_D(); a.echo_SCC();

    std::cout << "0b" << std::bitset<32>(a.D) << std::endl;

    return 0;
}
