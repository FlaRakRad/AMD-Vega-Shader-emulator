All info is taken from: 
https://docs.amd.com/v/u/en-US/vega-shader-instruction-set-architecture


AMD Vega (GCN/RDNA) Shader Emulator
* An instruction-accurate emulator for AMD GPU with architecture GCN 5.0 (Vega)

Key-features
* ISA Compliance: all coerence with ISA documentation
* Portability
* Hybrid Optimization
* Instruction-Level Granularity: every instruction is special functional block using for debuging and modulation


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
