#include <iostream>
#include <unistd.h>
#include "../header/cpu.hh"
#include "../header/registers.hh"

cpu::cpu()
{
    for( int i = 0 ; i < 6 ; i++)
        registers.insert(std::make_pair(regnames[i],new register16()));
    frameCycles = 0;
    initializeInstructionTable();
    initializeCBInstructionTable();
    powerUpSequence();
}

cpu::~cpu()
{
    for( int i = 0; i < 6 ; i++)
        delete registers[regnames[i]];
}

void cpu::initializeInstructionTable(void)
{
    instructionTable[0x00] = &cpu::op_NOOP;
    instructionTable[0x01] = &cpu::op_LD_BCnn;
    instructionTable[0x02] = &cpu::op_LD_BCA;
    instructionTable[0x03] = &cpu::op_INC_BC;
    instructionTable[0x04] = &cpu::op_INC_B;
    instructionTable[0x05] = &cpu::op_DEC_B;
    instructionTable[0x06] = &cpu::op_LD_Bn;
    instructionTable[0x07] = &cpu::op_RLCA;
    instructionTable[0x08] = &cpu::op_LD_aaSP;
    instructionTable[0x09] = &cpu::op_ADD_HLBC;
    instructionTable[0x0A] = &cpu::op_LD_ABC;
    instructionTable[0x0B] = &cpu::op_DEC_BC;
    instructionTable[0x0C] = &cpu::op_INC_C;
    instructionTable[0x0D] = &cpu::op_DEC_C;
    instructionTable[0x0E] = &cpu::op_LD_Cn;
    instructionTable[0x0F] = &cpu::op_RRCA;

    instructionTable[0x10] = &cpu::op_STOP;
    instructionTable[0x11] = &cpu::op_LD_DEnn;
    instructionTable[0x12] = &cpu::op_LD_DEA;
    instructionTable[0x13] = &cpu::op_INC_DE;
    instructionTable[0x14] = &cpu::op_INC_D;
    instructionTable[0x15] = &cpu::op_DEC_D;
    instructionTable[0x16] = &cpu::op_LD_Dn;
    instructionTable[0x17] = &cpu::op_RLA;
    instructionTable[0x18] = &cpu::op_JR_n;
    instructionTable[0x19] = &cpu::op_ADD_HLDE;
    instructionTable[0x1A] = &cpu::op_LD_ADE;
    instructionTable[0x1B] = &cpu::op_DEC_DE;
    instructionTable[0x1C] = &cpu::op_INC_E;
    instructionTable[0x1D] = &cpu::op_DEC_E;
    instructionTable[0x1E] = &cpu::op_LD_En;
    instructionTable[0x1F] = &cpu::op_RRA;

    instructionTable[0x20] = &cpu::op_JR_NZn;
    instructionTable[0x21] = &cpu::op_LD_HLnn;
    instructionTable[0x22] = &cpu::op_LD_HLincA;
    instructionTable[0x23] = &cpu::op_INC_HL;
    instructionTable[0x24] = &cpu::op_INC_H;
    instructionTable[0x25] = &cpu::op_DEC_H;
    instructionTable[0x26] = &cpu::op_LD_Hn;
    instructionTable[0x27] = &cpu::op_DAA;
    instructionTable[0x28] = &cpu::op_JR_Zn;
    instructionTable[0x29] = &cpu::op_ADD_HLHL;
    instructionTable[0x2A] = &cpu::op_LD_AHLinc;
    instructionTable[0x2B] = &cpu::op_DEC_HL;
    instructionTable[0x2C] = &cpu::op_INC_L;
    instructionTable[0x2D] = &cpu::op_DEC_L;
    instructionTable[0x2E] = &cpu::op_LD_Ln;
    instructionTable[0x2F] = &cpu::op_CPL;

    instructionTable[0x30] = &cpu::op_JR_NCn;
    instructionTable[0x31] = &cpu::op_LD_SPnn;
    instructionTable[0x32] = &cpu::op_LD_HLdecA;
    instructionTable[0x33] = &cpu::op_INC_SP;
    instructionTable[0x34] = &cpu::op_INC_HLaddr;
    instructionTable[0x35] = &cpu::op_DEC_HLaddr;
    instructionTable[0x36] = &cpu::op_LD_HLaddrn;
    instructionTable[0x37] = &cpu::op_SCF;
    instructionTable[0x38] = &cpu::op_JR_Cn;
    instructionTable[0x39] = &cpu::op_ADD_HLSP;
    instructionTable[0x3A] = &cpu::op_LD_AHLdec;
    instructionTable[0x3B] = &cpu::op_DEC_SP;
    instructionTable[0x3C] = &cpu::op_INC_A;
    instructionTable[0x3D] = &cpu::op_DEC_A;
    instructionTable[0x3E] = &cpu::op_LD_An;
    instructionTable[0x3F] = &cpu::op_CCF;

    instructionTable[0x40] = &cpu::op_LD_BB;
    instructionTable[0x41] = &cpu::op_LD_BC;
    instructionTable[0x42] = &cpu::op_LD_BD;
    instructionTable[0x43] = &cpu::op_LD_BE;
    instructionTable[0x44] = &cpu::op_LD_BH;
    instructionTable[0x45] = &cpu::op_LD_BL;
    instructionTable[0x46] = &cpu::op_LD_BHL;
    instructionTable[0x47] = &cpu::op_LD_BA;
    instructionTable[0x48] = &cpu::op_LD_CB;
    instructionTable[0x49] = &cpu::op_LD_CC;
    instructionTable[0x4A] = &cpu::op_LD_CD;
    instructionTable[0x4B] = &cpu::op_LD_CE;
    instructionTable[0x4C] = &cpu::op_LD_CH;
    instructionTable[0x4D] = &cpu::op_LD_CL;
    instructionTable[0x4E] = &cpu::op_LD_CHL;
    instructionTable[0x4F] = &cpu::op_LD_CA;

    instructionTable[0x50] = &cpu::op_LD_DB;
    instructionTable[0x51] = &cpu::op_LD_DC;
    instructionTable[0x52] = &cpu::op_LD_DD;
    instructionTable[0x53] = &cpu::op_LD_DE;
    instructionTable[0x54] = &cpu::op_LD_DH;
    instructionTable[0x55] = &cpu::op_LD_DL;
    instructionTable[0x56] = &cpu::op_LD_DHL;
    instructionTable[0x57] = &cpu::op_LD_DA;
    instructionTable[0x58] = &cpu::op_LD_EB;
    instructionTable[0x59] = &cpu::op_LD_EC;
    instructionTable[0x5A] = &cpu::op_LD_ED;
    instructionTable[0x5B] = &cpu::op_LD_EE;
    instructionTable[0x5C] = &cpu::op_LD_EH;
    instructionTable[0x5D] = &cpu::op_LD_EL;
    instructionTable[0x5E] = &cpu::op_LD_EHL;
    instructionTable[0x5F] = &cpu::op_LD_EA;

    instructionTable[0x60] = &cpu::op_LD_HB;
    instructionTable[0x61] = &cpu::op_LD_HC;
    instructionTable[0x62] = &cpu::op_LD_HD;
    instructionTable[0x63] = &cpu::op_LD_HE;
    instructionTable[0x64] = &cpu::op_LD_HH;
    instructionTable[0x65] = &cpu::op_LD_HL;
    instructionTable[0x66] = &cpu::op_LD_HHL;
    instructionTable[0x67] = &cpu::op_LD_HA;
    instructionTable[0x68] = &cpu::op_LD_LB;
    instructionTable[0x69] = &cpu::op_LD_LC;
    instructionTable[0x6A] = &cpu::op_LD_LD;
    instructionTable[0x6B] = &cpu::op_LD_LE;
    instructionTable[0x6C] = &cpu::op_LD_LH;
    instructionTable[0x6D] = &cpu::op_LD_LL;
    instructionTable[0x6E] = &cpu::op_LD_LHL;
    instructionTable[0x6F] = &cpu::op_LD_LA;

    instructionTable[0x70] = &cpu::op_LD_HLB;
    instructionTable[0x71] = &cpu::op_LD_HLC;
    instructionTable[0x72] = &cpu::op_LD_HLD;
    instructionTable[0x73] = &cpu::op_LD_HLE;
    instructionTable[0x74] = &cpu::op_LD_HLH;
    instructionTable[0x75] = &cpu::op_LD_HLL;
    instructionTable[0x76] = &cpu::op_HALT;
    instructionTable[0x77] = &cpu::op_LD_HLA;
    instructionTable[0x78] = &cpu::op_LD_AB;
    instructionTable[0x79] = &cpu::op_LD_AC;
    instructionTable[0x7A] = &cpu::op_LD_AD;
    instructionTable[0x7B] = &cpu::op_LD_AE;
    instructionTable[0x7C] = &cpu::op_LD_AH;
    instructionTable[0x7D] = &cpu::op_LD_AL;
    instructionTable[0x7E] = &cpu::op_LD_AHL;
    instructionTable[0x7F] = &cpu::op_LD_AA;

    instructionTable[0x80] = &cpu::op_ADD_AB;
    instructionTable[0x81] = &cpu::op_ADD_AC;
    instructionTable[0x82] = &cpu::op_ADD_AD;
    instructionTable[0x83] = &cpu::op_ADD_AE;
    instructionTable[0x84] = &cpu::op_ADD_AH;
    instructionTable[0x85] = &cpu::op_ADD_AL;
    instructionTable[0x86] = &cpu::op_ADD_AHL;
    instructionTable[0x87] = &cpu::op_ADD_AA;
    instructionTable[0x88] = &cpu::op_ADC_AB;
    instructionTable[0x89] = &cpu::op_ADC_AC;
    instructionTable[0x8A] = &cpu::op_ADC_AD;
    instructionTable[0x8B] = &cpu::op_ADC_AE;
    instructionTable[0x8C] = &cpu::op_ADC_AH;
    instructionTable[0x8D] = &cpu::op_ADC_AL;
    instructionTable[0x8E] = &cpu::op_ADC_AHL;
    instructionTable[0x8F] = &cpu::op_ADC_AA;

    instructionTable[0x90] = &cpu::op_SUB_B;
    instructionTable[0x91] = &cpu::op_SUB_C;
    instructionTable[0x92] = &cpu::op_SUB_D;
    instructionTable[0x93] = &cpu::op_SUB_E;
    instructionTable[0x94] = &cpu::op_SUB_H;
    instructionTable[0x95] = &cpu::op_SUB_L;
    instructionTable[0x96] = &cpu::op_SUB_HL;
    instructionTable[0x97] = &cpu::op_SUB_A;
    instructionTable[0x98] = &cpu::op_SBC_AB;
    instructionTable[0x99] = &cpu::op_SBC_AC;
    instructionTable[0x9A] = &cpu::op_SBC_AD;
    instructionTable[0x9B] = &cpu::op_SBC_AE;
    instructionTable[0x9C] = &cpu::op_SBC_AH;
    instructionTable[0x9D] = &cpu::op_SBC_AL;
    instructionTable[0x9E] = &cpu::op_SBC_AHL;
    instructionTable[0x9F] = &cpu::op_SBC_AA;

    instructionTable[0xA0] = &cpu::op_AND_B;
    instructionTable[0xA1] = &cpu::op_AND_C;
    instructionTable[0xA2] = &cpu::op_AND_D;
    instructionTable[0xA3] = &cpu::op_AND_E;
    instructionTable[0xA4] = &cpu::op_AND_H;
    instructionTable[0xA5] = &cpu::op_AND_L;
    instructionTable[0xA6] = &cpu::op_AND_HL;
    instructionTable[0xA7] = &cpu::op_AND_A;
    instructionTable[0xA8] = &cpu::op_XOR_B;
    instructionTable[0xA9] = &cpu::op_XOR_C;
    instructionTable[0xAA] = &cpu::op_XOR_D;
    instructionTable[0xAB] = &cpu::op_XOR_E;
    instructionTable[0xAC] = &cpu::op_XOR_H;
    instructionTable[0xAD] = &cpu::op_XOR_L;
    instructionTable[0xAE] = &cpu::op_XOR_HL;
    instructionTable[0xAF] = &cpu::op_XOR_A;
    
    instructionTable[0xB0] = &cpu::op_OR_B;
    instructionTable[0xB1] = &cpu::op_OR_C;
    instructionTable[0xB2] = &cpu::op_OR_D;
    instructionTable[0xB3] = &cpu::op_OR_E;
    instructionTable[0xB4] = &cpu::op_OR_H;
    instructionTable[0xB5] = &cpu::op_OR_L;
    instructionTable[0xB6] = &cpu::op_OR_HL;
    instructionTable[0xB7] = &cpu::op_OR_A;
    instructionTable[0xB8] = &cpu::op_CP_B;
    instructionTable[0xB9] = &cpu::op_CP_C;
    instructionTable[0xBA] = &cpu::op_CP_D;
    instructionTable[0xBB] = &cpu::op_CP_E;
    instructionTable[0xBC] = &cpu::op_CP_H;
    instructionTable[0xBD] = &cpu::op_CP_L;
    instructionTable[0xBE] = &cpu::op_CP_HL;
    instructionTable[0xBF] = &cpu::op_CP_A;

    instructionTable[0xC0] = &cpu::op_RET_NZ;
    instructionTable[0xC1] = &cpu::op_POP_BC;
    instructionTable[0xC2] = &cpu::op_JP_NZnn;
    instructionTable[0xC3] = &cpu::op_JP_nn;
    instructionTable[0xC4] = &cpu::op_CALL_NZnn;
    instructionTable[0xC5] = &cpu::op_PUSH_BC;
    instructionTable[0xC6] = &cpu::op_ADD_An;
    instructionTable[0xC7] = &cpu::op_RST_00H;
    instructionTable[0xC8] = &cpu::op_RET_Z;
    instructionTable[0xC9] = &cpu::op_RET;
    instructionTable[0xCA] = &cpu::op_JP_Znn;
    instructionTable[0xCB] = &cpu::op_PREFIX_CB;
    instructionTable[0xCC] = &cpu::op_CALL_Znn;
    instructionTable[0xCD] = &cpu::op_CALL_nn;
    instructionTable[0xCE] = &cpu::op_ADC_An;
    instructionTable[0xCF] = &cpu::op_RST_08H;

    instructionTable[0xD0] = &cpu::op_RET_NC;
    instructionTable[0xD1] = &cpu::op_POP_DE;
    instructionTable[0xD2] = &cpu::op_JP_NCnn;
    instructionTable[0xD3] = &cpu::unusedInstruction;
    instructionTable[0xD4] = &cpu::op_CALL_NCnn;
    instructionTable[0xD5] = &cpu::op_PUSH_DE;
    instructionTable[0xD6] = &cpu::op_SUB_n;
    instructionTable[0xD7] = &cpu::op_RST_10H;
    instructionTable[0xD8] = &cpu::op_RET_C;
    instructionTable[0xD9] = &cpu::op_RETI;
    instructionTable[0xDA] = &cpu::op_JP_Cnn;
    instructionTable[0xDB] = &cpu::unusedInstruction;
    instructionTable[0xDC] = &cpu::op_CALL_Cnn;
    instructionTable[0xDD] = &cpu::unusedInstruction;
    instructionTable[0xDE] = &cpu::op_SBC_An;
    instructionTable[0xDF] = &cpu::op_RST_18H;

    instructionTable[0xE0] = &cpu::op_LDH_nA;
    instructionTable[0xE1] = &cpu::op_POP_HL;
    instructionTable[0xE2] = &cpu::op_LD_CaddrA;
    instructionTable[0xE3] = &cpu::unusedInstruction;
    instructionTable[0xE4] = &cpu::unusedInstruction;
    instructionTable[0xE5] = &cpu::op_PUSH_HL;
    instructionTable[0xE6] = &cpu::op_AND_n;
    instructionTable[0xE7] = &cpu::op_RST_20H;
    instructionTable[0xE8] = &cpu::op_ADD_SPn;
    instructionTable[0xE9] = &cpu::op_JP_HLaddr;
    instructionTable[0xEA] = &cpu::op_LD_nnA;
    instructionTable[0xEB] = &cpu::unusedInstruction;
    instructionTable[0xEC] = &cpu::unusedInstruction;
    instructionTable[0xED] = &cpu::unusedInstruction;
    instructionTable[0xEE] = &cpu::op_XOR_n;
    instructionTable[0xEF] = &cpu::op_RST_28H;

    instructionTable[0xF0] = &cpu::op_LDH_An;
    instructionTable[0xF1] = &cpu::op_POP_AF;
    instructionTable[0xF2] = &cpu::op_LD_ACaddr;
    instructionTable[0xF3] = &cpu::op_DI;
    instructionTable[0xF4] = &cpu::unusedInstruction;
    instructionTable[0xF5] = &cpu::op_PUSH_AF;
    instructionTable[0xF6] = &cpu::op_OR_n;
    instructionTable[0xF7] = &cpu::op_RST_30H;
    instructionTable[0xF8] = &cpu::op_LD_HLSPn;
    instructionTable[0xF9] = &cpu::op_LD_SPHL;
    instructionTable[0xFA] = &cpu::op_LD_Ann;
    instructionTable[0xFB] = &cpu::op_EI;
    instructionTable[0xFC] = &cpu::unusedInstruction;
    instructionTable[0xFD] = &cpu::unusedInstruction;
    instructionTable[0xFE] = &cpu::op_CP_n;
    instructionTable[0xFF] = &cpu::op_RST_38H;

}

