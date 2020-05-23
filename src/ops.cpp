#include "../header/cpu.hh"

int cpu::op_NOOP(void)
{
    // opCode 0x00
    // NOOP
    //
    // Does Nothing
    // 4 Cycles, 1 byte

    return 4;
}

int cpu::op_LD_BCnn(void)
{
    // opCode 0x01
    // LD BC, nn
    //
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
    //
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
    //
    // Increments value in register BC by 1
    // 8 Cycles, 1 byte

    registers["BC"]->incrementRegister();

    return 8;
}

int cpu::op_INC_B(void)
{
    // opCode 0x04
    // INC B
    //
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
    // DEC B
    //
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
    // LD B, n
    //
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
    // RLCA
    //
    // Rotates register A left
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
    // LD nn, SP
    //
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
    // ADD HL, BC
    // Adds BC to HL
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
    // LD A, BC
    //
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
    // DEC BC
    //
    // Decrements value in register BC by 1
    // 8 Cycles, 1 byte

    registers["BC"]->decrementRegister();

    return 8;
}

int cpu::op_INC_C(void)
{
    // opCode 0x0C
    // INC C
    //
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
    // DEC C
    //
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
    // LD C, n
    //
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
    // RRCA
    //
    // Rotates register A right
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
    // STOP 0
    //
    // Halt CPU & LCD Display until button pressed
    // Note: Actually is a 2 byte instruction: 0x10 0x00
    // 4 Cycles , 2 bytes

    // TODO: Implement

    return 4;
}

int cpu::op_LD_DEnn(void)
{
    // opCode 0x11
    // LD DE, nn
    //
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
    //
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
    //
    // Increments value in register DE by 1
    // 8 Cycles, 1 byte

    registers["DE"]->incrementRegister();

    return 8;
}

int cpu::op_INC_D(void)
{
    // opCode 0x14
    // INC D
    //
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
    // DEC D
    //
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
    // LD D, n
    //
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
    // RLA
    //
    // Rotates register A left
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
    // JR n
    //
    // Adds n to current address
    // and jumps to it
    // 12 Cycles, 2 bytes

    // TODO: Implement

    return 12;
}

int cpu::op_ADD_HLDE(void)
{
    // opCode 0x19
    // ADD HL, DE
    //
    // Adds DE to HL
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
    // LD A, DE
    //
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
    // DEC DE
    //
    // Decrements value in register DE by 1
    // 8 Cycles, 1 byte

    registers["DE"]->decrementRegister();

    return 8;
}

int cpu::op_INC_E(void)
{
    // opCode 0x1C
    // INC E
    //
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
    // DEC E
    //
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
    // LD E. n
    //
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
    // RLA
    //
    // Rotates register A right
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
    // If Z flag is not set
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

    uint8_t val;

    val = getNextByte();
    registers["HL"]->setLowValue(val);

    val = getNextByte();
    registers["HL"]->setHighValue(val);

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

    uint16_t addr;
    uint8_t val;

    addr = registers["HL"]->getTotalValue();
    val = registers["AF"]->getHighValue();

    mainMemory.writeToAddress(addr,val);

    registers["HL"]->incrementRegister();

    return 8;
}

