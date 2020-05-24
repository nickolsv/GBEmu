#ifndef __GB_CPU_HH__
#define __GB_CPU_HH__

#include <map>
#include "../header/registers.hh"
#include "../header/memory.hh"

// High Registers: A, B, D, H, Hi Bits of SP, Hi Bits of PC
// Low Registers : F, C, E, L, Lo Bits of SP, Lo Bits of PC
class cpu
{
    private:
        const std::string regnames[6] = { "AF", "BC", "DE", "HL", "SP", "PC"};
        std::map<std::string,register16 *> registers;
        memory mainMemory;
        int frameCycles;

        std::map<uint8_t, int (cpu::*)()> instructionTable;
        void initializeInstructionTable();

        uint8_t getNextByte();

        uint8_t add16Bit(uint16_t srcVal, std::string destReg);
        uint8_t add8Bit(uint8_t srcVal, std::string destReg, uint8_t hiLo);
        uint8_t add8BitWithCarry(uint8_t srcVal, std::string destReg, uint8_t hiLo);

        void load16BitRegister(std::string, uint16_t);

        // Flag Access Methods

        uint8_t getFlag(char);
        void setFlag(char);
        void resetFlag(char);

    public:
        cpu();
        ~cpu();

        void runFrame();
        int executeInstruction();

        // Instruction Set

        int op_NOOP();                                              // 0x00  NOOP
        int op_LD_BCnn();                                           // 0x01  LD BC, nn
        int op_LD_BCA();                                            // 0x02  LD (BC), A
        int op_INC_BC();                                            // 0x03  INC BC
        int op_INC_B();                                             // 0x04  INC B
        int op_DEC_B();                                             // 0x05  DEC B
        int op_LD_Bn();                                             // 0x06  LD B, n
        int op_RLC_A();                                             // 0x07  RLCA
        int op_LD_aaSP();                                           // 0x08  LD aa, SP
        int op_ADD_HLBC();                                          // 0x09  ADD HL, BC
        int op_LD_ABC();                                            // 0x0A  LD A, BC
        int op_DEC_BC();                                            // 0x0B  DEC BC
        int op_INC_C();                                             // 0x0C  INC C
        int op_DEC_C();                                             // 0x0D  DEC C
        int op_LD_Cn();                                             // 0x0E  LD C, n
        int op_RRC_A();                                             // 0x0F  RRCA

        int op_STOP();                                              // 0x10  STOP 0             // TODO: Implement
        int op_LD_DEnn();                                           // 0x11  LD DE, nn
        int op_LD_DEA();                                            // 0x12  LD (DE), A
        int op_INC_DE();                                            // 0x13  INC DE
        int op_INC_D();                                             // 0x14  INC D
        int op_DEC_D();                                             // 0x15  DEC D
        int op_LD_Dn();                                             // 0x16  LD D, n
        int op_RLA();                                               // 0x17  RLA
        int op_JR_n();                                              // 0x18  JR n               // TODO: Implement
        int op_ADD_HLDE();                                          // 0x19  ADD HL, DE
        int op_LD_ADE();                                            // 0x1A  LD A, DE
        int op_DEC_DE();                                            // 0x1B  DEC DE
        int op_INC_E();                                             // 0x1C  INC E
        int op_DEC_E();                                             // 0x1D  DEC E
        int op_LD_En();                                             // 0x1E  LD E, n
        int op_RRA();                                               // 0x1F  RRA

        int op_JR_NZn();                                            // 0x20  JR NZ, n           // TODO: Implement
        int op_LD_HLnn();                                           // 0x21  LD HL, nn
        int op_LD_HLincA();                                         // 0x22  LD HL+, A
        int op_INC_HL();                                            // 0x23  INC HL
        int op_INC_H();                                             // 0x24  INC H
        int op_DEC_H();                                             // 0x25  DEC H
        int op_LD_Hn();                                             // 0x26  LD H, n
        int op_DAA();                                               // 0x27  DAA                // TODO: Implement
        int op_JR_Zn();                                             // 0x28  JR Z, n            // TODO: Implement
        int op_ADD_HLHL();                                          // 0x29  ADD HL, HL
        int op_LD_AHLinc();                                         // 0x2A  LD A, (HL-)
        int op_DEC_HL();                                            // 0x2B  DEC HL
        int op_INC_L();                                             // 0x2C  INC L
        int op_DEC_L();                                             // 0x2D  DEC L
        int op_LD_Ln();                                             // 0x2E  LD L, n
        int op_CPL();                                               // 0x2F  CPL

