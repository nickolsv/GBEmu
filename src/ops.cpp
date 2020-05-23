#include "../header/cpu.hh"

int cpu::op_NOOP(void)
{
    // opCode 0x00
    // NOOP
    // Does Nothing
    // 4 Cycles, 1 byte

    return 4;
}

int cpu::op_LD_BCnn(void)
{
    // opCode 0x01
    // LD BC, nn
    // Loads next 2 bytes of memory
    // into BC register
    // 12 Cycles, 3 bytes

    uint8_t val;

    val = getNextByte();
    registers["BC"]->setLowValue(val);

    val = getNextByte();
    registers["BC"]->setHighValue(val);

    return 12;
}

int cpu::op_LD_BCA(void)
{
    // opCode 0x02
    // LD (BC), A
    // Loads value in register A into memory
    // location pointed to by register BC
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;

    addr = registers["BC"]->getTotalValue();
    val = registers["AF"]->getHighValue();

    mainMemory.writeToAddress(addr,val);

    return 8;
}

int cpu::op_INC_BC(void)
{
    // opCode 0x03
    // INC BC
    // Increments value in register BC by 1
    // 8 Cycles, 1 byte

    registers["BC"]->incrementRegister();

    return 8;
}

int cpu::op_INC_B(void)
{
    // opCode 0x04
    // INC B
    // Increments value in register B by 1
    // Flags: 
    //      - Sets Z if result is 0
    //      - N to 0
    //      - Sets H if bit 3 overflows
    // 4 Cycles, 1 byte

    registers["BC"]->incrementHighRegister();

    uint8_t val = registers["BC"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else if( val % 16 == 0 )    setFlag('H');           // When incrementing a number, the only case
                                                        // bit 3 can overflow is when a number of the form
                                                        // XXX01111 is incremented to XXX10000, therefore
                                                        // the result mod 16 equals 0
    resetFlag('N');

    return 4;
}

int cpu::op_DEC_B(void)
{
    // opCode 0x05
    // Decrements value in register B by 1
    // Flags: 
    //      - Sets Z if result is 0
    //      - N to 1
    //      - Sets H if borrows from bit 4
    // 4 Cycles, 1 byte

    registers["BC"]->decrementHighRegister();

    uint8_t val = registers["BC"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else if( val % 16 == 15 )   setFlag('H');           // When decrementing a number, the only case
                                                        // bit 4 is borrowed from is when a number of the form
                                                        // XXX10000 is decremented to XXX01111, therefore
                                                        // the result mod 16 equals 15

    setFlag('N');

    return 4;
}

int cpu::op_LD_Bn(void)
{
    // opCode 0x06
    // Loads next byte of memory
    // into B register
    // 8 Cycles, 2 bytes

    uint8_t val = getNextByte();
    registers["BC"]->setHighValue(val);
    
    return 8;
}

int cpu::op_RLC_A(void)
{
    // opCode 0x07
    // Rotate register A left
    // by 1 bit
    // Flags: 
    //      - Sets Z if result is 0
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 4 Cycles, 1 byte

    uint8_t carry = registers["AF"]->rotateHighLeft();

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    
    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 4;
}

int cpu::op_LD_aaSP(void)
{
    // opCode 0x08
    // Loads SP into address aa
    // 20 Cycles, 3 bytes

    uint8_t low  = registers["SP"]->getLowValue();
    uint8_t high = registers["SP"]->getHighValue();

    uint8_t lAddr = getNextByte();
    uint8_t hAddr = getNextByte();

    uint16_t addr = hAddr;
    addr = addr << 8;
    addr = addr + lAddr;

    mainMemory.writeToAddress(addr,low);
    mainMemory.writeToAddress(addr + 1,high);

    return 20;
}

int cpu::op_ADD_HLBC(void)
{
    // opCode 0x09
    // Add BC to HL
    // Flags: 
    //      - Reset N
    //      - Set H if bit 11 overflows
    //      - Set C if bit 15 overflows
    // 8 Cycles, 1 byte

    // TODO: Implement

    return 8;
}

int cpu::op_LD_ABC(void)
{
    // opCode 0x0A
    // Loads the value pointed to by
    // register BC into register A
    // 8 Cycles, 1 byte

    uint16_t addr = registers["BC"]->getTotalValue();
    uint8_t  val  = registers["AF"]->getHighValue();

    mainMemory.writeToAddress(addr,val);

    return 8;
}

int cpu::op_DEC_BC(void)
{
    // opCode 0x0B
    // Decrements value in register BC by 1
    // 8 Cycles, 1 byte

    registers["BC"]->decrementRegister();

    return 8;
}

int cpu::op_INC_C(void)
{
    // opCode 0x0C
    // Increments value in register C by 1
    // Flags: 
    //      - Sets Z if result is 0
    //      - N to 0
    //      - Sets H if bit 3 overflows
    // 4 Cycles, 1 byte

    registers["BC"]->incrementLowRegister();

    uint8_t val = registers["BC"]->getLowValue();

    if( val == 0 )          setFlag('Z');
    else if( val % 8 == 0 ) setFlag('H');

    resetFlag('N');

    return 4;
}

int cpu::op_DEC_C(void)
{
    // opCode 0x0D
    // Decrements value in register C by 1
    // Flags: 
    //      - Sets Z if result is 0
    //      - N to 1
    //      - Sets H if borrows from bit 4
    // 4 Cycles, 1 byte

    registers["BC"]->decrementLowRegister();

    uint8_t val = registers["BC"]->getLowValue();

    if( val == 0 )          setFlag('Z');
    else if( val % 8 == 7 ) setFlag('H');

    setFlag('N');


    return 4;
}

int cpu::op_LD_Cn(void)
{
    // opCode 0x0E
    // Loads next byte of memory
    // into C register
    // 8 Cycles, 2 bytes

    uint8_t val = getNextByte();
    registers["BC"]->setLowValue(val);

    return 8;
}

int cpu::op_RRC_A(void)
{
    // opCode 0x0F
    // Rotate register A right
    // by 1 bit
    // Flags: 
    //      - Sets Z if result is 0
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 4 Cycles, 1 byte

    uint8_t carry = registers["AF"]->rotateHighRight();

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    
    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 4;
}

int cpu::op_STOP(void)
{
    // opCode 0x10
    // Halt CPU & LCD Display until button pressed
    // 4 Cycles , 2 bytes
    // Note: Actually is a 2 byte instruction: 0x10 0x00

    // TODO: Implement

    return 4;
}

int cpu::op_LD_DEnn(void)
{
    // opCode 0x11
    // LD DE, nn
    // Loads next 2 bytes of memory
    // into DE register
    // 12 Cycles, 3 bytes

    uint8_t val;

    val = getNextByte();
    registers["DE"]->setLowValue(val);

    val = getNextByte();
    registers["DE"]->setHighValue(val);

    return 12;
}

int cpu::op_LD_DEA(void)
{
    // opCode 0x12
    // LD (DE), A
    // Loads value in register A into memory
    // location pointed to by register DE
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;

    addr = registers["DE"]->getTotalValue();
    val = registers["AF"]->getHighValue();

    mainMemory.writeToAddress(addr,val);

    return 8;
}

int cpu::op_INC_DE(void)
{
    // opCode 0x13
    // INC DE
    // Increments value in register DE by 1
    // 8 Cycles, 1 byte

    registers["DE"]->incrementRegister();

    return 8;
}

int cpu::op_INC_D(void)
{
    // opCode 0x14
    // INC D
    // Increments value in register D by 1
    // Flags: 
    //      - Sets Z if result is 0
    //      - N to 0
    //      - Sets H if bit 3 overflows
    // 4 Cycles, 1 byte

    registers["DE"]->incrementHighRegister();

    uint8_t val = registers["DE"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else if( val % 16 == 0 )    setFlag('H');           // When incrementing a number, the only case
                                                        // bit 3 can overflow is when a number of the form
                                                        // XXX01111 is incremented to XXX10000, therefore
                                                        // the result mod 16 equals 0
    resetFlag('N');

    return 4;
}

int cpu::op_DEC_D(void)
{
    // opCode 0x15
    // Decrements value in register D by 1
    // Flags: 
    //      - Sets Z if result is 0
    //      - N to 1
    //      - Sets H if borrows from bit 4
    // 4 Cycles, 1 byte

    registers["DE"]->decrementHighRegister();

    uint8_t val = registers["DE"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else if( val % 16 == 15 )   setFlag('H');           // When decrementing a number, the only case
                                                        // bit 4 is borrowed from is when a number of the form
                                                        // XXX10000 is decremented to XXX01111, therefore
                                                        // the result mod 16 equals 15

    setFlag('N');

    return 4;
}

int cpu::op_LD_Dn(void)
{
    // opCode 0x16
    // Loads next byte of memory
    // into D register
    // 8 Cycles, 2 bytes

    uint8_t val = getNextByte();
    registers["DE"]->setHighValue(val);
    
    return 8;
}

int cpu::op_RLA(void)
{
    // opCode 0x17
    // Rotate register A left
    // by 1 bit. Previous C flag
    // value written to new bit 0
    // Flags: 
    //      - Sets Z if result is 0
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 4 Cycles, 1 byte

    // TODO: Implement

    return 4;
}

int cpu::op_JR_n(void)
{
    // opCode 0x18
    // Add n to current address
    // and jump to it
    // 12 Cycles, 2 bytes

    // TODO: Implement

    return 12;
}

int cpu::op_ADD_HLDE(void)
{
    // opCode 0x19
    // Add DE to HL
    // Flags: 
    //      - Reset N
    //      - Set H if bit 11 overflows
    //      - Set C if bit 15 overflows
    // 8 Cycles, 1 byte

    // TODO: Implement

    return 8;
}

int cpu::op_LD_ADE(void)
{
    // opCode 0x1A
    // Loads the value pointed to by
    // register DE into register A
    // 8 Cycles, 1 byte

    uint16_t addr = registers["DE"]->getTotalValue();
    uint8_t  val  = registers["AF"]->getHighValue();

    mainMemory.writeToAddress(addr,val);
    return 8;
}

int cpu::op_DEC_DE(void)
{
    // opCode 0x1B
    // Decrements value in register DE by 1
    // 8 Cycles, 1 byte

    registers["DE"]->decrementRegister();

    return 8;
}

int cpu::op_INC_E(void)
{
    // opCode 0x1C
    // Increments value in register E by 1
    // Flags: 
    //      - Sets Z if result is 0
    //      - N to 0
    //      - Sets H if bit 3 overflows
    // 4 Cycles, 1 byte

    registers["DE"]->incrementLowRegister();

    uint8_t val = registers["DE"]->getLowValue();

    if( val == 0 )              setFlag('Z');
    else if( val % 16 == 0 )    setFlag('H');           // When incrementing a number, the only case
                                                        // bit 3 can overflow is when a number of the form
                                                        // XXX01111 is incremented to XXX10000, therefore
                                                        // the result mod 16 equals 0
    resetFlag('N');

    return 4;
}

int cpu::op_DEC_E(void)
{
    // opCode 0x1D
    // Decrements value in register E by 1
    // Flags: 
    //      - Sets Z if result is 0
    //      - N to 1
    //      - Sets H if borrows from bit 4
    // 4 Cycles, 1 byte

    registers["DE"]->decrementLowRegister();

    uint8_t val = registers["DE"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else if( val % 16 == 15 )   setFlag('H');           // When decrementing a number, the only case
                                                        // bit 4 is borrowed from is when a number of the form
                                                        // XXX10000 is decremented to XXX01111, therefore
                                                        // the result mod 16 equals 15

    setFlag('N');

    return 4;
}

int cpu::op_LD_En(void)
{
    // opCode 0x1E
    // Loads next byte of memory
    // into E register
    // 8 Cycles, 2 bytes

    uint8_t val = getNextByte();
    registers["DE"]->setLowValue(val);

    return 8;
}

int cpu::op_RLA(void)
{
    // opCode 0x1F
    // Rotate register A right
    // by 1 bit. Previous C flag
    // value written to new bit 7
    // Flags: 
    //      - Sets Z if result is 0
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 4 Cycles, 1 byte

    // TODO: Implement

    return 4;
}

int cpu::op_JR_NZn(void)
{
    // opCode 0x20
    // JR NZ, n
    //
    // If Z flag is reset
    // Adds n to current address
    // and jumps to it
    // 8 Cycles, 2 bytes

    // TODO: Implement

    return 8;
}

int cpu::op_LD_HLnn(void)
{
    // opCode 0x21
    // LD HL, nn
    //
    // Loads next 2 bytes of memory
    // into HL register
    // 12 Cycles, 3 bytes

    // TODO: Implement

    return 12;
}

int cpu::op_LD_HLincA(void)
{
    // opCode 0x22
    // LD (HL+), A
    //
    // Loads value in register A into memory
    // location pointed to by register HL
    // Then, increments HL
    // 8 Cycles, 1 byte

    // TODO: Implement

    return 8;
}

int cpu::op_INC_HL(void)
{
    // opCode 0x23
    // INC HL
    //
    // Increments value in register HL by 1
    // 8 Cycles, 1 byte

    // TODO: Implement

    return 8;
}

int cpu::op_INC_H(void)
{
    // opCode 0x24
    // INC H
    //
    // Increments value in register H by 1
    // Flags: 
    //      - Sets Z if result is 0
    //      - N to 0
    //      - Sets H if bit 3 overflows
    // 4 Cycles, 1 byte

    // TODO: Implement

    return 4;
}

int cpu::op_DEC_H(void)
{
    // opCode 0x25
    // DEC H
    //
    // Decrements value in register H by 1
    // Flags: 
    //      - Sets Z if result is 0
    //      - N to 1
    //      - Sets H if borrows from bit 4
    // 4 Cycles, 1 byte

    // TODO: Implement

    return 4;
}

int cpu::op_LD_Hn(void)
{
    // opCode 0x26
    // LD H, n
    //
    // Loads next byte of memory
    // into H register
    // 8 Cycles, 2 bytes

    // TODO: Implement
    
    return 8;
}

int cpu::op_DAA(void)
{
    // opCode 0x27
    // DAA
    //
    // Adjusts register A so that
    // the correct representation
    // of Binary Coded Decimal is
    // Obtained
    // Flags:
    //      - Sets Z if register A is 0
    //      - Resets H
    //      - Set/Reset C according to operation
    // 4 Cycles, 1 byte

    // TODO: Implement

    return 4;
}

int cpu::op_JR_Zn(void)
{
    // opCode 0x28
    // JR Z, n
    //
    // If Z flag is set
    // Adds n to current address
    // and jumps to it
    // 8 Cycles, 2 bytes

    // TODO: Implement

    return 8;
}

int cpu::op_ADD_HLHL(void)
{
    // opCode 0x29
    // ADD HL, HL
    //
    // Adds HL to HL
    // Flags: 
    //      - Reset N
    //      - Set H if bit 11 overflows
    //      - Set C if bit 15 overflows
    // 8 Cycles, 1 byte

    // TODO: Implement

    return 8;
}

int cpu::op_LD_AHLinc(void)
{
    // opCode 0x2A
    // LD A, (HL+)
    //
    // Loads the value pointed to by
    // register HL into register A
    // Then, increments HL
    // 8 Cycles, 1 byte

    // TODO: Implement

    return 8;
}

int cpu::op_DEC_HL(void)
{
    // opCode 0x2B
    // DEC HL
    //
    // Decrements value in register HL by 1
    // 8 Cycles, 1 byte

    // TODO: Implement

    return 8;
}

int cpu::op_INC_L(void)
{
    // opCode 0x2C
    // INC L
    //
    // Increments value in register L by 1
    // Flags: 
    //      - Sets Z if result is 0
    //      - N to 0
    //      - Sets H if bit 3 overflows
    // 4 Cycles, 1 byte

    // TODO: Implement

    return 4;
}

int cpu::op_DEC_L(void)
{
    // opCode 0x2D
    // DEC L
    //
    // Decrements value in register L by 1
    // Flags: 
    //      - Sets Z if result is 0
    //      - N to 1
    //      - Sets H if borrows from bit 4
    // 4 Cycles, 1 byte

    // TODO: Implement

    return 4;
}

int cpu::op_LD_Ln(void)
{
    // opCode 0x2E
    // LD L, n
    //
    // Loads next byte of memory
    // into E register
    // 8 Cycles, 2 bytes

    // TODO: Implement

    return 8;
}

int cpu::op_CPL(void)
{
    // opCode 0x2F
    // CPL
    //
    // Complements A register
    // ( Flips all bits )
    // Flags:
    //      - Sets N
    //      - Sets H
    // 4 Cycles, 1 byte

    // TODO: Implement

    return 4;
}