int cpu::op_INC_HL(void)
{
    // opCode 0x23
    // INC HL
    //
    // Increments value in register HL by 1
    // 8 Cycles, 1 byte

    registers["HL"]->incrementRegister();

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

    registers["HL"]->incrementHighRegister();

    uint8_t val = registers["HL"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else if( val % 16 == 0 )    setFlag('H');           // When incrementing a number, the only case
                                                        // bit 3 can overflow is when a number of the form
                                                        // XXX01111 is incremented to XXX10000, therefore
                                                        // the result mod 16 equals 0
    resetFlag('N');

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

    registers["HL"]->decrementHighRegister();

    uint8_t val = registers["HL"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else if( val % 16 == 15 )   setFlag('H');           // When decrementing a number, the only case
                                                        // bit 4 is borrowed from is when a number of the form
                                                        // XXX10000 is decremented to XXX01111, therefore
                                                        // the result mod 16 equals 15

    setFlag('N');

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

    uint8_t val = getNextByte();
    registers["HL"]->setHighValue(val);
    
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

    uint16_t addr = registers["HL"]->getTotalValue();
    uint8_t  val  = registers["AF"]->getHighValue();

    mainMemory.writeToAddress(addr,val);

    registers["HL"]->incrementRegister();

    return 8;
}

int cpu::op_DEC_HL(void)
{
    // opCode 0x2B
    // DEC HL
    //
    // Decrements value in register HL by 1
    // 8 Cycles, 1 byte

    registers["BC"]->decrementRegister();

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

    registers["HL"]->incrementLowRegister();

    uint8_t val = registers["HL"]->getLowValue();

    if( val == 0 )          setFlag('Z');
    else if( val % 8 == 0 ) setFlag('H');

    resetFlag('N');

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

    registers["HL"]->decrementLowRegister();

    uint8_t val = registers["HL"]->getLowValue();

    if( val == 0 )          setFlag('Z');
    else if( val % 8 == 7 ) setFlag('H');

    setFlag('N');

    return 4;
}

int cpu::op_LD_Ln(void)
{
    // opCode 0x2E
    // LD L, n
    //
    // Loads next byte of memory
    // into L register
    // 8 Cycles, 2 bytes

    uint8_t val = getNextByte();
    registers["HL"]->setLowValue(val);

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

    uint8_t val = registers["AF"]->getHighValue();

    val = val^0xFF;

    registers["AF"]->setHighValue(val);

    setFlag('N');
    setFlag('H');

    return 4;
}

int cpu::op_JR_NCn(void)
{
    // opCode 0x30
    // JR NC, n
    //
    // If C flag is not set
    // Adds n to current address
    // and jumps to it
    // 8 Cycles, 2 bytes

    // TODO: Implement

    return 8;
}

int cpu::op_LD_SPnn(void)
{
    // opCode 0x31
    // LD SP, nn
    //
    // Loads next 2 bytes of memory
    // into SP register
    // 12 Cycles, 3 bytes

    uint8_t val;

    val = getNextByte();
    registers["SP"]->setLowValue(val);

    val = getNextByte();
    registers["SP"]->setHighValue(val);

    return 12;
}

int cpu::op_LD_HLdecA(void)
{
    // opCode 0x32
    // LD (HL-), A
    //
    // Loads value in register A into memory
    // location pointed to by register HL
    // Then, decrements HL
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;

    addr = registers["HL"]->getTotalValue();
    val = registers["AF"]->getHighValue();

    mainMemory.writeToAddress(addr,val);

    registers["HL"]->decrementRegister();

    return 8;
}

int cpu::op_INC_SP(void)
{
    // opCode 0x33
    // INC SP
    //
    // Increments value in register SP by 1
    // 8 Cycles, 1 byte

    registers["SP"]->incrementRegister();

    return 8;
}

int cpu::op_INC_HLaddr(void)
{
    // opCode 0x34
    // INC (HL)
    //
    // Increments value at memory address
    // register HL points to
    // Flags:
    //      - Sets Z if result is 0
    //      - Resets N
    //      - Sets H if bit 3 overflows
    // 12 Cycles, 1 byte
    
    // TODO: Implement

    return 12;
}

int cpu::op_DEC_HLaddr(void)
{
    // opCode 0x35
    // DEC (HL)
    //
    // Decrements value at memory address
    // register HL points to
    // Flags:
    //      - Sets Z if result is 0
    //      - Sets N
    //      - Sets H if borrows from bit 4
    // 12 Cycles, 1 byte
    
    // TODO: Implement

    return 12;
}

int cpu::op_LD_HLaddrn(void)
{
    // opCode 0x36
    // LD (HL), n
    //
    // Loads next byte of memory
    // into memory address register HL
    // points to
    // 12 Cycles, 8 bytes
    
    // TODO: Implement

    return 12;
}

int cpu::op_SCF(void)
{
    // opCode 0x37
    // SCF
    //
    // Sets the Carry Flag
    // Flags:
    //      - Reset N
    //      - Reset H
    //      - Set C
    // 4 Cycles, 1 byte

    resetFlag('N');
    resetFlag('H');
    setFlag('C');

    return 4;
}

int cpu::op_JR_Cn(void)
{
    // opCode 0x38
    // JR C, n
    //
    // If C flag is set
    // Adds n to current address
    // and jumps to it
    // 8 Cycles, 2 bytes

    // TODO: Implement

    return 8;
}

int cpu::op_ADD_HLSP(void)
{
    // opCode 0x39
    // ADD HL, SP
    //
    // Adds SP to HL
    // Flags: 
    //      - Reset N
    //      - Set H if bit 11 overflows
    //      - Set C if bit 15 overflows
    // 8 Cycles, 1 byte

    // TODO: Implement

    return 8;
}

int cpu::op_LD_AHLdec(void)
{
    // opCode 0x3A
    // LD A, (HL-)
    //
    // Loads the value pointed to by
    // register HL into register A
    // Then, decrements HL
    // 8 Cycles, 1 byte

    uint16_t addr = registers["HL"]->getTotalValue();
    uint8_t  val  = registers["AF"]->getHighValue();

    mainMemory.writeToAddress(addr,val);

    registers["HL"]->decrementRegister();

    return 8;
}

int cpu::op_DEC_SP(void)
{
    // opCode 0x3B
    // DEC SP
    //
    // Decrements value in register SP by 1
    // 8 Cycles, 1 byte

    registers["SP"]->decrementRegister();

    return 8;
}

int cpu::op_INC_A(void)
{
    // opCode 0x3C
    // INC A
    //
    // Increments value in register A by 1
    // Flags: 
    //      - Sets Z if result is 0
    //      - N to 0
    //      - Sets H if bit 3 overflows
    // 4 Cycles, 1 byte

    registers["AF"]->incrementHighRegister();

    uint8_t val = registers["AF"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else if( val % 16 == 0 )    setFlag('H');           // When incrementing a number, the only case
                                                        // bit 3 can overflow is when a number of the form
                                                        // XXX01111 is incremented to XXX10000, therefore
                                                        // the result mod 16 equals 0
    resetFlag('N');

    return 4;
}

int cpu::op_DEC_A(void)
{
    // opCode 0x3D
    // DEC A
    //
    // Decrements value in register A by 1
    // Flags: 
    //      - Sets Z if result is 0
    //      - N to 1
    //      - Sets H if borrows from bit 4
    // 4 Cycles, 1 byte

    registers["AF"]->decrementHighRegister();

    uint8_t val = registers["AF"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else if( val % 16 == 15 )   setFlag('H');           // When decrementing a number, the only case
                                                        // bit 4 is borrowed from is when a number of the form
                                                        // XXX10000 is decremented to XXX01111, therefore
                                                        // the result mod 16 equals 15

    setFlag('N');

    return 4;
}

int cpu::op_LD_An(void)
{
    // opCode 0x3E
    // LD A, n
    //
    // Loads next byte of memory
    // into A register
    // 8 Cycles, 2 bytes

    uint8_t val = getNextByte();
    registers["AF"]->setHighValue(val);

    return 8;
}

int cpu::op_CCF(void)
{
    // opCode 0x3F
    // CCF
    //
    // Complements Carry Flag
    // ( Resets if set and vice versa )
    // Flags:
    //      - Resets N
    //      - Resets H
    //      - Set/Reset C according to operation
    // 4 Cycles, 1 byte
    
    uint8_t CFlag = getFlag('C');

    resetFlag('N');
    resetFlag('H');

    if( CFlag == 0 )    setFlag('C');
    else                resetFlag('C');

    return 4;
}

int cpu::op_LD_BB(void)
{
    // opCode 0x40
    // LD B, B
    //
    // Loads value in register B
    // into register B
    // 4 Cycles, 1 byte

    uint8_t src = registers["BC"]->getHighValue();
    registers["BC"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_BC(void)
{
    // opCode 0x41
    // LD B, C
    //
    // Loads value in register C
    // into register B
    // 4 Cycles, 1 byte

    uint8_t src = registers["BC"]->getLowValue();
    registers["BC"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_BD(void)
{
    // opCode 0x42
    // LD B, D
    //
    // Loads value in register D
    // into register B
    // 4 Cycles, 1 byte

    uint8_t src = registers["DE"]->getHighValue();
    registers["BC"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_BE(void)
{
    // opCode 0x43
    // LD B, E
    //
    // Loads value in register E
    // into register B
    // 4 Cycles, 1 byte

    uint8_t src = registers["DE"]->getLowValue();
    registers["BC"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_BH(void)
{
    // opCode 0x44
    // LD B, H
    //
    // Loads value in register H
    // into register B
    // 4 Cycles, 1 byte

    uint8_t src = registers["HL"]->getHighValue();
    registers["BC"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_BL(void)
{
    // opCode 0x45
    // LD B, L
    //
    // Loads value in register L
    // into register B
    // 4 Cycles, 1 byte

    uint8_t src = registers["HL"]->getLowValue();
    registers["BC"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_BHL(void)
{
    // opCode 0x46
    // LD B, (HL)
    //
    // Loads value in memory address
    // that register HL points to
    // into register B
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;
    
    addr = registers["HL"]->getTotalValue();
    val  = mainMemory.readAddress(addr);

    registers["BC"]->setHighValue(val);

    return 8;
}

int cpu::op_LD_BA(void)
{
    // opCode 0x47
    // LD B, A
    //
    // Loads value in register A
    // into register B
    // 4 Cycles, 1 byte

    uint8_t src = registers["AF"]->getHighValue();
    registers["BC"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_CB(void)
{
    // opCode 0x48
    // LD C, B
    //
    // Loads value in register B
    // into register C
    // 4 Cycles, 1 byte

    uint8_t src = registers["BC"]->getHighValue();
    registers["BC"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_CC(void)
{
    // opCode 0x49
    // LD C, C
    //
    // Loads value in register C
    // into register C
    // 4 Cycles, 1 byte

    uint8_t src = registers["BC"]->getLowValue();
    registers["BC"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_CD(void)
{
    // opCode 0x4A
    // LD C, D
    //
    // Loads value in register D
    // into register C
    // 4 Cycles, 1 byte

    uint8_t src = registers["DE"]->getHighValue();
    registers["BC"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_CE(void)
{
    // opCode 0x4B
    // LD C, E
    //
    // Loads value in register E
    // into register C
    // 4 Cycles, 1 byte

    uint8_t src = registers["DE"]->getLowValue();
    registers["BC"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_CH(void)
{
    // opCode 0x4C
    // LD C, H
    //
    // Loads value in register H
    // into register C
    // 4 Cycles, 1 byte

    uint8_t src = registers["HL"]->getHighValue();
    registers["BC"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_CL(void)
{
    // opCode 0x4D
    // LD C, L
    //
    // Loads value in register L
    // into register C
    // 4 Cycles, 1 byte

    uint8_t src = registers["HL"]->getLowValue();
    registers["BC"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_CHL(void)
{
    // opCode 0x4E
    // LD C, (HL)
    //
    // Loads value in memory address
    // that register HL points to
    // into register C
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;
    
    addr = registers["HL"]->getTotalValue();
    val  = mainMemory.readAddress(addr);

    registers["BC"]->setLowValue(val);
    return 8;
}

int cpu::op_LD_CA(void)
{
    // opCode 0x4F
    // LD C, A
    //
    // Loads value in register A
    // into register C
    // 4 Cycles, 1 byte

    uint8_t src = registers["AF"]->getHighValue();
    registers["BC"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_DB(void)
{
    // opCode 0x50
    // LD D, B
    //
    // Loads value in register B
    // into register D
    // 4 Cycles, 1 byte

    uint8_t src = registers["BC"]->getHighValue();
    registers["DE"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_DC(void)
{
    // opCode 0x51
    // LD D, C
    //
    // Loads value in register C
    // into register D
    // 4 Cycles, 1 byte

    uint8_t src = registers["BC"]->getLowValue();
    registers["DE"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_DD(void)
{
    // opCode 0x52
    // LD D, D
    //
    // Loads value in register D
    // into register D
    // 4 Cycles, 1 byte

    uint8_t src = registers["DE"]->getHighValue();
    registers["DE"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_DE(void)
{
    // opCode 0x53
    // LD D, E
    //
    // Loads value in register E
    // into register D
    // 4 Cycles, 1 byte

    uint8_t src = registers["DE"]->getLowValue();
    registers["DE"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_DH(void)
{
    // opCode 0x54
    // LD D, H
    //
    // Loads value in register H
    // into register D
    // 4 Cycles, 1 byte

    uint8_t src = registers["HL"]->getHighValue();
    registers["DE"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_DL(void)
{
    // opCode 0x55
    // LD D, L
    //
    // Loads value in register L
    // into register D
    // 4 Cycles, 1 byte

    uint8_t src = registers["HL"]->getLowValue();
    registers["DE"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_DHL(void)
{
    // opCode 0x56
    // LD D, (HL)
    //
    // Loads value in memory address
    // that register HL points to
    // into register D
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;
    
    addr = registers["HL"]->getTotalValue();
    val  = mainMemory.readAddress(addr);

    registers["DE"]->setHighValue(val);

    return 8;
}

int cpu::op_LD_DA(void)
{
    // opCode 0x57
    // LD D, A
    //
    // Loads value in register A
    // into register D
    // 4 Cycles, 1 byte

    uint8_t src = registers["AF"]->getHighValue();
    registers["DE"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_EB(void)
{
    // opCode 0x58
    // LD E, B
    //
    // Loads value in register B
    // into register E
    // 4 Cycles, 1 byte

    uint8_t src = registers["BC"]->getHighValue();
    registers["DE"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_EC(void)
{
    // opCode 0x59
    // LD E, C
    //
    // Loads value in register C
    // into register E
    // 4 Cycles, 1 byte

    uint8_t src = registers["BC"]->getLowValue();
    registers["DE"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_ED(void)
{
    // opCode 0x5A
    // LD E, D
    //
    // Loads value in register D
    // into register E
    // 4 Cycles, 1 byte

    uint8_t src = registers["DE"]->getHighValue();
    registers["DE"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_EE(void)
{
    // opCode 0x5B
    // LD E, E
    //
    // Loads value in register E
    // into register E
    // 4 Cycles, 1 byte

    uint8_t src = registers["DE"]->getLowValue();
    registers["DE"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_EH(void)
{
    // opCode 0x5C
    // LD E, H
    //
    // Loads value in register H
    // into register E
    // 4 Cycles, 1 byte

    uint8_t src = registers["HL"]->getHighValue();
    registers["DE"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_EL(void)
{
    // opCode 0x5D
    // LD E, L
    //
    // Loads value in register L
    // into register E
    // 4 Cycles, 1 byte

    uint8_t src = registers["HL"]->getLowValue();
    registers["DE"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_EHL(void)
{
    // opCode 0x5E
    // LD E, (HL)
    //
    // Loads value in memory address
    // that register HL points to
    // into register E
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;
    
    addr = registers["HL"]->getTotalValue();
    val  = mainMemory.readAddress(addr);

    registers["DE"]->setLowValue(val);
    return 8;
}

int cpu::op_LD_EA(void)
{
    // opCode 0x5F
    // LD E, A
    //
    // Loads value in register A
    // into register E
    // 4 Cycles, 1 byte

    uint8_t src = registers["AF"]->getHighValue();
    registers["DE"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_HB(void)
{
    // opCode 0x60
    // LD H, B
    //
    // Loads value in register B
    // into register H
    // 4 Cycles, 1 byte

    uint8_t src = registers["BC"]->getHighValue();
    registers["HL"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_HC(void)
{
    // opCode 0x61
    // LD H, C
    //
    // Loads value in register C
    // into register H
    // 4 Cycles, 1 byte

    uint8_t src = registers["BC"]->getLowValue();
    registers["HL"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_HD(void)
{
    // opCode 0x62
    // LD H, D
    //
    // Loads value in register D
    // into register H
    // 4 Cycles, 1 byte

    uint8_t src = registers["DE"]->getHighValue();
    registers["HL"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_HE(void)
{
    // opCode 0x63
    // LD H, E
    //
    // Loads value in register E
    // into register H
    // 4 Cycles, 1 byte

    uint8_t src = registers["DE"]->getLowValue();
    registers["HL"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_HH(void)
{
    // opCode 0x64
    // LD H, H
    //
    // Loads value in register H
    // into register H
    // 4 Cycles, 1 byte

    uint8_t src = registers["HL"]->getHighValue();
    registers["HL"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_HL(void)
{
    // opCode 0x65
    // LD H, L
    //
    // Loads value in register L
    // into register H
    // 4 Cycles, 1 byte

    uint8_t src = registers["HL"]->getLowValue();
    registers["HL"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_HHL(void)
{
    // opCode 0x66
    // LD H, (HL)
    //
    // Loads value in memory address
    // that register HL points to
    // into register H
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;
    
    addr = registers["HL"]->getTotalValue();
    val  = mainMemory.readAddress(addr);

    registers["HL"]->setHighValue(val);

    return 8;
}

int cpu::op_LD_HA(void)
{
    // opCode 0x67
    // LD H, A
    //
    // Loads value in register A
    // into register H
    // 4 Cycles, 1 byte

    uint8_t src = registers["AF"]->getHighValue();
    registers["HL"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_LB(void)
{
    // opCode 0x68
    // LD L, B
    //
    // Loads value in register B
    // into register L
    // 4 Cycles, 1 byte

    uint8_t src = registers["BC"]->getHighValue();
    registers["HL"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_LC(void)
{
    // opCode 0x69
    // LD L, C
    //
    // Loads value in register C
    // into register L
    // 4 Cycles, 1 byte

    uint8_t src = registers["BC"]->getLowValue();
    registers["HL"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_LD(void)
{
    // opCode 0x6A
    // LD L, D
    //
    // Loads value in register D
    // into register L
    // 4 Cycles, 1 byte

    uint8_t src = registers["DE"]->getHighValue();
    registers["HL"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_LE(void)
{
    // opCode 0x6B
    // LD L, E
    //
    // Loads value in register E
    // into register L
    // 4 Cycles, 1 byte

    uint8_t src = registers["DE"]->getLowValue();
    registers["HL"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_LH(void)
{
    // opCode 0x6C
    // LD L, H
    //
    // Loads value in register H
    // into register L
    // 4 Cycles, 1 byte

    uint8_t src = registers["HL"]->getHighValue();
    registers["HL"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_LL(void)
{
    // opCode 0x6D
    // LD L, L
    //
    // Loads value in register L
    // into register L
    // 4 Cycles, 1 byte

    uint8_t src = registers["HL"]->getLowValue();
    registers["HL"]->setLowValue(src);

    return 4;
}

int cpu::op_LD_LHL(void)
{
    // opCode 0x6E
    // LD L, (HL)
    //
    // Loads value in memory address
    // that register HL points to
    // into register L
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;
    
    addr = registers["HL"]->getTotalValue();
    val  = mainMemory.readAddress(addr);

    registers["HL"]->setLowValue(val);
    return 8;
}

int cpu::op_LD_LA(void)
{
    // opCode 0x6F
    // LD L, A
    //
    // Loads value in register A
    // into register L
    // 4 Cycles, 1 byte

    uint8_t src = registers["AF"]->getHighValue();
    registers["HL"]->setLowValue(src);

    return 4;
}