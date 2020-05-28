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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H if bit 3 overflows; Otherwise Resets H
    // 4 Cycles, 1 byte

    registers["BC"]->incrementHighRegister();

    uint8_t val = registers["BC"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');

    if( val % 16 == 0 )         setFlag('H');           // When incrementing a number, the only case
    else                        resetFlag('H');         // bit 3 can overflow is when a number of the form
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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if borrows from bit 4; Otherwise Resets H
    // 4 Cycles, 1 byte

    registers["BC"]->decrementHighRegister();

    uint8_t val = registers["BC"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');

    if( val % 16 == 15 )        setFlag('H');           // When decrementing a number, the only case
    else                        resetFlag('H');         // bit 4 is borrowed from is when a number of the form
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

int cpu::op_RLCA(void)
{
    // opCode 0x07
    // RLCA
    //
    // Rotates register A left
    // by 1 bit
    // Flags: 
    //      - Resets Z
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 4 Cycles, 1 byte

    uint8_t carry = registers["AF"]->rotateHighLeft();

    resetFlag('Z');
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
    mainMemory.writeToAddress(addr + 1, high);

    return 20;
}

int cpu::op_ADD_HLBC(void)
{
    // opCode 0x09
    // ADD HL, BC
    // Adds BC to HL
    // Flags: 
    //      - Reset N
    //      - Set H if bit 11 overflows; Otherwise Reset
    //      - Set C if bit 15 overflows; Otherwise Reset
    // 8 Cycles, 1 byte

    uint8_t flags;
    uint16_t srcVal;

    srcVal = registers["BC"]->getTotalValue();
    flags  = add16Bit(srcVal,"HL");

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

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
    uint8_t  val  = mainMemory.readAddress(addr);

    registers["AF"]->setHighValue(val);

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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H if bit 3 overflows; Otherwise Resets H
    // 4 Cycles, 1 byte

    registers["BC"]->incrementLowRegister();

    uint8_t val = registers["BC"]->getLowValue();

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');

    if( val % 16 == 0 )         setFlag('H');           // When incrementing a number, the only case
    else                        resetFlag('H');         // bit 3 can overflow is when a number of the form
                                                        // XXX01111 is incremented to XXX10000, therefore
                                                        // the result mod 16 equals 0
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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if borrows from bit 4; Otherwise Resets H
    // 4 Cycles, 1 byte

    registers["BC"]->decrementLowRegister();

    uint8_t val = registers["BC"]->getLowValue();

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');
    
    if( val % 16 == 15 )        setFlag('H');           // When decrementing a number, the only case
    else                        resetFlag('H');         // bit 4 is borrowed from is when a number of the form
                                                        // XXX10000 is decremented to XXX01111, therefore
                                                        // the result mod 16 equals 15

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

int cpu::op_RRCA(void)
{
    // opCode 0x0F
    // RRCA
    //
    // Rotates register A right
    // by 1 bit
    // Flags: 
    //      - Reset Z
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 4 Cycles, 1 byte

    uint8_t carry = registers["AF"]->rotateHighRight();

    resetFlag('Z');
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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H if bit 3 overflows; Otherwise Resets H
    // 4 Cycles, 1 byte

    registers["DE"]->incrementHighRegister();

    uint8_t val = registers["DE"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');

    if( val % 16 == 0 )         setFlag('H');           // When incrementing a number, the only case
    else                        resetFlag('H');         // bit 3 can overflow is when a number of the form
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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if borrows from bit 4; Otherwise Resets H
    // 4 Cycles, 1 byte

    registers["DE"]->decrementHighRegister();

    uint8_t val = registers["DE"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');

    if( val % 16 == 15 )        setFlag('H');           // When decrementing a number, the only case
    else                        resetFlag('H');         // bit 4 is borrowed from is when a number of the form
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
    //      - Reset Z
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 4 Cycles, 1 byte

    uint8_t bit7, val, flag;

    bit7 = registers["AF"]->rotateHighLeft();
    val  = registers["AF"]->getHighValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0xFE;
    else                val = val | 0x01;

    registers["AF"]->setHighValue(val);

    resetFlag('Z');
    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

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

    uint8_t val;
    uint16_t totalVal;

    val = getNextByte();
    totalVal = registers["PC"]->getTotalValue();

    if( (val & 0x80) != 0 ) totalVal -= ((val^0xFF) + 1);
    else                    totalVal += val;

    registers["PC"]->setTotalValue(totalVal);

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
    //      - Set H if bit 11 overflows; Otherwise Reset
    //      - Set C if bit 15 overflows; Otherwise Reset
    // 8 Cycles, 1 byte

    uint8_t flags;
    uint16_t srcVal;

    srcVal = registers["DE"]->getTotalValue();
    flags  = add16Bit(srcVal,"HL");

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H if bit 3 overflows; Otherwise Resets H
    // 4 Cycles, 1 byte

    registers["DE"]->incrementLowRegister();

    uint8_t val = registers["DE"]->getLowValue();

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');

    if( val % 16 == 0 )         setFlag('H');           // When incrementing a number, the only case
    else                        resetFlag('H');         // bit 3 can overflow is when a number of the form
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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if borrows from bit 4; Otherwise Resets H
    // 4 Cycles, 1 byte

    registers["DE"]->decrementLowRegister();

    uint8_t val = registers["DE"]->getLowValue();

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');
    
    if( val % 16 == 15 )        setFlag('H');           // When decrementing a number, the only case
    else                        resetFlag('H');         // bit 4 is borrowed from is when a number of the form
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

int cpu::op_RRA(void)
{
    // opCode 0x1F
    // RRA
    //
    // Rotates register A right
    // by 1 bit. Previous C flag
    // value written to new bit 7
    // Flags: 
    //      - Reset Z
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 4 Cycles, 1 byte

    uint8_t bit0, val, flag;

    bit0 = registers["AF"]->rotateHighRight();
    val  = registers["AF"]->getHighValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0x7F;
    else                val = val | 0x80;

    registers["AF"]->setHighValue(val);

    resetFlag('Z');
    resetFlag('N');
    resetFlag('H');

    if( bit0 == 0 )     resetFlag('C');
    else                setFlag('C');

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
    // 12 Cycles if Jump, 8 Cycles if not Jump, 2 bytes

    uint8_t val;
    uint16_t totalVal;

    if( getFlag('Z') == 0 )
    {
        val = getNextByte();
        totalVal = registers["PC"]->getTotalValue();

        if( (val & 0x80) != 0 ) totalVal -= ((val^0xFF) + 1);
        else                    totalVal += val;

        registers["PC"]->setTotalValue(totalVal);

        return 12;
    }

    registers["PC"]->incrementRegister();
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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H if bit 3 overflows; Otherwise Resets H
    // 4 Cycles, 1 byte

    registers["HL"]->incrementHighRegister();

    uint8_t val = registers["HL"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');

    if( val % 16 == 0 )         setFlag('H');           // When incrementing a number, the only case
    else                        resetFlag('H');         // bit 3 can overflow is when a number of the form
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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if borrows from bit 4; Otherwise Resets H
    // 4 Cycles, 1 byte

    registers["HL"]->decrementHighRegister();

    uint8_t val = registers["HL"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');

    if( val % 16 == 15 )        setFlag('H');           // When decrementing a number, the only case
    else                        resetFlag('H');         // bit 4 is borrowed from is when a number of the form
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

    uint8_t val;
    uint16_t totalVal;

    if( getFlag('Z') == 1 )
    {
        val = getNextByte();
        totalVal = registers["PC"]->getTotalValue();

        if( (val & 0x80) != 0 ) totalVal -= ((val^0xFF) + 1);
        else                    totalVal += val;

        registers["PC"]->setTotalValue(totalVal);

        return 12;
    }

    registers["PC"]->incrementRegister();
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
    //      - Set H if bit 11 overflows; Otherwise Reset
    //      - Set C if bit 15 overflows; Otherwise Reset
    // 8 Cycles, 1 byte

    uint8_t flags;
    uint16_t srcVal;

    srcVal = registers["HL"]->getTotalValue();
    flags  = add16Bit(srcVal,"HL");

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H if bit 3 overflows; Otherwise Resets H
    // 4 Cycles, 1 byte

    registers["HL"]->incrementLowRegister();

    uint8_t val = registers["HL"]->getLowValue();

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');

    if( val % 16 == 0 )         setFlag('H');           // When incrementing a number, the only case
    else                        resetFlag('H');         // bit 3 can overflow is when a number of the form
                                                        // XXX01111 is incremented to XXX10000, therefore
                                                        // the result mod 16 equals 0
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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if borrows from bit 4; Otherwise Resets H
    // 4 Cycles, 1 byte

    registers["HL"]->decrementLowRegister();

    uint8_t val = registers["HL"]->getLowValue();

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');
    
    if( val % 16 == 15 )        setFlag('H');           // When decrementing a number, the only case
    else                        resetFlag('H');         // bit 4 is borrowed from is when a number of the form
                                                        // XXX10000 is decremented to XXX01111, therefore
                                                        // the result mod 16 equals 15

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

    uint8_t val;
    uint16_t totalVal;

    if( getFlag('C') == 0 )
    {
        val = getNextByte();
        totalVal = registers["PC"]->getTotalValue();

        if( (val & 0x80) != 0 ) totalVal -= ((val^0xFF) + 1);
        else                    totalVal += val;

        registers["PC"]->setTotalValue(totalVal);

        return 12;
    }

    registers["PC"]->incrementRegister();
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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H if bit 3 overflows; Otherwise Resets H
    // 12 Cycles, 1 byte
    
    uint8_t val;
    uint16_t addr;
    
    addr = registers["HL"]->getTotalValue();
    val  = mainMemory.readAddress(addr);

    val++;

    mainMemory.writeToAddress(addr,val);

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');

    if( val % 16 == 0 )         setFlag('H');           // When incrementing a number, the only case
    else                        resetFlag('H');         // bit 3 can overflow is when a number of the form
                                                        // XXX01111 is incremented to XXX10000, therefore
                                                        // the result mod 16 equals 0
    resetFlag('N');

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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if borrows from bit 4; Otherwise Resets H
    // 12 Cycles, 1 byte
    
    uint8_t val;
    uint16_t addr;
    
    addr = registers["HL"]->getTotalValue();
    val  = mainMemory.readAddress(addr);

    val--;

    mainMemory.writeToAddress(addr,val);

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');
    
    if( val % 16 == 15 )        setFlag('H');           // When decrementing a number, the only case
    else                        resetFlag('H');         // bit 4 is borrowed from is when a number of the form
                                                        // XXX10000 is decremented to XXX01111, therefore
                                                        // the result mod 16 equals 15

    setFlag('N');

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
    
    uint16_t addrSP, addrHL;
    uint8_t val;
    
    addrSP = registers["SP"]->getTotalValue();
    addrHL = registers["HL"]->getTotalValue();

    val    = mainMemory.readAddress(addrSP);
    mainMemory.writeToAddress(addrHL,val);

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

    uint8_t val;
    uint16_t totalVal;

    if( getFlag('C') == 1 )
    {
        val = getNextByte();
        totalVal = registers["PC"]->getTotalValue();

        if( (val & 0x80) != 0 ) totalVal -= ((val^0xFF) + 1);
        else                    totalVal += val;

        registers["PC"]->setTotalValue(totalVal);

        return 12;
    }

    registers["PC"]->incrementRegister();
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
    //      - Set H if bit 11 overflows; Otherwise Reset
    //      - Set C if bit 15 overflows; Otherwise Reset
    // 8 Cycles, 1 byte

    uint8_t flags;
    uint16_t srcVal;

    srcVal = registers["SP"]->getTotalValue();
    flags  = add16Bit(srcVal,"HL");

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H if bit 3 overflows; Otherwise Resets H
    // 4 Cycles, 1 byte

    registers["AF"]->incrementHighRegister();

    uint8_t val = registers["AF"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');

    if( val % 16 == 0 )         setFlag('H');           // When incrementing a number, the only case
    else                        resetFlag('H');         // bit 3 can overflow is when a number of the form
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
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if borrows from bit 4; Otherwise Resets H
    // 4 Cycles, 1 byte

    registers["AF"]->decrementHighRegister();

    uint8_t val = registers["AF"]->getHighValue();

    if( val == 0 )              setFlag('Z');
    else                        resetFlag('Z');
    
    if( val % 16 == 15 )        setFlag('H');           // When decrementing a number, the only case
    else                        resetFlag('H');         // bit 4 is borrowed from is when a number of the form
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

int cpu::op_LD_HLB(void)
{
    // opCode 0x70
    // LD (HL), B
    //
    // Loads value in register B
    // into memory address
    // that register HL points to
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;
    
    addr = registers["HL"]->getTotalValue();
    val  = registers["BC"]->getHighValue();

    mainMemory.writeToAddress(addr,val);
    
    return 8;
}

int cpu::op_LD_HLC(void)
{
    // opCode 0x71
    // LD (HL), C
    //
    // Loads value in register C
    // into memory address
    // that register HL points to
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;
    
    addr = registers["HL"]->getTotalValue();
    val  = registers["BC"]->getLowValue();

    mainMemory.writeToAddress(addr,val);
    
    return 8;
}

int cpu::op_LD_HLD(void)
{
    // opCode 0x72
    // LD (HL), D
    //
    // Loads value in register D
    // into memory address
    // that register HL points to
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;
    
    addr = registers["HL"]->getTotalValue();
    val  = registers["DE"]->getHighValue();

    mainMemory.writeToAddress(addr,val);
    
    return 8; 
}

int cpu::op_LD_HLE(void)
{
    // opCode 0x73
    // LD (HL), E
    //
    // Loads value in register E
    // into memory address
    // that register HL points to
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;
    
    addr = registers["HL"]->getTotalValue();
    val  = registers["DE"]->getLowValue();

    mainMemory.writeToAddress(addr,val);
    
    return 8;
}

int cpu::op_LD_HLH(void)
{
    // opCode 0x74
    // LD (HL), H
    //
    // Loads value in register H
    // into memory address
    // that register HL points to
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;
    
    addr = registers["HL"]->getTotalValue();
    val  = registers["HL"]->getHighValue();

    mainMemory.writeToAddress(addr,val);
    
    return 8;
}

int cpu::op_LD_HLL(void)
{
    // opCode 0x75
    // LD (HL), L
    //
    // Loads value in register L
    // into memory address
    // that register HL points to
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;
    
    addr = registers["HL"]->getTotalValue();
    val  = registers["HL"]->getLowValue();

    mainMemory.writeToAddress(addr,val);
    
    return 8;
}

int cpu::op_HALT(void)
{
    // opCode 0x76
    // HALT
    //
    // Powers down CPU until
    // an interrupt occurs
    // 4 Cycles, 1 byte

    // TODO: Implement

    return 4;
}

int cpu::op_LD_HLA(void)
{
    // opCode 0x77
    // LD (HL), A
    //
    // Loads value in register A
    // into memory address
    // that register HL points to
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;
    
    addr = registers["HL"]->getTotalValue();
    val  = registers["AF"]->getHighValue();

    mainMemory.writeToAddress(addr,val);
    
    return 8;
}

int cpu::op_LD_AB(void)
{
    // opCode 0x78
    // LD A, B
    //
    // Loads value in register B
    // into register A
    // 4 Cycles, 1 byte

    uint8_t src = registers["BC"]->getHighValue();
    registers["AF"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_AC(void)
{
    // opCode 0x79
    // LD A, C
    //
    // Loads value in register C
    // into register A
    // 4 Cycles, 1 byte

    uint8_t src = registers["BC"]->getLowValue();
    registers["AF"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_AD(void)
{
    // opCode 0x7A
    // LD A, D
    //
    // Loads value in register D
    // into register A
    // 4 Cycles, 1 byte

    uint8_t src = registers["DE"]->getHighValue();
    registers["AF"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_AE(void)
{
    // opCode 0x7B
    // LD A, E
    //
    // Loads value in register E
    // into register A
    // 4 Cycles, 1 byte

    uint8_t src = registers["DE"]->getLowValue();
    registers["AF"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_AH(void)
{
    // opCode 0x7C
    // LD A, H
    //
    // Loads value in register H
    // into register A
    // 4 Cycles, 1 byte

    uint8_t src = registers["HL"]->getHighValue();
    registers["AF"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_AL(void)
{
    // opCode 0x7D
    // LD A, L
    //
    // Loads value in register L
    // into register A
    // 4 Cycles, 1 byte

    uint8_t src = registers["HL"]->getLowValue();
    registers["AF"]->setHighValue(src);

    return 4;
}

int cpu::op_LD_AHL(void)
{
    // opCode 0x7E
    // LD A, (HL)
    //
    // Loads value in memory address
    // that register HL points to
    // into register A
    // 8 Cycles, 1 byte

    uint16_t addr;
    uint8_t val;
    
    addr = registers["HL"]->getTotalValue();
    val  = mainMemory.readAddress(addr);

    registers["AF"]->setHighValue(val);
    return 8;
}

int cpu::op_LD_AA(void)
{
    // opCode 0x7F
    // LD A, A
    //
    // Loads value in register A
    // into register A
    // 4 Cycles, 1 byte

    uint8_t src = registers["AF"]->getHighValue();
    registers["AF"]->setHighValue(src);

    return 4;
}

int cpu::op_ADD_AB(void)
{
    // opCode 0x80
    // ADD A, B
    //
    // Adds value in register B
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["BC"]->getHighValue();
    flags  = add8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_ADD_AC(void)
{
    // opCode 0x81
    // ADD A, C
    //
    // Adds value in register C
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["BC"]->getLowValue();
    flags  = add8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_ADD_AD(void)
{
    // opCode 0x82
    // ADD A, D
    //
    // Adds value in register D
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["DE"]->getHighValue();
    flags  = add8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_ADD_AE(void)
{
    // opCode 0x83
    // ADD A, E
    //
    // Adds value in register E
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["DE"]->getLowValue();
    flags  = add8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_ADD_AH(void)
{
    // opCode 0x84
    // ADD A, H
    //
    // Adds value in register H
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["HL"]->getHighValue();
    flags  = add8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_ADD_AL(void)
{
    // opCode 0x85
    // ADD A, L
    //
    // Adds value in register L
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["HL"]->getLowValue();
    flags  = add8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_ADD_AHL(void)
{
    // opCode 0x86
    // ADD A, (HL)
    //
    // Adds value in memory address
    // that register HL points to
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 8 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    srcVal = mainMemory.readAddress(addr);
    flags  = add8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 8;
}

int cpu::op_ADD_AA(void)
{
    // opCode 0x87
    // ADD A, A
    //
    // Adds value in register A
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["AF"]->getHighValue();
    flags  = add8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_ADC_AB(void)
{
    // opCode 0x88
    // ADC A, B
    //
    // Adds value in register B
    // plus the Carry Flag
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["BC"]->getHighValue();
    flags = add8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_ADC_AC(void)
{
    // opCode 0x89
    // ADC A, C
    //
    // Adds value in register C
    // plus the Carry Flag
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["BC"]->getLowValue();
    flags = add8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_ADC_AD(void)
{
    // opCode 0x8A
    // ADC A, D
    //
    // Adds value in register D
    // plus the Carry Flag
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["DE"]->getHighValue();
    flags = add8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_ADC_AE(void)
{
    // opCode 0x8B
    // ADC A, E
    //
    // Adds value in register E
    // plus the Carry Flag
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["DE"]->getLowValue();
    flags = add8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_ADC_AH(void)
{
    // opCode 0x8C
    // ADC A, H
    //
    // Adds value in register H
    // plus the Carry Flag
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["HL"]->getHighValue();
    flags = add8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_ADC_AL(void)
{
    // opCode 0x8D
    // ADC A, L
    //
    // Adds value in register L
    // plus the Carry Flag
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["HL"]->getLowValue();
    flags = add8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_ADC_AHL(void)
{
    // opCode 0x8E
    // ADC A, (HL)
    //
    // Adds value in memory address
    // that register HL points to
    // plus the Carry Flag
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 8 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    srcVal = mainMemory.readAddress(addr);
    flags = add8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 8;
}

int cpu::op_ADC_AA(void)
{
    // opCode 0x8F
    // ADC A, A
    //
    // Adds value in register A
    // plus the Carry Flag
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["AF"]->getHighValue();
    flags = add8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_SUB_B(void)
{
    // opCode 0x90
    // SUB B
    //
    // Subtracts value in register B
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["BC"]->getHighValue();
    flags = subtract8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_SUB_C(void)
{
    // opCode 0x91
    // SUB C
    //
    // Subtracts value in register C
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["BC"]->getLowValue();
    flags = subtract8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_SUB_D(void)
{
    // opCode 0x92
    // SUB D
    //
    // Subtracts value in register D
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["DE"]->getHighValue();
    flags = subtract8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_SUB_E(void)
{
    // opCode 0x93
    // SUB E
    //
    // AdSubtractsds value in register E
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["DE"]->getLowValue();
    flags = subtract8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_SUB_H(void)
{
    // opCode 0x94
    // SUB H
    //
    // Subtracts value in register H
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["HL"]->getHighValue();
    flags = subtract8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_SUB_L(void)
{
    // opCode 0x95
    // SUB L
    //
    // Subtracts value in register L
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["HL"]->getLowValue();
    flags = subtract8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_SUB_HL(void)
{
    // opCode 0x96
    // SUB (HL)
    //
    // Subtracts value in memory address
    // that register HL points to
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    srcVal = mainMemory.readAddress(addr);
    flags = subtract8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 8;
}

int cpu::op_SUB_A(void)
{
    // opCode 0x97
    // SUB A
    //
    // Subtracts value in register A
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["AF"]->getHighValue();
    flags = subtract8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_SBC_AB(void)
{
    // opCode 0x98
    // SBC A, B
    //
    // Subtracts value in register B
    // plus the Carry Flag
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["BC"]->getHighValue();
    flags = subtract8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_SBC_AC(void)
{
    // opCode 0x99
    // SBC A, C
    //
    // Subtracts value in register C
    // plus the Carry Flag
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["BC"]->getLowValue();
    flags = subtract8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_SBC_AD(void)
{
    // opCode 0x9A
    // SBC A, D
    //
    // Subtracts value in register D
    // plus the Carry Flag
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["DE"]->getHighValue();
    flags = subtract8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_SBC_AE(void)
{
    // opCode 0x9B
    // SBC A, E
    //
    // AdSubtractsds value in register E
    // plus the Carry Flag
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["DE"]->getLowValue();
    flags = subtract8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_SBC_AH(void)
{
    // opCode 0x9C
    // SBC A, H
    //
    // Subtracts value in register H
    // plus the Carry Flag
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["HL"]->getHighValue();
    flags = subtract8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_SBC_AL(void)
{
    // opCode 0x9D
    // SBC A, L
    //
    // Subtracts value in register L
    // plus the Carry Flag
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["HL"]->getLowValue();
    flags = subtract8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_SBC_AHL(void)
{
    // opCode 0x9E
    // SBC A, (HL)
    //
    // Subtracts value in memory address
    // that register HL points to
    // plus the Carry Flag
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    srcVal = mainMemory.readAddress(addr);
    flags = subtract8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 8;
}

int cpu::op_SBC_AA(void)
{
    // opCode 0x9F
    // SBC A, A
    //
    // Subtracts value in register A
    // plus the Carry Flag
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["AF"]->getHighValue();
    flags = subtract8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    setFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 4;
}

int cpu::op_AND_B(void)
{
    // opCode 0xA0
    // AND B
    //
    // Takes the logical AND of
    // the contents of register B
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["BC"]->getHighValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 & val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    setFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_AND_C(void)
{
    // opCode 0xA1
    // AND C
    //
    // Takes the logical AND of
    // the contents of register C
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["BC"]->getLowValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 & val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    setFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_AND_D(void)
{
    // opCode 0xA2
    // AND D
    //
    // Takes the logical AND of
    // the contents of register D
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["DE"]->getHighValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 & val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    setFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_AND_E(void)
{
    // opCode 0xA3
    // AND E
    //
    // Takes the logical AND of
    // the contents of register E
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["DE"]->getLowValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 & val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    setFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_AND_H(void)
{
    // opCode 0xA4
    // AND H
    //
    // Takes the logical AND of
    // the contents of register H
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["HL"]->getHighValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 & val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    setFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_AND_L(void)
{
    // opCode 0xA5
    // AND L
    //
    // Takes the logical AND of
    // the contents of register L
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["HL"]->getLowValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 & val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    setFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_AND_HL(void)
{
    // opCode 0xA6
    // AND (HL)
    //
    // Takes the logical AND of
    // the contents of THE memory address
    // that register HL points to
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H
    //      - Resets C
    // 8 Cycles, 1 byte

    uint8_t val1, val2, res;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    val1 = mainMemory.readAddress(addr);
    val2 = registers["AF"]->getHighValue();

    res  = val1 & val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    setFlag('H');
    resetFlag('C'); 

    return 8;
}

int cpu::op_AND_A(void)
{
    // opCode 0xA7
    // AND A
    //
    // Takes the logical AND of
    // the contents of register A
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["AF"]->getHighValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 & val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    setFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_XOR_B(void)
{
    // opCode 0xA8
    // XOR B
    //
    // Takes the logical XOR of
    // the contents of register B
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["BC"]->getHighValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 ^ val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_XOR_C(void)
{
    // opCode 0xA9
    // XOR C
    //
    // Takes the logical XOR of
    // the contents of register C
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["BC"]->getLowValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 ^ val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_XOR_D(void)
{
    // opCode 0xAA
    // XOR D
    //
    // Takes the logical XOR of
    // the contents of register D
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["DE"]->getHighValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 ^ val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_XOR_E(void)
{
    // opCode 0xAB
    // XOR E
    //
    // Takes the logical XOR of
    // the contents of register E
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["DE"]->getLowValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 ^ val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_XOR_H(void)
{
    // opCode 0xAC
    // XOR H
    //
    // Takes the logical XOR of
    // the contents of register H
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["HL"]->getHighValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 ^ val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C');

    return 4;
}

int cpu::op_XOR_L(void)
{
    // opCode 0xAD
    // XOR L
    //
    // Takes the logical XOR of
    // the contents of register L
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["HL"]->getLowValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 ^ val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C');

    return 4;
}

int cpu::op_XOR_HL(void)
{
    // opCode 0xAE
    // XOR (HL)
    //
    // Takes the logical XOR of
    // the contents of THE memory address
    // that register HL points to
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 8 Cycles, 1 byte

    uint8_t val1, val2, res;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    val1 = mainMemory.readAddress(addr);
    val2 = registers["AF"]->getHighValue();

    res  = val1 ^ val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C'); 

    return 8;
}

int cpu::op_XOR_A(void)
{
    // opCode 0xAF
    // XOR A
    //
    // Takes the logical XOR of
    // the contents of register A
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["AF"]->getHighValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 ^ val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C');

    return 4;
}

int cpu::op_OR_B(void)
{
    // opCode 0xB0
    // OR B
    //
    // Takes the logical OR of
    // the contents of register B
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["BC"]->getHighValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 | val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_OR_C(void)
{
    // opCode 0xB1
    // OR C
    //
    // Takes the logical OR of
    // the contents of register C
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["BC"]->getLowValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 | val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_OR_D(void)
{
    // opCode 0xB2
    // OR D
    //
    // Takes the logical OR of
    // the contents of register D
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["DE"]->getHighValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 | val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_OR_E(void)
{
    // opCode 0xB3
    // OR E
    //
    // Takes the logical OR of
    // the contents of register E
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["DE"]->getLowValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 | val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_OR_H(void)
{
    // opCode 0xB4
    // OR H
    //
    // Takes the logical OR of
    // the contents of register H
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["HL"]->getHighValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 | val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_OR_L(void)
{
    // opCode 0xB5
    // OR L
    //
    // Takes the logical OR of
    // the contents of register L
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["HL"]->getLowValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 | val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_OR_HL(void)
{
    // opCode 0xB6
    // OR (HL)
    //
    // Takes the logical OR of
    // the contents of the memory address
    // that register HL points to
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 8 Cycles, 1 byte

    uint8_t val1, val2, res;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    val1 = mainMemory.readAddress(addr);
    val2 = registers["AF"]->getHighValue();

    res  = val1 | val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C'); 

    return 8;
}

int cpu::op_OR_A(void)
{
    // opCode 0xB7
    // OR A
    //
    // Takes the logical OR of
    // the contents of register A
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 4 Cycles, 1 byte

    uint8_t val1, val2, res;

    val1 = registers["AF"]->getHighValue();
    val2 = registers["AF"]->getHighValue();

    res  = val1 | val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C'); 

    return 4;
}

int cpu::op_CP_B(void)
{
    // opCode 0xB8
    // CP B
    //
    // Compares the contents of register B
    // with the contents of register A
    // Note: Same as SUB B
    // instruction but results are not saved
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte
    
    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["BC"]->getHighValue();
    flags = compare8Bit(srcVal,"AF",1);

    if( flags % 2 == 0 )        resetFlag('H');
    else                        setFlag('H');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('C');
    else                        setFlag('C');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('Z');
    else                        setFlag('Z');

    setFlag('N');

    return 4;
}

int cpu::op_CP_C(void)
{
    // opCode 0xB9
    // CP C
    //
    // Compares the contents of register C
    // with the contents of register A
    // Note: Same as SUB C
    // instruction but results are not saved
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte
    
    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["BC"]->getLowValue();
    flags = compare8Bit(srcVal,"AF",1);

    if( flags % 2 == 0 )        resetFlag('H');
    else                        setFlag('H');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('C');
    else                        setFlag('C');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('Z');
    else                        setFlag('Z');

    setFlag('N');

    return 4;
}

int cpu::op_CP_D(void)
{
    // opCode 0xBA
    // CP D
    //
    // Compares the contents of register D
    // with the contents of register A
    // Note: Same as SUB D
    // instruction but results are not saved
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte
    
    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["DE"]->getHighValue();
    flags = compare8Bit(srcVal,"AF",1);

    if( flags % 2 == 0 )        resetFlag('H');
    else                        setFlag('H');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('C');
    else                        setFlag('C');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('Z');
    else                        setFlag('Z');

    setFlag('N');

    return 4;
}

int cpu::op_CP_E(void)
{
    // opCode 0xBB
    // CP E
    //
    // Compares the contents of register E
    // with the contents of register A
    // Note: Same as SUB E
    // instruction but results are not saved
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte
    
    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["DE"]->getLowValue();
    flags = compare8Bit(srcVal,"AF",1);

    if( flags % 2 == 0 )        resetFlag('H');
    else                        setFlag('H');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('C');
    else                        setFlag('C');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('Z');
    else                        setFlag('Z');

    setFlag('N');

    return 4;
}

int cpu::op_CP_H(void)
{
    // opCode 0xBC
    // CP H
    //
    // Compares the contents of register H
    // with the contents of register A
    // Note: Same as SUB H
    // instruction but results are not saved
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte
    
    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["HL"]->getHighValue();
    flags = compare8Bit(srcVal,"AF",1);

    if( flags % 2 == 0 )        resetFlag('H');
    else                        setFlag('H');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('C');
    else                        setFlag('C');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('Z');
    else                        setFlag('Z');

    setFlag('N');

    return 4;
}

int cpu::op_CP_L(void)
{
    // opCode 0xBD
    // CP L
    //
    // Compares the contents of register L
    // with the contents of register A
    // Note: Same as SUB L
    // instruction but results are not saved
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte
    
    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["HL"]->getLowValue();
    flags = compare8Bit(srcVal,"AF",1);

    if( flags % 2 == 0 )        resetFlag('H');
    else                        setFlag('H');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('C');
    else                        setFlag('C');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('Z');
    else                        setFlag('Z');

    setFlag('N');

    return 4;
}

int cpu::op_CP_HL(void)
{
    // opCode 0xBE
    // CP (HL)
    //
    // Compares the contents of the memory
    // address that register HL points to
    // with the contents of register A
    // Note: Same as SUB (HL)
    // instruction but results are not saved
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte
    
    uint8_t flags;
    uint8_t srcVal;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    srcVal = mainMemory.readAddress(addr);
    flags = compare8Bit(srcVal,"AF",1);

    if( flags % 2 == 0 )        resetFlag('H');
    else                        setFlag('H');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('C');
    else                        setFlag('C');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('Z');
    else                        setFlag('Z');

    setFlag('N');

    return 8;
}

int cpu::op_CP_A(void)
{
    // opCode 0xBF
    // CP A
    //
    // Compares the contents of register L
    // with the contents of register A
    // Note: Same as SUB A
    // instruction but results are not saved
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 4 Cycles, 1 byte
    
    uint8_t flags;
    uint8_t srcVal;

    srcVal = registers["AF"]->getHighValue();
    flags = compare8Bit(srcVal,"AF",1);

    if( flags % 2 == 0 )        resetFlag('H');
    else                        setFlag('H');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('C');
    else                        setFlag('C');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('Z');
    else                        setFlag('Z');

    setFlag('N');

    return 4;
}

int cpu::op_RET_NZ(void)
{
    // opCode 0xC0
    // RET NZ
    // 
    // If flag Z is reset,
    // Pops 2 bytes from the memory stack
    // and into the PC
    // Increments SP by 2
    // 20 Cycles if jump, 8 Cycles if no jump, 1 byte

    if( getFlag('Z') == 0 )
    {
        popToRegister("PC");
        return 20;
    }

    return 8;
}

int cpu::op_POP_BC(void)
{
    // opCode 0xC1
    // POP BC
    //
    // Pops contents from the memory stack
    // into register BC
    // Also increments SP by 2
    // 12 Cycles, 1 byte

    popToRegister("BC");
    return 12;
}

int cpu::op_JP_NZnn(void)
{
    // opCode 0xC2
    // JP NZ, nn
    //
    // If Z flag is reset
    // Jumps to immediate memory address
    // 16 Cycles if Jump, 12 if not Jump, 3 bytes

    uint8_t low, high;

    if( getFlag('Z') == 0 )
    {
        low = getNextByte();
        high = getNextByte();

        registers["PC"]->setLowValue(low);
        registers["PC"]->setHighValue(low);

        return 16;
    }

    registers["PC"]->incrementRegister();
    registers["PC"]->incrementRegister();

    return 12;
}

int cpu::op_JP_nn(void)
{
    // opCode 0xC3
    // JP nn
    //
    // Jumps to immediate memory address
    // 16 Cycles, 3 bytes

    uint8_t low, high;

    low = getNextByte();
    high = getNextByte();

    registers["PC"]->setLowValue(low);
    registers["PC"]->setHighValue(low);

    return 16;
}

int cpu::op_CALL_NZnn(void)
{
    // opCode 0xC4
    // CALL NZ, nn
    //
    // If flag Z is reset,
    // Pushes the PC value corresponding to the instruction
    // after CALL to the memory stack
    // then jumps to nn
    // Decrements Stack Pointer by 2
    // 24 Cycles if jump, 12 Cycles if no jump, 3 bytes

    uint8_t high, low;

    if( getFlag('Z') == 0 )
    {
        low = getNextByte();
        high = getNextByte();

        pushByteToStack(registers["PC"]->getHighValue());
        pushByteToStack(registers["PC"]->getLowValue());

        registers["PC"]->setHighValue(high);
        registers["PC"]->setLowValue(low);
        
        return 24;
    }

    registers["PC"]->incrementRegister();
    registers["PC"]->incrementRegister();

    return 12;
}

int cpu::op_PUSH_BC(void)
{
    // opCode 0xC5
    // PUSH BC
    //
    // Pushes contents of BC
    // into the memory stack
    // Decrements SP by 2
    // 16 Cycles, 1 byte

    uint8_t high, low;

    high = registers["BC"]->getHighValue();
    low = registers["BC"]->getLowValue();

    pushByteToStack(high);
    pushByteToStack(low);

    return 16;
}

int cpu::op_ADD_An(void)
{
    // opCode 0xC6
    // ADD A, n
    //
    // Adds next byte in memory
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 8 Cycles, 2 byteS

    uint8_t flags;
    uint8_t srcVal;

    srcVal = getNextByte();
    flags  = add8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');
    return 8;
}

int cpu::op_RST_00H(void)
{
    // opCode 0xC7
    // RST 00H
    //
    // Pushes current value of the PC
    // into the memory stack
    // then jumps to memory address  0x0000
    // 16 Cycles, 1 byte
    
    pushByteToStack(registers["PC"]->getHighValue());
    pushByteToStack(registers["PC"]->getLowValue());

    registers["PC"]->setTotalValue(0x0000);

    return 16;
}

int cpu::op_RET_Z(void)
{
    // opCode 0xC8
    // RET Z
    // 
    // If flag Z is set,
    // Pops 2 bytes from the memory stack
    // and into the PC
    // Increments SP by 2
    // 20 Cycles if jump, 8 Cycles if no jump, 1 byte

    if( getFlag('Z') == 1 )
    {
        popToRegister("PC");
        return 20;
    }

    return 8;
}

int cpu::op_RET(void)
{
    // opCode 0xC9
    // RET
    // Pops 2 bytes from the memory stack
    // and into the PC
    // Increments SP by 2
    // 16 Cycles, 1 byte

    popToRegister("PC");
    return 16;
}

int cpu::op_JP_Znn(void)
{
    // opCode 0xCA
    // JP NZ, nn
    //
    // If Z flag is set
    // Jumps to immediate memory address
    // 16 Cycles if Jump, 12 if not Jump, 3 bytes

    uint8_t low, high;

    if( getFlag('Z') == 1 )
    {
        low = getNextByte();
        high = getNextByte();

        registers["PC"]->setLowValue(low);
        registers["PC"]->setHighValue(low);

        return 16;
    }

    registers["PC"]->incrementRegister();
    registers["PC"]->incrementRegister();

    return 12;
}

int cpu::op_PREFIX_CB(void)
{
    // opCode 0xCB
    // 
    // First byte of 2-byte opCodes
    // Reads next byte(s) in memory
    // and calls the respective instruction
    // from CB table
    // Will probably do nothing
    // and the cpu loop will be handling it

    return 0;
}

int cpu::op_CALL_Znn(void)
{
    // opCode 0xCC
    // CALL Z, nn
    //
    // If flag Z is set,
    // Pushes the PC value corresponding to the instruction
    // after CALL to the memory stack
    // Decrements Stack Pointer by 2
    // 24 Cycles if jump, 12 Cycles if no jump, 3 bytes

    uint8_t high, low;

    if( getFlag('Z') == 1 )
    {
        low = getNextByte();
        high = getNextByte();

        pushByteToStack(registers["PC"]->getHighValue());
        pushByteToStack(registers["PC"]->getLowValue());

        registers["PC"]->setHighValue(high);
        registers["PC"]->setLowValue(low);
        
        return 24;
    }

    registers["PC"]->incrementRegister();
    registers["PC"]->incrementRegister();

    return 12;
}

int cpu::op_CALL_nn(void)
{
    // opCode 0xCD
    // CALL nn
    //
    // Pushes the PC value corresponding to the instruction
    // after CALL to the memory stack
    // Decrements Stack Pointer by 2
    // 24 Cycles, 3 bytes

    uint8_t high, low;

    low = getNextByte();
    high = getNextByte();

    pushByteToStack(registers["PC"]->getHighValue());
    pushByteToStack(registers["PC"]->getLowValue());

    registers["PC"]->setHighValue(high);
    registers["PC"]->setLowValue(low);
    
    return 24;
}

int cpu::op_ADC_An(void)
{
    // opCode 0xCE
    // ADC A, n
    //
    // Adds next value in memory
    // plus the Carry Flag
    // into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Set H if bit 3 overflows; Otherwise Resets H
    //      - Set C if bit 7 overflows; Otherwise Resets C
    // 8 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = getNextByte();
    flags = add8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 8;
}

int cpu::op_RST_08H(void)
{
    // opCode 0xCF
    // RST 08H
    //
    // Pushes current value of the PC
    // into the memory stack
    // then jumps to memory address  0x0008
    // 16 Cycles, 1 byte
    
    pushByteToStack(registers["PC"]->getHighValue());
    pushByteToStack(registers["PC"]->getLowValue());

    registers["PC"]->setTotalValue(0x0008);

    return 16;
}

int cpu::op_RET_NC(void)
{
    // opCode 0xD0
    // RET NC
    // 
    // If flag C is reset,
    // Pops 2 bytes from the memory stack
    // and into the PC
    // Increments SP by 2
    // 20 Cycles if jump, 8 Cycles if no jump, 1 byte

    if( getFlag('C') == 0 )
    {
        popToRegister("PC");
        return 20;
    }

    return 8;
}

int cpu::op_POP_DE(void)
{
    // opCode 0xD1
    // POP DE
    //
    // Pops contents from the memory stack
    // into register DE
    // Also increments SP by 2
    // 12 Cycles, 1 byte

    popToRegister("DE");
    return 12;
}

int cpu::op_JP_NCnn(void)
{
    // opCode 0xD2
    // JP NC, nn
    //
    // If C flag is reset
    // Jumps to immediate memory address
    // 16 Cycles if Jump, 12 if not Jump, 3 bytes

    uint8_t low, high;

    if( getFlag('C') == 0 )
    {
        low = getNextByte();
        high = getNextByte();

        registers["PC"]->setLowValue(low);
        registers["PC"]->setHighValue(low);

        return 16;
    }

    registers["PC"]->incrementRegister();
    registers["PC"]->incrementRegister();

    return 12;
}

// opCode 0xD3 Unused

int cpu::op_CALL_NCnn(void)
{
    // opCode 0xD4
    // CALL NC, nn
    //
    // If flag C is reset,
    // Pushes the PC value corresponding to the instruction
    // after CALL to the memory stack
    // then jumps to nn
    // Decrements Stack Pointer by 2
    // 24 Cycles if jump, 12 Cycles if no jump, 3 bytes

    uint8_t high, low;

    if( getFlag('C') == 0 )
    {
        low = getNextByte();
        high = getNextByte();

        pushByteToStack(registers["PC"]->getHighValue());
        pushByteToStack(registers["PC"]->getLowValue());

        registers["PC"]->setHighValue(high);
        registers["PC"]->setLowValue(low);
        
        return 24;
    }

    registers["PC"]->incrementRegister();
    registers["PC"]->incrementRegister();

    return 12;
}

int cpu::op_PUSH_DE(void)
{
    // opCode 0xD5
    // PUSH DE
    //
    // Pushes contents of DE
    // into the memory stack
    // Decrements SP by 2
    // 16 Cycles, 1 byte

    uint8_t high, low;

    high = registers["DE"]->getHighValue();
    low = registers["DE"]->getLowValue();

    pushByteToStack(high);
    pushByteToStack(low);

    return 16;
}

int cpu::op_SUB_n(void)
{
    // opCode 0xD6
    // SUB n
    //
    // Subtracts next byte in memory
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 8 Cycles, 2 byteS

    uint8_t flags;
    uint8_t srcVal;

    srcVal = getNextByte();
    flags  = subtract8Bit(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');
    return 8;
}

int cpu::op_RST_10H(void)
{
    // opCode 0xD7
    // RST 10H
    //
    // Pushes current value of the PC
    // into the memory stack
    // then jumps to memory address  0x0010
    // 16 Cycles, 1 byte
    
    pushByteToStack(registers["PC"]->getHighValue());
    pushByteToStack(registers["PC"]->getLowValue());

    registers["PC"]->setTotalValue(0x0010);

    return 16;
}

int cpu::op_RET_C(void)
{
    // opCode 0xD8
    // RET C
    // 
    // If flag C is set,
    // Pops 2 bytes from the memory stack
    // and into the PC
    // Increments SP by 2
    // 20 Cycles if jump, 8 Cycles if no jump, 1 byte

    if( getFlag('C') == 1 )
    {
        popToRegister("PC");
        return 20;
    }

    return 8;
}

int cpu::op_RETI(void)
{
    // opCode 0xD9
    // RETI
    // Pops 2 bytes from the memory stack
    // and into the PC
    // Increments SP by 2
    // Then, enable interrupts
    // 16 Cycles, 1 byte

    popToRegister("PC");

    // TODO: Enable interrupts

    return 16;
}

int cpu::op_JP_Cnn(void)
{
    // opCode 0xDA
    // JP NC, nn
    //
    // If C flag is set
    // Jumps to immediate memory address
    // 16 Cycles if Jump, 12 if not Jump, 3 bytes

    uint8_t low, high;

    if( getFlag('C') == 1 )
    {
        low = getNextByte();
        high = getNextByte();

        registers["PC"]->setLowValue(low);
        registers["PC"]->setHighValue(low);

        return 16;
    }

    registers["PC"]->incrementRegister();
    registers["PC"]->incrementRegister();

    return 12;
}

// opCode 0xDB Unused

int cpu::op_CALL_Cnn(void)
{
    // opCode 0xDC
    // CALL C, nn
    //
    // If flag C is set,
    // Pushes the PC value corresponding to the instruction
    // after CALL to the memory stack
    // Decrements Stack Pointer by 2
    // 24 Cycles if jump, 12 Cycles if no jump, 3 bytes

    uint8_t high, low;

    if( getFlag('C') == 1 )
    {
        low = getNextByte();
        high = getNextByte();

        pushByteToStack(registers["PC"]->getHighValue());
        pushByteToStack(registers["PC"]->getLowValue());

        registers["PC"]->setHighValue(high);
        registers["PC"]->setLowValue(low);
        
        return 24;
    }

    registers["PC"]->incrementRegister();
    registers["PC"]->incrementRegister();

    return 12;
}

// opCode 0xDD Unused


int cpu::op_SBC_An(void)
{
    // opCode 0xDE
    // SBC A, n
    //
    // Subtracts next value in memory
    // plus the Carry Flag
    // from register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 8 Cycles, 1 byte

    uint8_t flags;
    uint8_t srcVal;

    srcVal = getNextByte();
    flags = subtract8BitWithCarry(srcVal,"AF",1);

    switch (flags)
    {
        case 3:
            setFlag('H');
            setFlag('C');
            break;
        case 2:
            resetFlag('H');
            setFlag('C');
            break;
        case 1:
            setFlag('H');
            resetFlag('C');
            break;
        case 0:
            resetFlag('H');
            resetFlag('C');
    }

    resetFlag('N');

    if( registers["AF"]->getHighValue() == 0 )  setFlag('Z');
    else                                        resetFlag('Z');

    return 8;
}

int cpu::op_RST_18H(void)
{
    // opCode 0xDF
    // RST 18H
    //
    // Pushes current value of the PC
    // into the memory stack
    // then jumps to memory address  0x0018
    // 16 Cycles, 1 byte
    
    pushByteToStack(registers["PC"]->getHighValue());
    pushByteToStack(registers["PC"]->getLowValue());

    registers["PC"]->setTotalValue(0x0018);

    return 16;
}

int cpu::op_LDH_nA(void)
{
    // opCode 0xE0
    // LDH n, A
    //
    // Reads next byte n in memory
    // and puts the contents of 
    // register A into memory
    // address 0xFF00 + n
    // 12 Cycles, 2 Bytes

    uint8_t val, n;
    uint16_t addr;

    n = getNextByte();
    addr = 0xFF00 + n;

    val = registers["AF"]->getHighValue();

    mainMemory.writeToAddress(addr, val);

    return 12;
}

int cpu::op_POP_HL(void)
{
    // opCode 0xE1
    // POP HL
    //
    // Pops contents from the memory stack
    // into register HL
    // Also increments SP by 2
    // 12 Cycles, 1 byte

    popToRegister("HL");
    return 12;
}

int cpu::op_LD_CaddrA(void)
{
    // opCode 0xE2
    // LD (C), A
    //
    // Reads value n of register C
    // and puts the contents of 
    // register A into memory
    // address 0xFF00 + n
    // 8 Cycles, 2 Bytes

    uint8_t val, n;
    uint16_t addr;

    n = registers["BC"]->getLowValue();
    addr = 0xFF00 + n;

    val = registers["AF"]->getHighValue();

    mainMemory.writeToAddress(addr, val);

    return 8;
}

// opCode 0xE3 Unused

// opCode 0xE4 Unused

int cpu::op_PUSH_HL(void)
{
    // opCode 0xE5
    // PUSH HL
    //
    // Pushes contents of HL
    // into the memory stack
    // Decrements SP by 2
    // 16 Cycles, 1 byte

    uint8_t high, low;

    high = registers["HL"]->getHighValue();
    low = registers["HL"]->getLowValue();

    pushByteToStack(high);
    pushByteToStack(low);

    return 16;  
}

int cpu::op_AND_n(void)
{
    // opCode 0xE6
    // AND n
    //
    // Takes the logical AND of
    // the contents of the next byte in memory
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Sets H
    //      - Resets C
    // 8 Cycles, 2 bytes

    uint8_t val1, val2, res;

    val1 = getNextByte();
    val2 = registers["AF"]->getHighValue();

    res  = val1 & val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    setFlag('H');
    resetFlag('C');

    return 8;
}

int cpu::op_RST_20H(void)
{
    // opCode 0xE7
    // RST 20H
    //
    // Pushes current value of the PC
    // into the memory stack
    // then jumps to memory address  0x0020
    // 16 Cycles, 1 byte
    
    pushByteToStack(registers["PC"]->getHighValue());
    pushByteToStack(registers["PC"]->getLowValue());

    registers["PC"]->setTotalValue(0x0020);

    return 16;
}

int cpu::op_ADD_SPn(void)
{
    // opCode 0xE8
    // ADD SP, n
    //
    // Adds next byte in memory
    // into SP
    // Note: Interprets the byte
    // as a signed value
    //
    // Flags:
    //      - Resets Z
    //      - Resets N
    //      - Sets H if bit 3 overflows; Otherwise Resets H
    //      - Sets C if bit 7 overflows; Otherwise Resets C
    // 16 Cycles, 2 bytes

    uint8_t val;
    uint16_t totalVal;

    val = getNextByte();
    totalVal = registers["SP"]->getTotalValue();

    if( (val & 0x80) != 0 ) totalVal -= ((val^0xFF) + 1);
    else                    totalVal += val;

    registers["SP"]->setTotalValue(totalVal);

    resetFlag('Z');
    resetFlag('N');

    // TODO: Set/Reset H,C Flags

    return 16;
}

int cpu::op_JP_HLaddr(void)
{
    // opCode 0xE9
    // JP (HL)
    //
    // Jumps memory address contained in register HL
    // 4 Cycles, 1 bytes

    uint8_t low, high;

    low = registers["HL"]->getLowValue();
    high = registers["HL"]->getHighValue();

    registers["PC"]->setLowValue(low);
    registers["PC"]->setHighValue(low);

    return 16;
}

int cpu::op_LD_nnA(void)
{
    // opCode 0xEA
    // LD (nn), A
    //
    // Put value in register A
    // into immediate memory address
    // 16 Cycles, 3 bytes

    uint8_t low, high, val;
    uint16_t addr;

    low = getNextByte();
    high = getNextByte();

    addr = high;
    addr = addr<<8;
    addr += low;

    val = registers["AF"]->getHighValue();

    mainMemory.writeToAddress(addr,val);

    return 16;
}

// opCode 0xEB Unused

// opCode 0xEC Unused

// opCode 0xED Unused

int cpu::op_XOR_n(void)
{
    // opCode 0xEE
    // XOR n
    //
    // Takes the logical XOR of
    // the contents of the next byte in memory
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 8 Cycles, 2 bytes

    uint8_t val1, val2, res;

    val1 = getNextByte();
    val2 = registers["AF"]->getHighValue();

    res  = val1 ^ val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C');

    return 8;
}

int cpu::op_RST_28H(void)
{
    // opCode 0xEF
    // RST 28H
    //
    // Pushes current value of the PC
    // into the memory stack
    // then jumps to memory address  0x0028
    // 16 Cycles, 1 byte
    
    pushByteToStack(registers["PC"]->getHighValue());
    pushByteToStack(registers["PC"]->getLowValue());

    registers["PC"]->setTotalValue(0x0028);

    return 16;
}

int cpu::op_LDH_An(void)
{
    // opCode 0xF0
    // LDH A, n
    //
    // Reads next byte n in memory
    // and puts the contents of memory
    // address 0xFF00 + n into register A
    // 12 Cycles, 2 Bytes

    uint8_t val, n;
    uint16_t addr;

    n = getNextByte();
    addr = 0xFF00 + n;

    val = mainMemory.readAddress(addr);

    registers["AF"]->setHighValue(val);

    return 12;
}

int cpu::op_POP_AF(void)
{
    // opCode 0xF1
    // POP AF
    //
    // Pops contents from the memory stack
    // into register AF
    // Also increments SP by 2
    // 12 Cycles, 1 byte

    popToRegister("AF");
    return 12;
}

int cpu::op_LD_ACaddr(void)
{
    // opCode 0xF2
    // LD A, (C)
    //
    // Reads value n of register C
    // and puts the contents of 
    // memory  address 0xFF00 + n
    // into register A
    // 8 Cycles, 2 Bytes

    uint8_t val, n;
    uint16_t addr;

    n = registers["BC"]->getLowValue();
    addr = 0xFF00 + n;

    val = mainMemory.readAddress(addr);

    registers["AF"]->setHighValue(val);

    return 8;
}

int cpu::op_DI(void)
{
    // opCode 0xF3
    // DI
    //
    // Disables interrups after
    // the next instruction is executed
    // 4 Cycles, 1 byte

    // TODO: Implement

    return 4;
}

// opCode 0xF4 Unused

int cpu::op_PUSH_AF(void)
{
    // opCode 0xF5
    // PUSH AF
    //
    // Pushes contents of AF
    // into the memory stack
    // Decrements SP by 2
    // 16 Cycles, 1 byte

    uint8_t high, low;

    high = registers["AF"]->getHighValue();
    low = registers["AF"]->getLowValue();

    pushByteToStack(high);
    pushByteToStack(low);

    return 16;  
}

int cpu::op_OR_n(void)
{
    // opCode 0xF6
    // OR n
    //
    // Takes the logical OR of
    // the contents of the next byte in memory
    // and register A and places
    // the result into register A
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Resets N
    //      - Resets H
    //      - Resets C
    // 8 Cycles, 2 bytes

    uint8_t val1, val2, res;

    val1 = getNextByte();
    val2 = registers["AF"]->getHighValue();

    res  = val1 | val2;

    registers["AF"]->setHighValue(res);

    if( res == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C');

    return 8;
}

int cpu::op_RST_30H(void)
{
    // opCode 0xF7
    // RST 30H
    //
    // Pushes current value of the PC
    // into the memory stack
    // then jumps to memory address  0x0030
    // 16 Cycles, 1 byte
    
    pushByteToStack(registers["PC"]->getHighValue());
    pushByteToStack(registers["PC"]->getLowValue());

    registers["PC"]->setTotalValue(0x0030);

    return 16;
}

int cpu::op_LD_HLSPn(void)
{
    // opCode 0xF8
    // LD HL SP+n
    //
    // Adds next byte in memory
    // and SP and loads the result into HL
    // Note: Interprets the byte
    // as a signed value
    //
    // Flags:
    //      - Resets Z
    //      - Resets N
    //      - Sets H if bit 3 overflows; Otherwise Resets H
    //      - Sets C if bit 7 overflows; Otherwise Resets C
    // 16 Cycles, 2 bytes

    uint8_t val;
    uint16_t totalVal;

    val = getNextByte();
    totalVal = registers["SP"]->getTotalValue();

    if( (val & 0x80) != 0 ) totalVal -= ((val^0xFF) + 1);
    else                    totalVal += val;

    registers["HL"]->setTotalValue(totalVal);

    resetFlag('Z');
    resetFlag('N');

    // TODO: Set/Reset H,C Flags

    return 16;
}

int cpu::op_LD_SPHL(void)
{
    // opCode 0xF9
    // LD SP, HL
    //
    // Loads HL into SP
    // 8 Cycles, 1 byte

    registers["SP"]->setTotalValue(registers["HL"]->getTotalValue());
    return 8;
}

int cpu::op_LD_Ann(void)
{
    // opCode 0xFA
    // LD A, (nn)
    //
    // Put value immediate memory 
    // address points to into register A
    // 16 Cycles, 3 bytes

    uint8_t low, high, val;
    uint16_t addr;

    low = getNextByte();
    high = getNextByte();

    addr = high;
    addr = addr<<8;
    addr += low;

    val = mainMemory.readAddress(addr);
    registers["AF"]->setHighValue(val);

    return 16;
}

int cpu::op_EI(void)
{
    // opCode 0xFB
    // EI
    //
    // Enables interrups after
    // the next instruction is executed
    // 4 Cycles, 1 byte

    // TODO: Implement

    return 4;
}

// opCode 0xFC Unused

// opCode 0xFD Unused

int cpu::op_CP_n(void)
{
    // opCode 0xFE
    // CP n
    //
    // Compares the contents of the
    // next byte in memory with
    // the contents of register A
    // Note: Same as SUB n
    // instruction but results are not saved
    // Flags:
    //      - Sets Z if result is 0; Otherwise Resets Z
    //      - Sets N
    //      - Sets H if there is a borrow from bit 4; Otherwise Resets H
    //      - Sets C if there is a borrow; Otherwise Resets C
    // 8 Cycles, 2 bytes
    
    uint8_t flags;
    uint8_t srcVal;

    srcVal = getNextByte();
    flags = compare8Bit(srcVal,"AF",1);

    if( flags % 2 == 0 )        resetFlag('H');
    else                        setFlag('H');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('C');
    else                        setFlag('C');

    flags = flags>>1;
    if( flags % 2 == 0 )        resetFlag('Z');
    else                        setFlag('Z');

    setFlag('N');

    return 8;
}

int cpu::op_RST_38H(void)
{
    // opCode 0xFF
    // RST 38H
    //
    // Pushes current value of the PC
    // into the memory stack
    // then jumps to memory address  0x0038
    // 16 Cycles, 1 byte
    
    pushByteToStack(registers["PC"]->getHighValue());
    pushByteToStack(registers["PC"]->getLowValue());

    registers["PC"]->setTotalValue(0x0038);

    return 16;
}