void cpu::initializeCBInstructionTable(void)
{
    CBinstructionTable[0x00] = &cpu::op_RLC_B;
    CBinstructionTable[0x01] = &cpu::op_RLC_C;
    CBinstructionTable[0x02] = &cpu::op_RLC_D;
    CBinstructionTable[0x03] = &cpu::op_RLC_E;
    CBinstructionTable[0x04] = &cpu::op_RLC_H;
    CBinstructionTable[0x05] = &cpu::op_RLC_L;
    CBinstructionTable[0x06] = &cpu::op_RLC_HLaddr;
    CBinstructionTable[0x07] = &cpu::op_RLC_A;
    CBinstructionTable[0x08] = &cpu::op_RRC_B;
    CBinstructionTable[0x09] = &cpu::op_RRC_C;
    CBinstructionTable[0x0A] = &cpu::op_RRC_D;
    CBinstructionTable[0x0B] = &cpu::op_RRC_E;
    CBinstructionTable[0x0C] = &cpu::op_RRC_H;
    CBinstructionTable[0x0D] = &cpu::op_RRC_L;
    CBinstructionTable[0x0E] = &cpu::op_RRC_HLaddr;
    CBinstructionTable[0x0F] = &cpu::op_RRC_A;

    CBinstructionTable[0x10] = &cpu::op_RL_B;
    CBinstructionTable[0x11] = &cpu::op_RL_C;
    CBinstructionTable[0x12] = &cpu::op_RL_D;
    CBinstructionTable[0x13] = &cpu::op_RL_E;
    CBinstructionTable[0x14] = &cpu::op_RL_H;
    CBinstructionTable[0x15] = &cpu::op_RL_L;
    CBinstructionTable[0x16] = &cpu::op_RL_HLaddr;
    CBinstructionTable[0x17] = &cpu::op_RL_A;
    CBinstructionTable[0x18] = &cpu::op_RR_B;
    CBinstructionTable[0x19] = &cpu::op_RR_C;
    CBinstructionTable[0x1A] = &cpu::op_RR_D;
    CBinstructionTable[0x1B] = &cpu::op_RR_E;
    CBinstructionTable[0x1C] = &cpu::op_RR_H;
    CBinstructionTable[0x1D] = &cpu::op_RR_L;
    CBinstructionTable[0x1E] = &cpu::op_RR_HLaddr;
    CBinstructionTable[0x1F] = &cpu::op_RR_A;

    CBinstructionTable[0x20] = &cpu::op_SLA_B;
    CBinstructionTable[0x21] = &cpu::op_SLA_C;
    CBinstructionTable[0x22] = &cpu::op_SLA_D;
    CBinstructionTable[0x23] = &cpu::op_SLA_E;
    CBinstructionTable[0x24] = &cpu::op_SLA_H;
    CBinstructionTable[0x25] = &cpu::op_SLA_L;
    CBinstructionTable[0x26] = &cpu::op_SLA_HLaddr;
    CBinstructionTable[0x27] = &cpu::op_SLA_A;
    CBinstructionTable[0x28] = &cpu::op_SRA_B;
    CBinstructionTable[0x29] = &cpu::op_SRA_C;
    CBinstructionTable[0x2A] = &cpu::op_SRA_D;
    CBinstructionTable[0x2B] = &cpu::op_SRA_E;
    CBinstructionTable[0x2C] = &cpu::op_SRA_H;
    CBinstructionTable[0x2D] = &cpu::op_SRA_L;
    CBinstructionTable[0x2E] = &cpu::op_SRA_HLaddr;
    CBinstructionTable[0x2F] = &cpu::op_SRA_A;

    CBinstructionTable[0x30] = &cpu::op_SWAP_B;
    CBinstructionTable[0x31] = &cpu::op_SWAP_C;
    CBinstructionTable[0x32] = &cpu::op_SWAP_D;
    CBinstructionTable[0x33] = &cpu::op_SWAP_E;
    CBinstructionTable[0x34] = &cpu::op_SWAP_H;
    CBinstructionTable[0x35] = &cpu::op_SWAP_L;
    CBinstructionTable[0x36] = &cpu::op_SWAP_HLaddr;
    CBinstructionTable[0x37] = &cpu::op_SWAP_A;
    CBinstructionTable[0x38] = &cpu::op_SRL_B;
    CBinstructionTable[0x39] = &cpu::op_SRL_C;
    CBinstructionTable[0x3A] = &cpu::op_SRL_D;
    CBinstructionTable[0x3B] = &cpu::op_SRL_E;
    CBinstructionTable[0x3C] = &cpu::op_SRL_H;
    CBinstructionTable[0x3D] = &cpu::op_SRL_L;
    CBinstructionTable[0x3E] = &cpu::op_SRL_HLaddr;
    CBinstructionTable[0x3F] = &cpu::op_SRL_A;

    CBinstructionTable[0x40] = &cpu::op_BIT_0B;
    CBinstructionTable[0x41] = &cpu::op_BIT_0C;
    CBinstructionTable[0x42] = &cpu::op_BIT_0D;
    CBinstructionTable[0x43] = &cpu::op_BIT_0E;
    CBinstructionTable[0x44] = &cpu::op_BIT_0H;
    CBinstructionTable[0x45] = &cpu::op_BIT_0L;
    CBinstructionTable[0x46] = &cpu::op_BIT_0HLaddr;
    CBinstructionTable[0x47] = &cpu::op_BIT_0A;
    CBinstructionTable[0x48] = &cpu::op_BIT_1B;
    CBinstructionTable[0x49] = &cpu::op_BIT_1C;
    CBinstructionTable[0x4A] = &cpu::op_BIT_1D;
    CBinstructionTable[0x4B] = &cpu::op_BIT_1E;
    CBinstructionTable[0x4C] = &cpu::op_BIT_1H;
    CBinstructionTable[0x4D] = &cpu::op_BIT_1L;
    CBinstructionTable[0x4E] = &cpu::op_BIT_1HLaddr;
    CBinstructionTable[0x4F] = &cpu::op_BIT_1A;

    CBinstructionTable[0x50] = &cpu::op_BIT_2B;
    CBinstructionTable[0x51] = &cpu::op_BIT_2C;
    CBinstructionTable[0x52] = &cpu::op_BIT_2D;
    CBinstructionTable[0x53] = &cpu::op_BIT_2E;
    CBinstructionTable[0x54] = &cpu::op_BIT_2H;
    CBinstructionTable[0x55] = &cpu::op_BIT_2L;
    CBinstructionTable[0x56] = &cpu::op_BIT_2HLaddr;
    CBinstructionTable[0x57] = &cpu::op_BIT_2A;
    CBinstructionTable[0x58] = &cpu::op_BIT_3B;
    CBinstructionTable[0x59] = &cpu::op_BIT_3C;
    CBinstructionTable[0x5A] = &cpu::op_BIT_3D;
    CBinstructionTable[0x5B] = &cpu::op_BIT_3E;
    CBinstructionTable[0x5C] = &cpu::op_BIT_3H;
    CBinstructionTable[0x5D] = &cpu::op_BIT_3L;
    CBinstructionTable[0x5E] = &cpu::op_BIT_3HLaddr;
    CBinstructionTable[0x5F] = &cpu::op_BIT_3A;

    CBinstructionTable[0x60] = &cpu::op_BIT_4B;
    CBinstructionTable[0x61] = &cpu::op_BIT_4C;
    CBinstructionTable[0x62] = &cpu::op_BIT_4D;
    CBinstructionTable[0x63] = &cpu::op_BIT_4E;
    CBinstructionTable[0x64] = &cpu::op_BIT_4H;
    CBinstructionTable[0x65] = &cpu::op_BIT_4L;
    CBinstructionTable[0x66] = &cpu::op_BIT_4HLaddr;
    CBinstructionTable[0x67] = &cpu::op_BIT_4A;
    CBinstructionTable[0x68] = &cpu::op_BIT_5B;
    CBinstructionTable[0x69] = &cpu::op_BIT_5C;
    CBinstructionTable[0x6A] = &cpu::op_BIT_5D;
    CBinstructionTable[0x6B] = &cpu::op_BIT_5E;
    CBinstructionTable[0x6C] = &cpu::op_BIT_5H;
    CBinstructionTable[0x6D] = &cpu::op_BIT_5L;
    CBinstructionTable[0x6E] = &cpu::op_BIT_5HLaddr;
    CBinstructionTable[0x6F] = &cpu::op_BIT_5A;

    CBinstructionTable[0x70] = &cpu::op_BIT_6B;
    CBinstructionTable[0x71] = &cpu::op_BIT_6C;
    CBinstructionTable[0x72] = &cpu::op_BIT_6D;
    CBinstructionTable[0x73] = &cpu::op_BIT_6E;
    CBinstructionTable[0x74] = &cpu::op_BIT_6H;
    CBinstructionTable[0x75] = &cpu::op_BIT_6L;
    CBinstructionTable[0x76] = &cpu::op_BIT_6HLaddr;
    CBinstructionTable[0x77] = &cpu::op_BIT_6A;
    CBinstructionTable[0x78] = &cpu::op_BIT_7B;
    CBinstructionTable[0x79] = &cpu::op_BIT_7C;
    CBinstructionTable[0x7A] = &cpu::op_BIT_7D;
    CBinstructionTable[0x7B] = &cpu::op_BIT_7E;
    CBinstructionTable[0x7C] = &cpu::op_BIT_7H;
    CBinstructionTable[0x7D] = &cpu::op_BIT_7L;
    CBinstructionTable[0x7E] = &cpu::op_BIT_7HLaddr;
    CBinstructionTable[0x7F] = &cpu::op_BIT_7A;

    CBinstructionTable[0x80] = &cpu::op_RES_0B;
    CBinstructionTable[0x81] = &cpu::op_RES_0C;
    CBinstructionTable[0x82] = &cpu::op_RES_0D;
    CBinstructionTable[0x83] = &cpu::op_RES_0E;
    CBinstructionTable[0x84] = &cpu::op_RES_0H;
    CBinstructionTable[0x85] = &cpu::op_RES_0L;
    CBinstructionTable[0x86] = &cpu::op_RES_0HLaddr;
    CBinstructionTable[0x87] = &cpu::op_RES_0A;
    CBinstructionTable[0x88] = &cpu::op_RES_1B;
    CBinstructionTable[0x89] = &cpu::op_RES_1C;
    CBinstructionTable[0x8A] = &cpu::op_RES_1D;
    CBinstructionTable[0x8B] = &cpu::op_RES_1E;
    CBinstructionTable[0x8C] = &cpu::op_RES_1H;
    CBinstructionTable[0x8D] = &cpu::op_RES_1L;
    CBinstructionTable[0x8E] = &cpu::op_RES_1HLaddr;
    CBinstructionTable[0x8F] = &cpu::op_RES_1A;

    CBinstructionTable[0x90] = &cpu::op_RES_2B;
    CBinstructionTable[0x91] = &cpu::op_RES_2C;
    CBinstructionTable[0x92] = &cpu::op_RES_2D;
    CBinstructionTable[0x93] = &cpu::op_RES_2E;
    CBinstructionTable[0x94] = &cpu::op_RES_2H;
    CBinstructionTable[0x95] = &cpu::op_RES_2L;
    CBinstructionTable[0x96] = &cpu::op_RES_2HLaddr;
    CBinstructionTable[0x97] = &cpu::op_RES_2A;
    CBinstructionTable[0x98] = &cpu::op_RES_3B;
    CBinstructionTable[0x99] = &cpu::op_RES_3C;
    CBinstructionTable[0x9A] = &cpu::op_RES_3D;
    CBinstructionTable[0x9B] = &cpu::op_RES_3E;
    CBinstructionTable[0x9C] = &cpu::op_RES_3H;
    CBinstructionTable[0x9D] = &cpu::op_RES_3L;
    CBinstructionTable[0x9E] = &cpu::op_RES_3HLaddr;
    CBinstructionTable[0x9F] = &cpu::op_RES_3A;

    CBinstructionTable[0xA0] = &cpu::op_RES_4B;
    CBinstructionTable[0xA1] = &cpu::op_RES_4C;
    CBinstructionTable[0xA2] = &cpu::op_RES_4D;
    CBinstructionTable[0xA3] = &cpu::op_RES_4E;
    CBinstructionTable[0xA4] = &cpu::op_RES_4H;
    CBinstructionTable[0xA5] = &cpu::op_RES_4L;
    CBinstructionTable[0xA6] = &cpu::op_RES_4HLaddr;
    CBinstructionTable[0xA7] = &cpu::op_RES_4A;
    CBinstructionTable[0xA8] = &cpu::op_RES_5B;
    CBinstructionTable[0xA9] = &cpu::op_RES_5C;
    CBinstructionTable[0xAA] = &cpu::op_RES_5D;
    CBinstructionTable[0xAB] = &cpu::op_RES_5E;
    CBinstructionTable[0xAC] = &cpu::op_RES_5H;
    CBinstructionTable[0xAD] = &cpu::op_RES_5L;
    CBinstructionTable[0xAE] = &cpu::op_RES_5HLaddr;
    CBinstructionTable[0xAF] = &cpu::op_RES_5A;

    CBinstructionTable[0xB0] = &cpu::op_RES_6B;
    CBinstructionTable[0xB1] = &cpu::op_RES_6C;
    CBinstructionTable[0xB2] = &cpu::op_RES_6D;
    CBinstructionTable[0xB3] = &cpu::op_RES_6E;
    CBinstructionTable[0xB4] = &cpu::op_RES_6H;
    CBinstructionTable[0xB5] = &cpu::op_RES_6L;
    CBinstructionTable[0xB6] = &cpu::op_RES_6HLaddr;
    CBinstructionTable[0xB7] = &cpu::op_RES_6A;
    CBinstructionTable[0xB8] = &cpu::op_RES_7B;
    CBinstructionTable[0xB9] = &cpu::op_RES_7C;
    CBinstructionTable[0xBA] = &cpu::op_RES_7D;
    CBinstructionTable[0xBB] = &cpu::op_RES_7E;
    CBinstructionTable[0xBC] = &cpu::op_RES_7H;
    CBinstructionTable[0xBD] = &cpu::op_RES_7L;
    CBinstructionTable[0xBE] = &cpu::op_RES_7HLaddr;
    CBinstructionTable[0xBF] = &cpu::op_RES_7A;

    CBinstructionTable[0xC0] = &cpu::op_SET_0B;
    CBinstructionTable[0xC1] = &cpu::op_SET_0C;
    CBinstructionTable[0xC2] = &cpu::op_SET_0D;
    CBinstructionTable[0xC3] = &cpu::op_SET_0E;
    CBinstructionTable[0xC4] = &cpu::op_SET_0H;
    CBinstructionTable[0xC5] = &cpu::op_SET_0L;
    CBinstructionTable[0xC6] = &cpu::op_SET_0HLaddr;
    CBinstructionTable[0xC7] = &cpu::op_SET_0A;
    CBinstructionTable[0xC8] = &cpu::op_SET_1B;
    CBinstructionTable[0xC9] = &cpu::op_SET_1C;
    CBinstructionTable[0xCA] = &cpu::op_SET_1D;
    CBinstructionTable[0xCB] = &cpu::op_SET_1E;
    CBinstructionTable[0xCC] = &cpu::op_SET_1H;
    CBinstructionTable[0xCD] = &cpu::op_SET_1L;
    CBinstructionTable[0xCE] = &cpu::op_SET_1HLaddr;
    CBinstructionTable[0xCF] = &cpu::op_SET_1A;

    CBinstructionTable[0xD0] = &cpu::op_SET_2B;
    CBinstructionTable[0xD1] = &cpu::op_SET_2C;
    CBinstructionTable[0xD2] = &cpu::op_SET_2D;
    CBinstructionTable[0xD3] = &cpu::op_SET_2E;
    CBinstructionTable[0xD4] = &cpu::op_SET_2H;
    CBinstructionTable[0xD5] = &cpu::op_SET_2L;
    CBinstructionTable[0xD6] = &cpu::op_SET_2HLaddr;
    CBinstructionTable[0xD7] = &cpu::op_SET_2A;
    CBinstructionTable[0xD8] = &cpu::op_SET_3B;
    CBinstructionTable[0xD9] = &cpu::op_SET_3C;
    CBinstructionTable[0xDA] = &cpu::op_SET_3D;
    CBinstructionTable[0xDB] = &cpu::op_SET_3E;
    CBinstructionTable[0xDC] = &cpu::op_SET_3H;
    CBinstructionTable[0xDD] = &cpu::op_SET_3L;
    CBinstructionTable[0xDE] = &cpu::op_SET_3HLaddr;
    CBinstructionTable[0xDF] = &cpu::op_SET_3A;

    CBinstructionTable[0xE0] = &cpu::op_SET_4B;
    CBinstructionTable[0xE1] = &cpu::op_SET_4C;
    CBinstructionTable[0xE2] = &cpu::op_SET_4D;
    CBinstructionTable[0xE3] = &cpu::op_SET_4E;
    CBinstructionTable[0xE4] = &cpu::op_SET_4H;
    CBinstructionTable[0xE5] = &cpu::op_SET_4L;
    CBinstructionTable[0xE6] = &cpu::op_SET_4HLaddr;
    CBinstructionTable[0xE7] = &cpu::op_SET_4A;
    CBinstructionTable[0xE8] = &cpu::op_SET_5B;
    CBinstructionTable[0xE9] = &cpu::op_SET_5C;
    CBinstructionTable[0xEA] = &cpu::op_SET_5D;
    CBinstructionTable[0xEB] = &cpu::op_SET_5E;
    CBinstructionTable[0xEC] = &cpu::op_SET_5H;
    CBinstructionTable[0xED] = &cpu::op_SET_5L;
    CBinstructionTable[0xEE] = &cpu::op_SET_5HLaddr;
    CBinstructionTable[0xEF] = &cpu::op_SET_5A;

    CBinstructionTable[0xF0] = &cpu::op_SET_6B;
    CBinstructionTable[0xF1] = &cpu::op_SET_6C;
    CBinstructionTable[0xF2] = &cpu::op_SET_6D;
    CBinstructionTable[0xF3] = &cpu::op_SET_6E;
    CBinstructionTable[0xF4] = &cpu::op_SET_6H;
    CBinstructionTable[0xF5] = &cpu::op_SET_6L;
    CBinstructionTable[0xF6] = &cpu::op_SET_6HLaddr;
    CBinstructionTable[0xF7] = &cpu::op_SET_6A;
    CBinstructionTable[0xF8] = &cpu::op_SET_7B;
    CBinstructionTable[0xF9] = &cpu::op_SET_7C;
    CBinstructionTable[0xFA] = &cpu::op_SET_7D;
    CBinstructionTable[0xFB] = &cpu::op_SET_7E;
    CBinstructionTable[0xFC] = &cpu::op_SET_7H;
    CBinstructionTable[0xFD] = &cpu::op_SET_7L;
    CBinstructionTable[0xFE] = &cpu::op_SET_7HLaddr;
    CBinstructionTable[0xFF] = &cpu::op_SET_7A;
}

