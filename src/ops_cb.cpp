#include "../header/cpu.hh"

int cpu::op_RLC_B(void)
{
    // opCode 0xCB 0x00
    // RLC B
    //
    // Rotates register B left
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val;

    carry = registers["BC"]->rotateHighLeft();
    val = registers["BC"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_RLC_C(void)
{
    // opCode 0xCB 0x01
    // RLC C
    //
    // Rotates register C left
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val;

    carry = registers["BC"]->rotateLowLeft();
    val = registers["BC"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_RLC_D(void)
{
    // opCode 0xCB 0x02
    // RLC D
    //
    // Rotates register D left
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val;

    carry = registers["DE"]->rotateHighLeft();
    val = registers["DE"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_RLC_E(void)
{
    // opCode 0xCB 0x03
    // RLC E
    //
    // Rotates register E left
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val;

    carry = registers["DE"]->rotateLowLeft();
    val = registers["DE"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_RLC_H(void)
{
    // opCode 0xCB 0x04
    // RLC H
    //
    // Rotates register H left
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val;

    carry = registers["HL"]->rotateHighLeft();
    val = registers["HL"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_RLC_L(void)
{
    // opCode 0xCB 0x05
    // RLC L
    //
    // Rotates register L left
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val;

    carry = registers["HL"]->rotateLowLeft();
    val = registers["HL"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_RLC_HLaddr(void)
{
    // opCode 0xCB 0x06
    // RLC (HL)
    //
    // Rotates the value at memory address
    // register HL points to left by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val, temp;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);
    
    carry = val & 0x80;
    carry = carry>>7;

    val = val<<1;
    val = val | carry;

    mainMemory.writeToAddress(addr, val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_RLC_A(void)
{
    // opCode 0xCB 0x07
    // RLC A
    //
    // Rotates register A left
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val;

    carry = registers["AF"]->rotateHighLeft();
    val = registers["AF"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_RRC_B(void)
{
    // opCode 0xCB 0x08
    // RRC B
    //
    // Rotates register B right
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val;

    carry = registers["BC"]->rotateHighRight();
    val = registers["BC"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_RRC_C(void)
{
    // opCode 0xCB 0x09
    // RRC C
    //
    // Rotates register C right
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val;

    carry = registers["BC"]->rotateLowRight();
    val = registers["BC"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_RRC_D(void)
{
    // opCode 0xCB 0x0A
    // RRC D
    //
    // Rotates register D right
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val;

    carry = registers["DE"]->rotateHighRight();
    val = registers["DE"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_RRC_E(void)
{
    // opCode 0xCB 0x0B
    // RRC E
    //
    // Rotates register E right
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val;

    carry = registers["DE"]->rotateLowRight();
    val = registers["DE"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_RRC_H(void)
{
    // opCode 0xCB 0x0C
    // RRC H
    //
    // Rotates register H right
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val;

    carry = registers["HL"]->rotateHighRight();
    val = registers["HL"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_RRC_L(void)
{
    // opCode 0xCB 0x0D
    // RRC L
    //
    // Rotates register L right
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val;

    carry = registers["HL"]->rotateLowRight();
    val = registers["HL"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_RRC_HLaddr(void)
{
    // opCode 0xCB 0x0E
    // RRC (HL)
    //
    // Rotates the value at memory address
    // register HL points to right by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val, temp;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);
    
    carry = val & 0x01;
    carry = carry<<7;

    val = val>>1;
    val = val | carry;

    mainMemory.writeToAddress(addr, val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_RRC_A(void)
{
    // opCode 0xCB 0x0F
    // RRC A
    //
    // Rotates register A right
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 byte

    uint8_t carry, val;

    carry = registers["AF"]->rotateHighRight();
    val = registers["AF"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}