        int op_JR_NCn();                                            // 0x30  JR NC, n           // TODO: Implement
        int op_LD_SPnn();                                           // 0x31  LD SP, nn
        int op_LD_HLdecA();                                         // 0x32  LD HL-, A
        int op_INC_SP();                                            // 0x33  INC SP
        int op_INC_HLaddr();                                        // 0x34  INC (HL)
        int op_DEC_HLaddr();                                        // 0x35  DEC (HL)
        int op_LD_HLaddrn();                                        // 0x36  LD (HL), n
        int op_SCF();                                               // 0x37  SCF
        int op_JR_Cn();                                             // 0x38  JR C, n            // TODO: Implement
        int op_ADD_HLSP();                                          // 0x39  ADD HL, SP
        int op_LD_AHLdec();                                         // 0x3A  LD A, (HL-)
        int op_DEC_SP();                                            // 0x3B  DEC SP
        int op_INC_A();                                             // 0x3C  INC A
        int op_DEC_A();                                             // 0x3D  DEC A
        int op_LD_An();                                             // 0x3E  LD A, n
        int op_CCF();                                               // 0x3F  CCF

        int op_LD_BB();                                             // 0x40  LD B, B
        int op_LD_BC();                                             // 0x41  LD B, C
        int op_LD_BD();                                             // 0x42  LD B, D
        int op_LD_BE();                                             // 0x43  LD B, E
        int op_LD_BH();                                             // 0x44  LD B, H
        int op_LD_BL();                                             // 0x45  LD B, L
        int op_LD_BHL();                                            // 0x46  LD B, (HL)
        int op_LD_BA();                                             // 0x47  LD B, A
        int op_LD_CB();                                             // 0x48  LD C, B
        int op_LD_CC();                                             // 0x49  LD C, C
        int op_LD_CD();                                             // 0x4A  LD C, D
        int op_LD_CE();                                             // 0x4B  LD C, E
        int op_LD_CH();                                             // 0x4C  LD C, H
        int op_LD_CL();                                             // 0x4D  LD C, L
        int op_LD_CHL();                                            // 0x4E  LD C, (HL)
        int op_LD_CA();                                             // 0x4F  LD C, A

        int op_LD_DB();                                             // 0x50  LD D, B
        int op_LD_DC();                                             // 0x51  LD D, C
        int op_LD_DD();                                             // 0x52  LD D, D
        int op_LD_DE();                                             // 0x53  LD D, E
        int op_LD_DH();                                             // 0x54  LD D, H
        int op_LD_DL();                                             // 0x55  LD D, L
        int op_LD_DHL();                                            // 0x56  LD D, (HL)
        int op_LD_DA();                                             // 0x57  LD D, A
        int op_LD_EB();                                             // 0x58  LD E, B
        int op_LD_EC();                                             // 0x59  LD E, C
        int op_LD_ED();                                             // 0x5A  LD E, D
        int op_LD_EE();                                             // 0x5B  LD E, E
        int op_LD_EH();                                             // 0x5C  LD E, H
        int op_LD_EL();                                             // 0x5D  LD E, L
        int op_LD_EHL();                                            // 0x5E  LD E, (HL)
        int op_LD_EA();                                             // 0x5F  LD E, A

        int op_LD_HB();                                             // 0x60  LD H, B
        int op_LD_HC();                                             // 0x61  LD H, C
        int op_LD_HD();                                             // 0x62  LD H, D
        int op_LD_HE();                                             // 0x63  LD H, E
        int op_LD_HH();                                             // 0x64  LD H, H
        int op_LD_HL();                                             // 0x65  LD H, L
        int op_LD_HHL();                                            // 0x66  LD H, (HL)
        int op_LD_HA();                                             // 0x67  LD H, A
        int op_LD_LB();                                             // 0x68  LD L, B
        int op_LD_LC();                                             // 0x69  LD L, C
        int op_LD_LD();                                             // 0x6A  LD L, D
        int op_LD_LE();                                             // 0x6B  LD L, E
        int op_LD_LH();                                             // 0x6C  LD L, H
        int op_LD_LL();                                             // 0x6D  LD L, L
        int op_LD_LHL();                                            // 0x6E  LD L, (HL)
        int op_LD_LA();                                             // 0x6F  LD L, A

        int op_LD_HLB();                                            // 0x70  LD (HL), B
        int op_LD_HLC();                                            // 0x71  LD (HL), C
        int op_LD_HLD();                                            // 0x72  LD (HL), D
        int op_LD_HLE();                                            // 0x73  LD (HL), E
        int op_LD_HLH();                                            // 0x74  LD (HL), H
        int op_LD_HLL();                                            // 0x75  LD (HL), L
        int op_HALT();                                              // 0x76  HALT               // TODO: Implement
        int op_LD_HLA();                                            // 0x77  LD (HL), A
        int op_LD_AB();                                             // 0x78  LD A, B
        int op_LD_AC();                                             // 0x79  LD A, C
        int op_LD_AD();                                             // 0x7A  LD A, D
        int op_LD_AE();                                             // 0x7B  LD A, E
        int op_LD_AH();                                             // 0x7C  LD A, H
        int op_LD_AL();                                             // 0x7D  LD A, L
        int op_LD_AHL();                                            // 0x7E  LD A, (HL)
        int op_LD_AA();                                             // 0x7F  LD A, A