void cpu::powerUpSequence(void)
{
    // The GB runs a 256 byte boot ROM on startup
    // which runs some checks and initializes
    // the CPU and HW Registers. Distribution
    // of this boot ROM is illegal, so this function
    // simply sets the emulator in the same state
    // the boot ROM would if it were to be executed

    // TODO: Possibly read the values from a file

    registers["AF"]->setTotalValue(0x01B0);
    registers["BC"]->setTotalValue(0x0013);
    registers["DE"]->setTotalValue(0x00D8);
    registers["HL"]->setTotalValue(0x014D);
    registers["SP"]->setTotalValue(0x0FFE);
    registers["PC"]->setTotalValue(0x0100);

    mainMemory.writeToAddress(0xFF05, 0X00);
    mainMemory.writeToAddress(0xFF06, 0X00);
    mainMemory.writeToAddress(0xFF07, 0X00);
    mainMemory.writeToAddress(0xFF10, 0X80);
    mainMemory.writeToAddress(0xFF11, 0XBF);
    mainMemory.writeToAddress(0xFF12, 0XF3);
    mainMemory.writeToAddress(0xFF14, 0XBF);
    mainMemory.writeToAddress(0xFF16, 0X3F);
    mainMemory.writeToAddress(0xFF17, 0X00);
    mainMemory.writeToAddress(0xFF19, 0XBF);
    mainMemory.writeToAddress(0xFF1A, 0X7F);
    mainMemory.writeToAddress(0xFF1B, 0XFF);
    mainMemory.writeToAddress(0xFF1C, 0X9F);
    mainMemory.writeToAddress(0xFF1E, 0XBF);
    mainMemory.writeToAddress(0xFF20, 0XFF);
    mainMemory.writeToAddress(0xFF21, 0X00);
    mainMemory.writeToAddress(0xFF22, 0X00);
    mainMemory.writeToAddress(0xFF23, 0XBF);
    mainMemory.writeToAddress(0xFF24, 0X77);
    mainMemory.writeToAddress(0xFF25, 0XF3);
    mainMemory.writeToAddress(0xFF26, 0XF1);
    mainMemory.writeToAddress(0xFF40, 0X91);
    mainMemory.writeToAddress(0xFF42, 0X00);
    mainMemory.writeToAddress(0xFF43, 0X00);
    mainMemory.writeToAddress(0xFF45, 0X00);
    mainMemory.writeToAddress(0xFF47, 0XFC);
    mainMemory.writeToAddress(0xFF48, 0XFF);
    mainMemory.writeToAddress(0xFF49, 0XFF);
    mainMemory.writeToAddress(0xFF4A, 0X00);
    mainMemory.writeToAddress(0xFF4B, 0X00);
    mainMemory.writeToAddress(0xFFFF, 0X00);
}

