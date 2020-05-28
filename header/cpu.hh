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

        uint8_t getOpCode();
        uint8_t getNextByte();

        uint8_t add16Bit(uint16_t srcVal, std::string destReg);
        uint8_t add8Bit(uint8_t srcVal, std::string destReg, uint8_t hiLo);
        uint8_t add8BitWithCarry(uint8_t srcVal, std::string destReg, uint8_t hiLo);

        uint8_t subtract8Bit(uint8_t srcVal, std::string destReg, uint8_t hiLo);
        uint8_t subtract8BitWithCarry(uint8_t srcVal, std::string destReg, uint8_t hiLo);
        uint8_t compare8Bit(uint8_t srcVal, std::string destReg, uint8_t hiLo);
        
        void pushByteToStack(uint8_t byte);
        void popToRegister(std::string destReg);
        void load16BitRegister(std::string, uint16_t);

    public:
        cpu();
        ~cpu();

        void runFrame();
        int executeInstruction();

        uint8_t getFlag(char);
        void setFlag(char);
        void resetFlag(char);
        uint8_t getByteAtAddress(uint16_t);
        void setByteAtAddress(uint16_t, uint8_t);
        uint8_t  getHighRegisterValue(std::string);
        uint8_t  getLowRegisterValue(std::string);
        uint16_t getRegisterValue(std::string);
        void setHighRegisterValue(std::string, uint8_t);
        void setLowRegisterValue(std::string, uint8_t);
        void setRegisterValue(std::string, uint16_t);

        // Instruction Set

        int op_NOOP();                                              // 0x00  NOOP
        int op_LD_BCnn();                                           // 0x01  LD BC, nn
        int op_LD_BCA();                                            // 0x02  LD (BC), A
        int op_INC_BC();                                            // 0x03  INC BC
        int op_INC_B();                                             // 0x04  INC B
        int op_DEC_B();                                             // 0x05  DEC B
        int op_LD_Bn();                                             // 0x06  LD B, n
        int op_RLCA();                                              // 0x07  RLCA
        int op_LD_aaSP();                                           // 0x08  LD aa, SP
        int op_ADD_HLBC();                                          // 0x09  ADD HL, BC
        int op_LD_ABC();                                            // 0x0A  LD A, BC
        int op_DEC_BC();                                            // 0x0B  DEC BC
        int op_INC_C();                                             // 0x0C  INC C
        int op_DEC_C();                                             // 0x0D  DEC C
        int op_LD_Cn();                                             // 0x0E  LD C, n
        int op_RRCA();                                              // 0x0F  RRCA

        int op_STOP();                                              // 0x10  STOP 0             // TODO: Implement
        int op_LD_DEnn();                                           // 0x11  LD DE, nn
        int op_LD_DEA();                                            // 0x12  LD (DE), A
        int op_INC_DE();                                            // 0x13  INC DE
        int op_INC_D();                                             // 0x14  INC D
        int op_DEC_D();                                             // 0x15  DEC D
        int op_LD_Dn();                                             // 0x16  LD D, n
        int op_RLA();                                               // 0x17  RLA
        int op_JR_n();                                              // 0x18  JR n
        int op_ADD_HLDE();                                          // 0x19  ADD HL, DE
        int op_LD_ADE();                                            // 0x1A  LD A, DE
        int op_DEC_DE();                                            // 0x1B  DEC DE
        int op_INC_E();                                             // 0x1C  INC E
        int op_DEC_E();                                             // 0x1D  DEC E
        int op_LD_En();                                             // 0x1E  LD E, n
        int op_RRA();                                               // 0x1F  RRA

        int op_JR_NZn();                                            // 0x20  JR NZ, n
        int op_LD_HLnn();                                           // 0x21  LD HL, nn
        int op_LD_HLincA();                                         // 0x22  LD HL+, A
        int op_INC_HL();                                            // 0x23  INC HL
        int op_INC_H();                                             // 0x24  INC H
        int op_DEC_H();                                             // 0x25  DEC H
        int op_LD_Hn();                                             // 0x26  LD H, n
        int op_DAA();                                               // 0x27  DAA                // TODO: Implement
        int op_JR_Zn();                                             // 0x28  JR Z, n
        int op_ADD_HLHL();                                          // 0x29  ADD HL, HL
        int op_LD_AHLinc();                                         // 0x2A  LD A, (HL-)
        int op_DEC_HL();                                            // 0x2B  DEC HL
        int op_INC_L();                                             // 0x2C  INC L
        int op_DEC_L();                                             // 0x2D  DEC L
        int op_LD_Ln();                                             // 0x2E  LD L, n
        int op_CPL();                                               // 0x2F  CPL

        int op_JR_NCn();                                            // 0x30  JR NC, n
        int op_LD_SPnn();                                           // 0x31  LD SP, nn
        int op_LD_HLdecA();                                         // 0x32  LD HL-, A
        int op_INC_SP();                                            // 0x33  INC SP
        int op_INC_HLaddr();                                        // 0x34  INC (HL)
        int op_DEC_HLaddr();                                        // 0x35  DEC (HL)
        int op_LD_HLaddrn();                                        // 0x36  LD (HL), n
        int op_SCF();                                               // 0x37  SCF
        int op_JR_Cn();                                             // 0x38  JR C, n
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

        int op_SUB_B();                                             // 0x90  SUB B
        int op_SUB_C();                                             // 0x91  SUB C
        int op_SUB_D();                                             // 0x92  SUB D
        int op_SUB_E();                                             // 0x93  SUB E
        int op_SUB_H();                                             // 0x94  SUB H
        int op_SUB_L();                                             // 0x95  SUB L
        int op_SUB_HL();                                            // 0x96  SUB (HL)
        int op_SUB_A();                                             // 0x97  SUB A
        int op_SBC_AB();                                            // 0x98  SBC A, B
        int op_SBC_AC();                                            // 0x99  SBC A, C
        int op_SBC_AD();                                            // 0x9A  SBC A, D
        int op_SBC_AE();                                            // 0x9B  SBC A, E
        int op_SBC_AH();                                            // 0x9C  SBC A, H
        int op_SBC_AL();                                            // 0x9D  SBC A, L
        int op_SBC_AHL();                                           // 0x9E  SBC A, (HL)
        int op_SBC_AA();                                            // 0x9F  SBC A, A

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
        int op_CP_B();                                              // 0xB8  CP B
        int op_CP_C();                                              // 0xB9  CP C
        int op_CP_D();                                              // 0xBA  CP D
        int op_CP_E();                                              // 0xBB  CP E
        int op_CP_H();                                              // 0xBC  CP H
        int op_CP_L();                                              // 0xBD  CP L
        int op_CP_HL();                                             // 0xBE  CP (HL)
        int op_CP_A();                                              // 0xBF  CP A

        int op_RET_NZ();                                            // 0xC0  RET NZ
        int op_POP_BC();                                            // 0xC1  POP BC
        int op_JP_NZnn();                                           // 0xC2  JP NZ, nn
        int op_JP_nn();                                             // 0xC3  JP nn
        int op_CALL_NZnn();                                         // 0xC4  CALL NZ, nn
        int op_PUSH_BC();                                           // 0xC5  PUSH BC
        int op_ADD_An();                                            // 0xC6  ADD A, n
        int op_RST_00H();                                           // 0xC7  RST 00H
        int op_RET_Z();                                             // 0xC8  RET Z
        int op_RET();                                               // 0xC9  RET
        int op_JP_Znn();                                            // 0xCA  JP Z, nn
        int op_PREFIX_CB();                                         // 0xCB  PREFIX CB          // TODO: Implement
        int op_CALL_Znn();                                          // 0xCC  CALL Z, nn
        int op_CALL_nn();                                           // 0xCD  CALL nn
        int op_ADC_An();                                            // 0xCE  ADC A, n
        int op_RST_08H();                                           // 0xCF  RST 08H

        int op_RET_NC();                                            // 0xD0  RET NC
        int op_POP_DE();                                            // 0xD1  POP DE
        int op_JP_NCnn();                                           // 0xD2  JP NC, nn
        // Unused Instruction 0xD3
        int op_CALL_NCnn();                                         // 0xD4  CALL NC, nn
        int op_PUSH_DE();                                           // 0xD5  PUSH DE
        int op_SUB_n();                                             // 0xD6  SUB n
        int op_RST_10H();                                           // 0xD7  RST 10H
        int op_RET_C();                                             // 0xD8  RET C
        int op_RETI();                                              // 0xD9  RETI               // TODO: Implement
        int op_JP_Cnn();                                            // 0xDA  JP C, nn
        // Unused Instruction 0xDB
        int op_CALL_Cnn();                                          // 0xDC  CALL C, nn
        // Unused Instruction 0xDD
        int op_SBC_An();                                            // 0xDE  SBC A, n
        int op_RST_18H();                                           // 0xDF  RST 18H

        int op_LDH_nA();                                            // 0xE0  LDH n, A
        int op_POP_HL();                                            // 0xE1  POP HL
        int op_LD_CaddrA();                                         // 0xE2  LD (C), A
        // Unused Instruction 0xE3
        // Unused Instruction 0xE4
        int op_PUSH_HL();                                           // 0xE5  PUSH HL
        int op_AND_n();                                             // 0xE6  AND n
        int op_RST_20H();                                           // 0xE7  RST 20H
        int op_ADD_SPn();                                           // 0xE8  ADD SP, n          // TODO: Set/Reset H,C Flags
        int op_JP_HLaddr();                                         // 0xE9  JP (HL)
        int op_LD_nnA();                                            // 0xEA  LD (nn), A
        // Unused Instruction 0xEB
        // Unused Instruction 0xEC
        // Unused Instruction 0xED
        int op_XOR_n();                                             // 0xEE  XOR n
        int op_RST_28H();                                           // 0xEF  RST 28H

        int op_LDH_An();                                            // 0xF0  LDH A, n
        int op_POP_AF();                                            // 0xF1  POP AF
        int op_LD_ACaddr();                                         // 0xF2  LD A, (C)
        int op_DI();                                                // 0xF3  DI                 // TODO: Implement
        // Unused Instruction 0xF4
        int op_PUSH_AF();                                           // 0xF5  PUSH AF
        int op_OR_n();                                              // 0xF6  OR n
        int op_RST_30H();                                           // 0xF7  RST 30H
        int op_LD_HLSPn();                                          // 0xF8  LD HL, SP+n        // TODO: Set/Reset H,C Flags
        int op_LD_SPHL();                                           // 0xF9  LD SP, HL
        int op_LD_Ann();                                            // 0xFA  LD A, (nn)
        int op_EI();                                                // 0xFB  EI                 // TODO: Implement
        // Unused Instruction 0xFC
        // Unused Instruction 0xFD
        int op_CP_n();                                              // 0xFE  CP n
        int op_RST_38H();                                           // 0xFF  RST 38H


        // Instructions (CB Prefix)

        int op_RLC_B();                                             // 0xCB 0x00  RLC B
        int op_RLC_C();                                             // 0xCB 0x01  RLC C
        int op_RLC_D();                                             // 0xCB 0x02  RLC D
        int op_RLC_E();                                             // 0xCB 0x03  RLC E
        int op_RLC_H();                                             // 0xCB 0x04  RLC H
        int op_RLC_L();                                             // 0xCB 0x05  RLC L
        int op_RLC_HLaddr();                                        // 0xCB 0x06  RLC (HL)
        int op_RLC_A();                                             // 0xCB 0x07  RLC A
        int op_RRC_B();                                             // 0xCB 0x08  RRC B
        int op_RRC_C();                                             // 0xCB 0x09  RRC C
        int op_RRC_D();                                             // 0xCB 0x0A  RRC D
        int op_RRC_E();                                             // 0xCB 0x0B  RRC E
        int op_RRC_H();                                             // 0xCB 0x0C  RRC H
        int op_RRC_L();                                             // 0xCB 0x0D  RRC L
        int op_RRC_HLaddr();                                        // 0xCB 0x0E  RRC (HL)
        int op_RRC_A();                                             // 0xCB 0x0F  RRC A

        int op_RL_B();                                              // 0xCB 0x10  RL B
        int op_RL_C();                                              // 0xCB 0x11  RL C
        int op_RL_D();                                              // 0xCB 0x12  RL D
        int op_RL_E();                                              // 0xCB 0x13  RL E
        int op_RL_H();                                              // 0xCB 0x14  RL H
        int op_RL_L();                                              // 0xCB 0x15  RL L
        int op_RL_HLaddr();                                         // 0xCB 0x16  RL (HL)
        int op_RL_A();                                              // 0xCB 0x17  RL A
        int op_RR_B();                                              // 0xCB 0x18  RR B
        int op_RR_C();                                              // 0xCB 0x19  RR C
        int op_RR_D();                                              // 0xCB 0x1A  RR D
        int op_RR_E();                                              // 0xCB 0x1B  RR E
        int op_RR_H();                                              // 0xCB 0x1C  RR H
        int op_RR_L();                                              // 0xCB 0x1D  RR L
        int op_RR_HLaddr();                                         // 0xCB 0x1E  RR (HL)
        int op_RR_A();                                              // 0xCB 0x1F  RR A

        int op_SLA_B();                                             // 0xCB 0x20  SLA B
        int op_SLA_C();                                             // 0xCB 0x21  SLA C
        int op_SLA_D();                                             // 0xCB 0x22  SLA D
        int op_SLA_E();                                             // 0xCB 0x23  SLA E
        int op_SLA_H();                                             // 0xCB 0x24  SLA H
        int op_SLA_L();                                             // 0xCB 0x25  SLA L
        int op_SLA_HLaddr();                                        // 0xCB 0x26  SLA (HL)
        int op_SLA_A();                                             // 0xCB 0x27  SLA A
        int op_SRA_B();                                             // 0xCB 0x28  SRA B
        int op_SRA_C();                                             // 0xCB 0x29  SRA C
        int op_SRA_D();                                             // 0xCB 0x2A  SRA D
        int op_SRA_E();                                             // 0xCB 0x2B  SRA E
        int op_SRA_H();                                             // 0xCB 0x2C  SRA H
        int op_SRA_L();                                             // 0xCB 0x2D  SRA L
        int op_SRA_HLaddr();                                        // 0xCB 0x2E  SRA (HL)
        int op_SRA_A();                                             // 0xCB 0x2F  SRA A

        int op_SWAP_B();                                            // 0xCB 0x30  SWAP B
        int op_SWAP_C();                                            // 0xCB 0x31  SWAP C
        int op_SWAP_D();                                            // 0xCB 0x32  SWAP D
        int op_SWAP_E();                                            // 0xCB 0x33  SWAP E
        int op_SWAP_H();                                            // 0xCB 0x34  SWAP H
        int op_SWAP_L();                                            // 0xCB 0x35  SWAP L
        int op_SWAP_HLaddr();                                       // 0xCB 0x36  SWAP (HL)
        int op_SWAP_A();                                            // 0xCB 0x37  SWAP A
        int op_SRL_B();                                             // 0xCB 0x38  SRL B
        int op_SRL_C();                                             // 0xCB 0x39  SRL C
        int op_SRL_D();                                             // 0xCB 0x3A  SRL D
        int op_SRL_E();                                             // 0xCB 0x3B  SRL E
        int op_SRL_H();                                             // 0xCB 0x3C  SRL H
        int op_SRL_L();                                             // 0xCB 0x3D  SRL L
        int op_SRL_HLaddr();                                        // 0xCB 0x3E  SRL (HL)
        int op_SRL_A();                                             // 0xCB 0x3F  SRL A

        int op_BIT_0B();                                            // 0xCB 0x48  BIT 0, B
        int op_BIT_0C();                                            // 0xCB 0x49  BIT 0, C
        int op_BIT_0D();                                            // 0xCB 0x4A  BIT 0, D
        int op_BIT_0E();                                            // 0xCB 0x4B  BIT 0, E
        int op_BIT_0H();                                            // 0xCB 0x4C  BIT 0, H
        int op_BIT_0L();                                            // 0xCB 0x4D  BIT 0, L
        int op_BIT_0HLaddr();                                       // 0xCB 0x4E  BIT 0, (HL)
        int op_BIT_0A();                                            // 0xCB 0x4F  BIT 0, A
        int op_BIT_1B();                                            // 0xCB 0x48  BIT 1, B
        int op_BIT_1C();                                            // 0xCB 0x49  BIT 1, C
        int op_BIT_1D();                                            // 0xCB 0x4A  BIT 1, D
        int op_BIT_1E();                                            // 0xCB 0x4B  BIT 1, E
        int op_BIT_1H();                                            // 0xCB 0x4C  BIT 1, H
        int op_BIT_1L();                                            // 0xCB 0x4D  BIT 1, L
        int op_BIT_1HLaddr();                                       // 0xCB 0x4E  BIT 1, (HL)
        int op_BIT_1A();                                            // 0xCB 0x4F  BIT 1, A

        int op_BIT_2B();                                            // 0xCB 0x58  BIT 2, B
        int op_BIT_2C();                                            // 0xCB 0x59  BIT 2, C
        int op_BIT_2D();                                            // 0xCB 0x5A  BIT 2, D
        int op_BIT_2E();                                            // 0xCB 0x5B  BIT 2, E
        int op_BIT_2H();                                            // 0xCB 0x5C  BIT 2, H
        int op_BIT_2L();                                            // 0xCB 0x5D  BIT 2, L
        int op_BIT_2HLaddr();                                       // 0xCB 0x5E  BIT 2, (HL)
        int op_BIT_2A();                                            // 0xCB 0x5F  BIT 2, A
        int op_BIT_3B();                                            // 0xCB 0x58  BIT 3, B
        int op_BIT_3C();                                            // 0xCB 0x59  BIT 3, C
        int op_BIT_3D();                                            // 0xCB 0x5A  BIT 3, D
        int op_BIT_3E();                                            // 0xCB 0x5B  BIT 3, E
        int op_BIT_3H();                                            // 0xCB 0x5C  BIT 3, H
        int op_BIT_3L();                                            // 0xCB 0x5D  BIT 3, L
        int op_BIT_3HLaddr();                                       // 0xCB 0x5E  BIT 3, (HL)
        int op_BIT_3A();                                            // 0xCB 0x5F  BIT 3, A

        int op_BIT_4B();                                            // 0xCB 0x68  BIT 4, B
        int op_BIT_4C();                                            // 0xCB 0x69  BIT 4, C
        int op_BIT_4D();                                            // 0xCB 0x6A  BIT 4, D
        int op_BIT_4E();                                            // 0xCB 0x6B  BIT 4, E
        int op_BIT_4H();                                            // 0xCB 0x6C  BIT 4, H
        int op_BIT_4L();                                            // 0xCB 0x6D  BIT 4, L
        int op_BIT_4HLaddr();                                       // 0xCB 0x6E  BIT 4, (HL)
        int op_BIT_4A();                                            // 0xCB 0x6F  BIT 4, A
        int op_BIT_5B();                                            // 0xCB 0x68  BIT 5, B
        int op_BIT_5C();                                            // 0xCB 0x69  BIT 5, C
        int op_BIT_5D();                                            // 0xCB 0x6A  BIT 5, D
        int op_BIT_5E();                                            // 0xCB 0x6B  BIT 5, E
        int op_BIT_5H();                                            // 0xCB 0x6C  BIT 5, H
        int op_BIT_5L();                                            // 0xCB 0x6D  BIT 5, L
        int op_BIT_5HLaddr();                                       // 0xCB 0x6E  BIT 5, (HL)
        int op_BIT_5A();                                            // 0xCB 0x6F  BIT 5, A

        int op_BIT_6B();                                            // 0xCB 0x78  BIT 6, B
        int op_BIT_6C();                                            // 0xCB 0x79  BIT 6, C
        int op_BIT_6D();                                            // 0xCB 0x7A  BIT 6, D
        int op_BIT_6E();                                            // 0xCB 0x7B  BIT 6, E
        int op_BIT_6H();                                            // 0xCB 0x7C  BIT 6, H
        int op_BIT_6L();                                            // 0xCB 0x7D  BIT 6, L
        int op_BIT_6HLaddr();                                       // 0xCB 0x7E  BIT 6, (HL)
        int op_BIT_6A();                                            // 0xCB 0x7F  BIT 6, A
        int op_BIT_7B();                                            // 0xCB 0x78  BIT 7, B
        int op_BIT_7C();                                            // 0xCB 0x79  BIT 7, C
        int op_BIT_7D();                                            // 0xCB 0x7A  BIT 7, D
        int op_BIT_7E();                                            // 0xCB 0x7B  BIT 7, E
        int op_BIT_7H();                                            // 0xCB 0x7C  BIT 7, H
        int op_BIT_7L();                                            // 0xCB 0x7D  BIT 7, L
        int op_BIT_7HLaddr();                                       // 0xCB 0x7E  BIT 7, (HL)
        int op_BIT_7A();                                            // 0xCB 0x7F  BIT 7, A

        int op_RES_0B();                                            // 0xCB 0x88  RES 0, B
        int op_RES_0C();                                            // 0xCB 0x89  RES 0, C
        int op_RES_0D();                                            // 0xCB 0x8A  RES 0, D
        int op_RES_0E();                                            // 0xCB 0x8B  RES 0, E
        int op_RES_0H();                                            // 0xCB 0x8C  RES 0, H
        int op_RES_0L();                                            // 0xCB 0x8D  RES 0, L
        int op_RES_0HLaddr();                                       // 0xCB 0x8E  RES 0, (HL)
        int op_RES_0A();                                            // 0xCB 0x8F  RES 0, A
        int op_RES_1B();                                            // 0xCB 0x88  RES 1, B
        int op_RES_1C();                                            // 0xCB 0x89  RES 1, C
        int op_RES_1D();                                            // 0xCB 0x8A  RES 1, D
        int op_RES_1E();                                            // 0xCB 0x8B  RES 1, E
        int op_RES_1H();                                            // 0xCB 0x8C  RES 1, H
        int op_RES_1L();                                            // 0xCB 0x8D  RES 1, L
        int op_RES_1HLaddr();                                       // 0xCB 0x8E  RES 1, (HL)
        int op_RES_1A();                                            // 0xCB 0x8F  RES 1, A

        int op_RES_2B();                                            // 0xCB 0x98  RES 2, B
        int op_RES_2C();                                            // 0xCB 0x99  RES 2, C
        int op_RES_2D();                                            // 0xCB 0x9A  RES 2, D
        int op_RES_2E();                                            // 0xCB 0x9B  RES 2, E
        int op_RES_2H();                                            // 0xCB 0x9C  RES 2, H
        int op_RES_2L();                                            // 0xCB 0x9D  RES 2, L
        int op_RES_2HLaddr();                                       // 0xCB 0x9E  RES 2, (HL)
        int op_RES_2A();                                            // 0xCB 0x9F  RES 2, A
        int op_RES_3B();                                            // 0xCB 0x98  RES 3, B
        int op_RES_3C();                                            // 0xCB 0x99  RES 3, C
        int op_RES_3D();                                            // 0xCB 0x9A  RES 3, D
        int op_RES_3E();                                            // 0xCB 0x9B  RES 3, E
        int op_RES_3H();                                            // 0xCB 0x9C  RES 3, H
        int op_RES_3L();                                            // 0xCB 0x9D  RES 3, L
        int op_RES_3HLaddr();                                       // 0xCB 0x9E  RES 3, (HL)
        int op_RES_3A();                                            // 0xCB 0x9F  RES 3, A

        int op_RES_4B();                                            // 0xCB 0xA8  RES 4, B
        int op_RES_4C();                                            // 0xCB 0xA9  RES 4, C
        int op_RES_4D();                                            // 0xCB 0xAA  RES 4, D
        int op_RES_4E();                                            // 0xCB 0xAB  RES 4, E
        int op_RES_4H();                                            // 0xCB 0xAC  RES 4, H
        int op_RES_4L();                                            // 0xCB 0xAD  RES 4, L
        int op_RES_4HLaddr();                                       // 0xCB 0xAE  RES 4, (HL)
        int op_RES_4A();                                            // 0xCB 0xAF  RES 4, A
        int op_RES_5B();                                            // 0xCB 0xA8  RES 5, B
        int op_RES_5C();                                            // 0xCB 0xA9  RES 5, C
        int op_RES_5D();                                            // 0xCB 0xAA  RES 5, D
        int op_RES_5E();                                            // 0xCB 0xAB  RES 5, E
        int op_RES_5H();                                            // 0xCB 0xAC  RES 5, H
        int op_RES_5L();                                            // 0xCB 0xAD  RES 5, L
        int op_RES_5HLaddr();                                       // 0xCB 0xAE  RES 5, (HL)
        int op_RES_5A();                                            // 0xCB 0xAF  RES 5, A

        int op_RES_6B();                                            // 0xCB 0xB8  RES 6, B
        int op_RES_6C();                                            // 0xCB 0xB9  RES 6, C
        int op_RES_6D();                                            // 0xCB 0xBA  RES 6, D
        int op_RES_6E();                                            // 0xCB 0xBB  RES 6, E
        int op_RES_6H();                                            // 0xCB 0xBC  RES 6, H
        int op_RES_6L();                                            // 0xCB 0xBD  RES 6, L
        int op_RES_6HLaddr();                                       // 0xCB 0xBE  RES 6, (HL)
        int op_RES_6A();                                            // 0xCB 0xBF  RES 6, A
        int op_RES_7B();                                            // 0xCB 0xB8  RES 7, B
        int op_RES_7C();                                            // 0xCB 0xB9  RES 7, C
        int op_RES_7D();                                            // 0xCB 0xBA  RES 7, D
        int op_RES_7E();                                            // 0xCB 0xBB  RES 7, E
        int op_RES_7H();                                            // 0xCB 0xBC  RES 7, H
        int op_RES_7L();                                            // 0xCB 0xBD  RES 7, L
        int op_RES_7HLaddr();                                       // 0xCB 0xBE  RES 7, (HL)
        int op_RES_7A();                                            // 0xCB 0xBF  RES 7, A

        int op_SET_0B();                                            // 0xCB 0xC8  SET 0, B
        int op_SET_0C();                                            // 0xCB 0xC9  SET 0, C
        int op_SET_0D();                                            // 0xCB 0xCA  SET 0, D
        int op_SET_0E();                                            // 0xCB 0xCB  SET 0, E
        int op_SET_0H();                                            // 0xCB 0xCC  SET 0, H
        int op_SET_0L();                                            // 0xCB 0xCD  SET 0, L
        int op_SET_0HLaddr();                                       // 0xCB 0xCE  SET 0, (HL)
        int op_SET_0A();                                            // 0xCB 0xCF  SET 0, A
        int op_SET_1B();                                            // 0xCB 0xC8  SET 1, B
        int op_SET_1C();                                            // 0xCB 0xC9  SET 1, C
        int op_SET_1D();                                            // 0xCB 0xCA  SET 1, D
        int op_SET_1E();                                            // 0xCB 0xCB  SET 1, E
        int op_SET_1H();                                            // 0xCB 0xCC  SET 1, H
        int op_SET_1L();                                            // 0xCB 0xCD  SET 1, L
        int op_SET_1HLaddr();                                       // 0xCB 0xCE  SET 1, (HL)
        int op_SET_1A();                                            // 0xCB 0xCF  SET 1, A

        int op_SET_2B();                                            // 0xCB 0xD8  SET 2, B
        int op_SET_2C();                                            // 0xCB 0xD9  SET 2, C
        int op_SET_2D();                                            // 0xCB 0xDA  SET 2, D
        int op_SET_2E();                                            // 0xCB 0xDB  SET 2, E
        int op_SET_2H();                                            // 0xCB 0xDC  SET 2, H
        int op_SET_2L();                                            // 0xCB 0xDD  SET 2, L
        int op_SET_2HLaddr();                                       // 0xCB 0xDE  SET 2, (HL)
        int op_SET_2A();                                            // 0xCB 0xDF  SET 2, A
        int op_SET_3B();                                            // 0xCB 0xD8  SET 3, B
        int op_SET_3C();                                            // 0xCB 0xD9  SET 3, C
        int op_SET_3D();                                            // 0xCB 0xDA  SET 3, D
        int op_SET_3E();                                            // 0xCB 0xDB  SET 3, E
        int op_SET_3H();                                            // 0xCB 0xDC  SET 3, H
        int op_SET_3L();                                            // 0xCB 0xDD  SET 3, L
        int op_SET_3HLaddr();                                       // 0xCB 0xDE  SET 3, (HL)
        int op_SET_3A();                                            // 0xCB 0xDF  SET 3, A

        int op_SET_4B();                                            // 0xCB 0xE8  SET 4, B
        int op_SET_4C();                                            // 0xCB 0xE9  SET 4, C
        int op_SET_4D();                                            // 0xCB 0xEA  SET 4, D
        int op_SET_4E();                                            // 0xCB 0xEB  SET 4, E
        int op_SET_4H();                                            // 0xCB 0xEC  SET 4, H
        int op_SET_4L();                                            // 0xCB 0xED  SET 4, L
        int op_SET_4HLaddr();                                       // 0xCB 0xEE  SET 4, (HL)
        int op_SET_4A();                                            // 0xCB 0xEF  SET 4, A
        int op_SET_5B();                                            // 0xCB 0xE8  SET 5, B
        int op_SET_5C();                                            // 0xCB 0xE9  SET 5, C
        int op_SET_5D();                                            // 0xCB 0xEA  SET 5, D
        int op_SET_5E();                                            // 0xCB 0xEB  SET 5, E
        int op_SET_5H();                                            // 0xCB 0xEC  SET 5, H
        int op_SET_5L();                                            // 0xCB 0xED  SET 5, L
        int op_SET_5HLaddr();                                       // 0xCB 0xEE  SET 5, (HL)
        int op_SET_5A();                                            // 0xCB 0xEF  SET 5, A

        int op_SET_6B();                                            // 0xCB 0xF8  SET 6, B
        int op_SET_6C();                                            // 0xCB 0xF9  SET 6, C
        int op_SET_6D();                                            // 0xCB 0xFA  SET 6, D
        int op_SET_6E();                                            // 0xCB 0xFB  SET 6, E
        int op_SET_6H();                                            // 0xCB 0xFC  SET 6, H
        int op_SET_6L();                                            // 0xCB 0xFD  SET 6, L
        int op_SET_6HLaddr();                                       // 0xCB 0xFE  SET 6, (HL)
        int op_SET_6A();                                            // 0xCB 0xFF  SET 6, A
        int op_SET_7B();                                            // 0xCB 0xF8  SET 7, B
        int op_SET_7C();                                            // 0xCB 0xF9  SET 7, C
        int op_SET_7D();                                            // 0xCB 0xFA  SET 7, D
        int op_SET_7E();                                            // 0xCB 0xFB  SET 7, E
        int op_SET_7H();                                            // 0xCB 0xFC  SET 7, H
        int op_SET_7L();                                            // 0xCB 0xFD  SET 7, L
        int op_SET_7HLaddr();                                       // 0xCB 0xFE  SET 7, (HL)
        int op_SET_7A();                                            // 0xCB 0xFF  SET 7, A

};

#endif