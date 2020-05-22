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
    public:
        cpu();
        ~cpu();

        void runFrame();
        int executeInstruction();
        void load16BitRegister(std::string, uint16_t);

        uint8_t getNextByte();


        // Flag Access Methods

        uint8_t getFlag(char);
        void setFlag(char);
        void resetFlag(char);

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

        int op_STOP();                                              // 0x10  STOP 0
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
        int op_DAA();                                               // 0x27  DAA
        int op_JR_Zn();                                             // 0x28  JR Z, n
        int op_ADD_HLHL();                                          // 0x29  ADD HL, HL
        int op_LD_AHLinc();                                         // 0x2A  LD A, HL+
        int op_DEC_HL();                                            // 0x2B  DEC HL
        int op_INC_L();                                             // 0x2C  INC L
        int op_DEC_L();                                             // 0x2D  DEC L
        int op_LD_Ln();                                             // 0x2E  LD L, n
        int op_CPL();                                               // 0x2F  CPL

        // Instructions (CB Prefix)
};

#endif