void cpu::loadROM(std::string filePath)
{
    // TODO: Checks
    currentROM = new cartridge(filePath);
    mainMemory.loadROM(currentROM);

}

void cpu::unloadROM()
{
    delete currentROM;
    currentROM = 0;
}

void cpu::runFrame(void)
{
    int opCycles = 0;


    // Screen Refreshes every 70244 clock cycles. CPU keeps running ops
    // until it reaches that number. Afterwards, it stops and waits
    // for screen refresh before resuming
    while( frameCycles < 70244)
    {
        opCycles = executeInstruction();

        frameCycles += opCycles;
    }
    frameCycles-= 70244;
}


void cpu::load16BitRegister(std::string registerName, uint16_t value)
{
    registers[registerName]->setTotalValue(value);
}

uint8_t cpu::getOpCode(void)
{
    uint8_t byte = getNextByte();
    return byte;
}

uint8_t cpu::getNextByte(void)
{
    // Retrieve the Byte that the Program Counter Points 
    // to then increment the Program Counter

    uint16_t addr = registers["PC"]->getTotalValue();
    uint8_t val = mainMemory.readAddress(addr);
    
    registers["PC"]->incrementRegister();

    return val;
}

int cpu::unusedInstruction(void)
{
    // To be used to log unused opCode
    // executions
}