        int op_ADD_AB();                                            // 0x80  ADD A, B
        int op_ADD_AC();                                            // 0x81  ADD A, C
        int op_ADD_AD();                                            // 0x82  ADD A, D
        int op_ADD_AE();                                            // 0x83  ADD A, E
        int op_ADD_AH();                                            // 0x84  ADD A, H
        int op_ADD_AL();                                            // 0x85  ADD A, L
        int op_ADD_AHL();                                           // 0x86  ADD A, (HL)
        int op_ADD_AA();                                            // 0x87  ADD A, A
        int op_ADC_AB();                                            // 0x88  ADC A, B
        int op_ADC_AC();                                            // 0x89  ADC A, C
        int op_ADC_AD();                                            // 0x8A  ADC A, D
        int op_ADC_AE();                                            // 0x8B  ADC A, E
        int op_ADC_AH();                                            // 0x8C  ADC A, H
        int op_ADC_AL();                                            // 0x8D  ADC A, L
        int op_ADC_AHL();                                           // 0x8E  ADC A, (HL)
        int op_ADC_AA();                                            // 0x8F  ADC A, A

        int op_SUB_B();                                             // 0x90  SUB B              // TODO: Implement
        int op_SUB_C();                                             // 0x91  SUB C              // TODO: Implement
        int op_SUB_D();                                             // 0x92  SUB D              // TODO: Implement
        int op_SUB_E();                                             // 0x93  SUB E              // TODO: Implement
        int op_SUB_H();                                             // 0x94  SUB H              // TODO: Implement
        int op_SUB_L();                                             // 0x95  SUB L              // TODO: Implement
        int op_SUB_HL();                                            // 0x96  SUB (HL)           // TODO: Implement
        int op_SUB_A();                                             // 0x97  SUB A              // TODO: Implement
        int op_SBC_B();                                             // 0x98  SBC B              // TODO: Implement
        int op_SBC_C();                                             // 0x99  SBC C              // TODO: Implement
        int op_SBC_D();                                             // 0x9A  SBC D              // TODO: Implement
        int op_SBC_E();                                             // 0x9B  SBC E              // TODO: Implement
        int op_SBC_H();                                             // 0x9C  SBC H              // TODO: Implement
        int op_SBC_L();                                             // 0x9D  SBC L              // TODO: Implement
        int op_SBC_HL();                                            // 0x9E  SBC (HL)           // TODO: Implement
        int op_SBC_A();                                             // 0x9F  SBC A              // TODO: Implement

        int op_AND_B();                                             // 0xA0  AND B
        int op_AND_C();                                             // 0xA1  AND C
        int op_AND_D();                                             // 0xA2  AND D
        int op_AND_E();                                             // 0xA3  AND E
        int op_AND_H();                                             // 0xA4  AND H
        int op_AND_L();                                             // 0xA5  AND L
        int op_AND_HL();                                            // 0xA6  AND (HL)
        int op_AND_A();                                             // 0xA7  AND A
        int op_XOR_B();                                             // 0xA8  XOR B
        int op_XOR_C();                                             // 0xA9  XOR C
        int op_XOR_D();                                             // 0xAA  XOR D
        int op_XOR_E();                                             // 0xAB  XOR E
        int op_XOR_H();                                             // 0xAC  XOR H
        int op_XOR_L();                                             // 0xAD  XOR L
        int op_XOR_HL();                                            // 0xAE  XOR (HL)
        int op_XOR_A();                                             // 0xAF  XOR A
        
        int op_OR_B();                                              // 0xB0  OR B
        int op_OR_C();                                              // 0xB1  OR C
        int op_OR_D();                                              // 0xB2  OR D
        int op_OR_E();                                              // 0xB3  OR E
        int op_OR_H();                                              // 0xB4  OR H
        int op_OR_L();                                              // 0xB5  OR L
        int op_OR_HL();                                             // 0xB6  OR (HL)
        int op_OR_A();                                              // 0xB7  OR A
        int op_CP_B();                                              // 0xB8  CP B               // TODO: Implement
        int op_CP_C();                                              // 0xB9  CP C               // TODO: Implement
        int op_CP_D();                                              // 0xBA  CP D               // TODO: Implement
        int op_CP_E();                                              // 0xBB  CP E               // TODO: Implement
        int op_CP_H();                                              // 0xBC  CP H               // TODO: Implement
        int op_CP_L();                                              // 0xBD  CP L               // TODO: Implement
        int op_CP_HL();                                             // 0xBE  CP (HL)            // TODO: Implement
        int op_CP_A();                                              // 0xBF  CP A               // TODO: Implement
        
        // Instructions (CB Prefix)
};

#endif