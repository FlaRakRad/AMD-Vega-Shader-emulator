All info is taken from: 
https://docs.amd.com/v/u/en-US/vega-shader-instruction-set-architecture


AMD Vega (GCN/RDNA) Shader Emulator
* An instruction-accurate emulator for AMD GPU with architecture GCN 5.0 (Vega)

Key-features
* ISA Compliance: all coerence with ISA documentation
* Portability
* Hybrid Optimization
* Instruction-Level Granularity: every instruction is special functional block using for debuging and modulation

### 12.1 SOP2 Insturctions (In Progress)
```text
SOP2    S_ADD_U32        Done    Adds S0 with S1 32-bit (unsigned)
SOP2    S_SUB_U32        Done    Subs S1 from S0 32-bit (unsigned)
SOP2    S_ADD_I32        Done    Adds S0 with S1 32-bit (signed)
SOP2    S_SUB_I32        Done    Subs S1 from S0 32-bit (signed)
SOP2    S_ADDC_U32       Done    Adds S0, S1 and SCC (carry-in) 32-bit
SOP2    S_SUBB_U32       Done    Subs S1 and SCC (borrow-in) from S0 32-bit
SOP2    S_MIN_I32        Done    Minimum of signed S0 and S1 32-bit
SOP2    S_MIN_U32        Done    Minimum of unsigned S0 and S1 32-bit
SOP2    S_MAX_I32        Done    Maximum of signed S0 and S1 32-bit
SOP2    S_MAX_U32        Done    Maximum of unsigned S0 and S1 32-bit
SOP2    S_CSELECT_B32    Done    Conditional select 32-bit based on SCC
SOP2    S_CSELECT_B64    Done    Conditional select 64-bit based on SCC
SOP2    S_AND_B32        Done    Bitwise AND 32-bit
SOP2    S_AND_B64        Done    Bitwise AND 64-bit
SOP2    S_OR_B32         Done    Bitwise OR 32-bit
SOP2    S_OR_B64         Done    Bitwise OR 64-bit
SOP2    S_XOR_B32        Done    Bitwise XOR 32-bit
SOP2    S_XOR_B64        Done    Bitwise XOR 64-bit
SOP2    S_ANDN2_B32      Done    Bitwise S0 AND NOT S1 32-bit
SOP2    S_ANDN2_B64      Done    Bitwise S0 AND NOT S1 64-bit
SOP2    S_ORN2_B32       Done    Bitwise S0 OR NOT S1 32-bit
SOP2    S_ORN2_B64       Done    Bitwise S0 OR NOT S1 64-bit
SOP2    S_NAND_B32       Done    Bitwise NOT (S0 AND S1) 32-bit
SOP2    S_NAND_B64       Done    Bitwise NOT (S0 AND S1) 64-bit
SOP2    S_NOR_B32        Done    Bitwise NOT (S0 OR S1) 32-bit
SOP2    S_NOR_B64        Done    Bitwise NOT (S0 OR S1) 64-bit
SOP2    S_XNOR_B32       Done    Bitwise NOT (S0 XOR S1) 32-bit
SOP2    S_XNOR_B64       Done    Bitwise NOT (S0 XOR S1) 64-bit
SOP2    S_LSHL_B32       Done    Logical Shift Left 32-bit
SOP2    S_LSHL_B64       Done    Logical Shift Left 64-bit
SOP2    S_LSHR_B32       Done    Logical Shift Right 32-bit
SOP2    S_LSHR_B64       Done    Logical Shift Right 64-bit
```
### 12.3 SOP1 Instructions (In Progress)
```text
SOP1    S_MOV_B32       Done    Move 32-bit
SOP1    S_MOV_B64       Done    Move 64-bit
SOP1    S_CMOV_B32      Done    Conditional Move 32-bit
SOP1    S_CMOV_B64      Done    Conditional Move 64-bit
SOP1    S_NOT_B32       Done    Bitwise Negation 32-bit
SOP1    S_NOT_B64       Done    Bitwise Negation 64-bit
SOP1    S_WQM_B32       Done    Whole Quad Mode 32-bit
SOP1    S_WQM_B64       Done    Whole Quad Node 64-bit
SOP1    S_BREV_B32      Done    Bit Reverse 32-bit
SOP1    S_BREV_B64      Done    Bit Reverse 64-bit     
SOP1    S_BCNT0_I32_B32 Done    Count of zeors 32-bit
SOP1    S_BCNT0_I32_B64 Done    Count of zeors 64-bit
SOP1    S_BCNT1_I32_B32 Done    Count of ones 32-bit
SOP1    S_BCNT1_I32_B64 Done    Count of ones 64-bit
SOP1    S_FF0_I32_B32   Done    Finds First zero 32-bit
SOP1    S_FF0_I32_B64   Done    Finds First zero 64-bit
SOP1    S_FF1_I32_B32   Done    Finds First one 32-bit
SOP1    S_FF1_I32_B64   Done    Finds first one 64-bit
SOP1    S_FLBIT_I32_B32 Done    Finds last bit 32-bit
SOP1    S_FLBIT_I32_B64 Done    Finds last bit 64-bit