int cpu::executeInstruction()
{
    uint8_t opcode = getOpCode();
    if( opcode == 0xCB )
    {
        opcode = getOpCode();
        return (this->*CBinstructionTable[opcode])();
    }

    return (this->*instructionTable[opcode])();
}

uint8_t cpu::getFlag(char flag)
{
    //  Flag Register Bits:
    //  7 6 5 4 3 2 1 0
    //  Z N H C 0 0 0 0

    uint8_t reg = registers["AF"]->getLowValue();
    reg = reg>>4;

    switch(flag) 
    {
        case 'Z': reg = reg>>1;
        case 'N': reg = reg>>1;
        case 'H': reg = reg>>1;
        case 'C': break;
        default: break;
    }

    return reg & 0x01;
}

void cpu::setFlag(char flag)
{
    //  Flag Register Bits:
    //  7 6 5 4 3 2 1 0
    //  Z N H C 0 0 0 0

    uint8_t reg = registers["AF"]->getLowValue();
    uint8_t val = 0x10;

    switch (flag)
    {
        case 'Z': val = val<<1;
        case 'N': val = val<<1;
        case 'H': val = val<<1;
        case 'C': break;
        default: break;
    }

    reg = val | reg;

    registers["AF"]->setLowValue(reg);

}

void cpu::resetFlag(char flag)
{
    //  Flag Register Bits:
    //  7 6 5 4 3 2 1 0
    //  Z N H C 0 0 0 0

    uint8_t reg = registers["AF"]->getLowValue();
    uint8_t val = 0x10;

    switch (flag)
    {
        case 'Z': val = val<<1;
        case 'N': val = val<<1;
        case 'H': val = val<<1;
        case 'C': break;
        default: break;
    }

    val = val^0xFF;
    reg = val & reg;

    registers["AF"]->setLowValue(reg);
}

uint8_t cpu::getByteAtAddress(uint16_t addr)
{
    return mainMemory.readAddress(addr);
}

void cpu::setByteAtAddress(uint16_t addr, uint8_t val)
{
    mainMemory.writeToAddress(addr,val);
}

uint8_t cpu::getHighRegisterValue(std::string regName)
{
    return registers[regName]->getHighValue();
}

uint8_t cpu::getLowRegisterValue(std::string regName)
{
    return registers[regName]->getLowValue();
}

uint16_t cpu::getRegisterValue(std::string regName)
{
    return registers[regName]->getTotalValue();
}

void cpu::setHighRegisterValue(std::string regName, uint8_t val)
{
    registers[regName]->setHighValue(val);
}

void cpu::setLowRegisterValue(std::string regName, uint8_t val)
{
    registers[regName]->setLowValue(val);
}

void cpu::setRegisterValue(std::string regName, uint16_t val)
{
    registers[regName]->setTotalValue(val);
}

uint8_t cpu::add16Bit(uint16_t srcVal, std::string destReg)
{
    // Adds value of srcReg to destReg
    // Return values:
    //          0 if no Carry and no Half-Carry
    //          1 if no Carry and Half-Carry
    //          2 if Carry and no Half-Carry
    //          3 if Carry and Half-Carry

    uint16_t destVal, totalVal;
    uint8_t halfCarry = 0, carry = 0;
 
    destVal = registers[destReg]->getTotalValue();

    totalVal = srcVal + destVal;

    // Check for Half-Carry
    if( ( ( ( srcVal & 0x0FFF ) + ( destVal & 0x0FFF ) ) & 0x1000 ) == 0x1000 )
        halfCarry = 1;

    // Check for Carry
    if( srcVal > totalVal || destVal > totalVal)
        carry = 2;
    

    registers[destReg]->setTotalValue(totalVal);

    return halfCarry + carry;
}

uint8_t cpu::add8Bit(uint8_t srcVal, std::string destReg, uint8_t hiLo)
{
    // Adds srcVal to destReg, either to the high or low order byte,
    // depending on whether hiLo is 1 (high) or 0 (low)
    // Note: Should probably be only invoked as add8Bit(srcVal,"AF",1);
    // Since all ADD instructions add to the A register
    // Return values:
    //          0 if no Carry and no Half-Carry
    //          1 if no Carry and Half-Carry
    //          2 if Carry and no Half-Carry
    //          3 if Carry and Half-Carry

    uint8_t destVal, totalVal;
    uint8_t halfCarry = 0, carry = 0;

    if( hiLo == 0 ) destVal = registers[destReg]->getLowValue();
    else            destVal = registers[destReg]->getHighValue();

    totalVal = srcVal + destVal;

    // Check for Half-Carry
    if( ( ( ( srcVal & 0x0F ) + ( destVal & 0x0F ) ) & 0x10 ) == 0x10 )
        halfCarry = 1;

    // Check for Carry
    if( srcVal > totalVal || destVal > totalVal)
        carry = 2;

    if( hiLo == 0 ) registers[destReg]->setLowValue(totalVal);
    else            registers[destReg]->setHighValue(totalVal);

    return halfCarry + carry; 
}

uint8_t cpu::add8BitWithCarry(uint8_t srcVal, std::string destReg, uint8_t hiLo)
{
    // Adds srcVal plus the value of the carry flag
    // to destReg, either to the high or low order byte,
    // depending on whether hiLo is 1 (high) or 0 (low)
    // Note: Should probably be only invoked as add8BitWithCarry(srcVal,"AF",1);
    // Since all ADC instructions add to the A register
    // Return values:
    //          0 if no Carry and no Half-Carry
    //          1 if no Carry and Half-Carry
    //          2 if Carry and no Half-Carry
    //          3 if Carry and Half-Carry

    uint8_t destVal, totalVal;
    uint8_t halfCarry = 0, carry = 0, flags = 0;

    if( getFlag('C') != 0 )
    {
        srcVal++;

        if( srcVal == 0)            carry = 2;
        if( srcVal % 16 == 0)       halfCarry = 1;          // When incrementing a number, the only case
                                                            // bit 3 can overflow is when a number of the form
                                                            // XXXX1111 is incremented to XXXX0000, therefore
                                                            // the result mod 16 equals 0
    }

    flags = add8Bit(srcVal, destReg, hiLo);

    return ( flags | (carry + halfCarry) );
}

uint8_t cpu::subtract8Bit(uint8_t srcVal, std::string destReg, uint8_t hiLo)
{
    // Subtracts srcVal from destReg, either from the high or low order byte,
    // depending on whether hiLo is 1 (high) or 0 (low)
    // Note: Should probably be only invoked as subtract8Bit(srcVal,"AF",1);
    // Since all SUB instructions subtract from the A register
    // Return values:
    //          0 if no Carry and no Half-Carry
    //          1 if no Carry and Half-Carry
    //          2 if Carry and no Half-Carry
    //          3 if Carry and Half-Carry

    uint8_t destVal, totalVal;
    uint8_t halfCarry = 0, carry = 0;

    if( hiLo == 0 ) destVal = registers[destReg]->getLowValue();
    else            destVal = registers[destReg]->getHighValue();

    totalVal = destVal - srcVal;

    // Check for Half-Carry
    if( ( srcVal & 0x0F ) > ( destVal & 0x0F ) )
        halfCarry = 1;

    // Check for Carry
    if( totalVal > destVal )
        carry = 2;

    if( hiLo == 0 ) registers[destReg]->setLowValue(totalVal);
    else            registers[destReg]->setHighValue(totalVal);

    return halfCarry + carry; 
}

uint8_t cpu::subtract8BitWithCarry(uint8_t srcVal, std::string destReg, uint8_t hiLo)
{
    // Subtracts srcVal plus the value of the carry flag from destReg, 
    // either from the high or low order byte,
    // depending on whether hiLo is 1 (high) or 0 (low)
    // Note: Should probably be only invoked as subtract8Bit(srcVal,"AF",1);
    // Since all SUB instructions subtract from the A register
    // Return values:
    //          0 if no Carry and no Half-Carry
    //          1 if no Carry and Half-Carry
    //          2 if Carry and no Half-Carry
    //          3 if Carry and Half-Carry

    uint8_t destVal, totalVal;
    uint8_t halfCarry = 0, carry = 0, flags = 0;

    if( getFlag('C') != 0 )
    {
        srcVal--;

        if( srcVal == 0)            carry = 2;
        if( srcVal % 16 == 15)  halfCarry = 1;         // When decrementing a number, the only case
                                                            // bit 4 is borrowed from is when a number of the form
                                                            // XXX10000 is decremented to XXX01111, therefore
                                                            // the result mod 16 equals 15
    }

    flags = subtract8Bit(srcVal, destReg, hiLo);

    return ( flags | (carry + halfCarry) );  
}

uint8_t cpu::compare8Bit(uint8_t srcVal, std::string destReg, uint8_t hiLo)
{
    // Compares srcVal with the contents of destReg, either with the high or
    // low order byte, depengind on whether hiLo is 1 (high) or 0 (low)
    // Works exactly like subtract8Bit, however the result is discarded
    // and only the flag changes apply, also return the zero flag value
    // as there is no way to deduce it after the function has returned
    // Note: Should probably be only invoked as compare8Bit(srcVal,"AF",1);
    // Since all CP instructions compare with the A register
    // Return values:
    //          0 if no Carry, no Half-Carry and not Zero
    //          1 if no Carry, Half-Carry and not Zero
    //          2 if Carry, no Half-Carry and not Zero
    //          3 if Carry, Half-Carry and not Zero
    //          4 if no Carry, no Half-Carry and Zero
    //          5 if no Carry, Half-Carry and Zero
    //          6 if Carry, no Half-Carry and Zero
    //          7 if Carry, Half-Carry and Zero

    uint8_t destVal, totalVal;
    uint8_t halfCarry = 0, carry = 0, zero = 0;

    if( hiLo == 0 ) destVal = registers[destReg]->getLowValue();
    else            destVal = registers[destReg]->getHighValue();

    totalVal = destVal - srcVal;

    // Check for Half-Carry
    if( ( srcVal & 0x0F ) > ( destVal & 0x0F ) )
        halfCarry = 1;

    // Check for Carry
    if( totalVal > destVal )
        carry = 2;

    // Check for Zero
    if( totalVal == 0 )
        zero = 4;

    return zero + halfCarry + carry; 
}

void cpu::popToRegister(std::string destReg)
{
    // Pops contents of stack into register destReg
    // Copies byte SP points to into the low register
    // then the next byte into the high register
    // also increments SP by 2

    uint8_t low, high;
    uint16_t addr = registers["SP"]->getTotalValue();

    low = mainMemory.readAddress(addr);
    addr++;

    high = mainMemory.readAddress(addr);
    addr++;

    registers[destReg]->setLowValue(low);
    registers[destReg]->setHighValue(high);

    registers["SP"]->setTotalValue(addr);
}

void cpu::pushByteToStack(uint8_t val)
{
    // Decrements SP by 1 then
    // loads val into the memory address
    // it points to

    uint16_t addr;
    
    addr = registers["SP"]->getTotalValue();
    addr--;

    mainMemory.writeToAddress(addr, val);

    registers["SP"]->setTotalValue(addr);
}