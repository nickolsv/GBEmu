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
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

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
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

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
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

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
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

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
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

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
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

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
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

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

    return 16;
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
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

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
    // 8 Cycles, 2 bytes

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
    // 8 Cycles, 2 bytes

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
    // 8 Cycles, 2 bytes

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
    // 8 Cycles, 2 bytes

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
    // 8 Cycles, 2 bytes

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
    // 8 Cycles, 2 bytes

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
    // 8 Cycles, 2 bytes

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

    return 16;
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
    // 8 Cycles, 2 bytes

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

int cpu::op_RL_B(void)
{
    // opCode 0xCB 0x10
    // RL B
    //
    // Rotates register B left
    // by 1 bit. Previous C flag
    // value written to new bit 0
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t bit7, val, flag;

    bit7 = registers["BC"]->rotateHighLeft();
    val  = registers["BC"]->getHighValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0xFE;
    else                val = val | 0x01;

    registers["BC"]->setHighValue(val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 8;    
}

int cpu::op_RL_C(void)
{
    // opCode 0xCB 0x11
    // RL C
    //
    // Rotates register C left
    // by 1 bit. Previous C flag
    // value written to new bit 0
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t bit7, val, flag;

    bit7 = registers["BC"]->rotateLowLeft();
    val  = registers["BC"]->getLowValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0xFE;
    else                val = val | 0x01;

    registers["BC"]->setLowValue(val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 8;    
}

int cpu::op_RL_D(void)
{
    // opCode 0xCB 0x12
    // RL D
    //
    // Rotates register D left
    // by 1 bit. Previous C flag
    // value written to new bit 0
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t bit7, val, flag;

    bit7 = registers["DE"]->rotateHighLeft();
    val  = registers["DE"]->getHighValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0xFE;
    else                val = val | 0x01;

    registers["DE"]->setHighValue(val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 8;    
}

int cpu::op_RL_E(void)
{
    // opCode 0xCB 0x13
    // RL E
    //
    // Rotates register E left
    // by 1 bit. Previous C flag
    // value written to new bit 0
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t bit7, val, flag;

    bit7 = registers["DE"]->rotateLowLeft();
    val  = registers["DE"]->getLowValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0xFE;
    else                val = val | 0x01;

    registers["DE"]->setLowValue(val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 8;    
}

int cpu::op_RL_H(void)
{
    // opCode 0xCB 0x14
    // RL H
    //
    // Rotates register H left
    // by 1 bit. Previous C flag
    // value written to new bit 0
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t bit7, val, flag;

    bit7 = registers["HL"]->rotateHighLeft();
    val  = registers["HL"]->getHighValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0xFE;
    else                val = val | 0x01;

    registers["HL"]->setHighValue(val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 8;    
}

int cpu::op_RL_L(void)
{
    // opCode 0xCB 0x15
    // RL L
    //
    // Rotates register L left
    // by 1 bit. Previous C flag
    // value written to new bit 0
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t bit7, val, flag;

    bit7 = registers["HL"]->rotateLowLeft();
    val  = registers["HL"]->getLowValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0xFE;
    else                val = val | 0x01;

    registers["HL"]->setLowValue(val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 8;    
}

int cpu::op_RL_HLaddr(void)
{
    // opCode 0xCB 0x16
    // RL (HL)
    //
    // Rotates at memory address register HL points
    // to left by 1 bit. Previous C flag
    // value written to new bit 0
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t bit7, val, flag;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    bit7 = val & 0x80;
    bit7 = bit7>>7;

    val = val<<1;
    val = val | bit7;

    flag = getFlag('C');

    if( flag == 0 )     val = val & 0xFE;
    else                val = val | 0x01;

    mainMemory.writeToAddress(addr, val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 16;    
}

int cpu::op_RL_A(void)
{
    // opCode 0xCB 0x17
    // RL A
    //
    // Rotates register A left
    // by 1 bit. Previous C flag
    // value written to new bit 0
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t bit7, val, flag;

    bit7 = registers["AF"]->rotateHighLeft();
    val  = registers["AF"]->getHighValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0xFE;
    else                val = val | 0x01;

    registers["AF"]->setHighValue(val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 8;    
}

int cpu::op_RR_B(void)
{
    // opCode 0xCB 0x18
    // RR B
    //
    // Rotates register B right
    // by 1 bit. Previous C flag
    // value written to new bit 7
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 bytes

    uint8_t bit7, val, flag;

    bit7 = registers["BC"]->rotateHighRight();
    val  = registers["BC"]->getHighValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0x7F;
    else                val = val | 0X80;

    registers["BC"]->setHighValue(val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 8;    
}

int cpu::op_RR_C(void)
{
    // opCode 0xCB 0x19
    // RR C
    //
    // Rotates register C right
    // by 1 bit. Previous C flag
    // value written to new bit 7
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 bytes

    uint8_t bit7, val, flag;

    bit7 = registers["BC"]->rotateLowRight();
    val  = registers["BC"]->getLowValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0x7F;
    else                val = val | 0X80;

    registers["BC"]->setLowValue(val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 8;    
}

int cpu::op_RR_D(void)
{
    // opCode 0xCB 0x1A
    // RR D
    //
    // Rotates register D right
    // by 1 bit. Previous C flag
    // value written to new bit 7
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 bytes

    uint8_t bit7, val, flag;

    bit7 = registers["DE"]->rotateHighRight();
    val  = registers["DE"]->getHighValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0x7F;
    else                val = val | 0X80;

    registers["DE"]->setHighValue(val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 8;    
}

int cpu::op_RR_E(void)
{
    // opCode 0xCB 0x1B
    // RR E
    //
    // Rotates register E right
    // by 1 bit. Previous C flag
    // value written to new bit 7
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 bytes

    uint8_t bit7, val, flag;

    bit7 = registers["DE"]->rotateLowRight();
    val  = registers["DE"]->getLowValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0x7F;
    else                val = val | 0X80;

    registers["DE"]->setLowValue(val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 8;    
}

int cpu::op_RR_H(void)
{
    // opCode 0xCB 0x1C
    // RR H
    //
    // Rotates register H right
    // by 1 bit. Previous C flag
    // value written to new bit 7
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 bytes

    uint8_t bit7, val, flag;

    bit7 = registers["HL"]->rotateHighRight();
    val  = registers["HL"]->getHighValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0x7F;
    else                val = val | 0X80;

    registers["HL"]->setHighValue(val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 8;    
}

int cpu::op_RR_L(void)
{
    // opCode 0xCB 0x1D
    // RR L
    //
    // Rotates register L right
    // by 1 bit. Previous C flag
    // value written to new bit 7
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 bytes

    uint8_t bit7, val, flag;

    bit7 = registers["HL"]->rotateLowRight();
    val  = registers["HL"]->getLowValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0x7F;
    else                val = val | 0X80;

    registers["HL"]->setLowValue(val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 8;    
}

int cpu::op_RR_HLaddr(void)
{
    // opCode 0xCB 0x1E
    // RR (HL)
    //
    // Rotates at memory address register HL points
    // to right by 1 bit. Previous C flag
    // value written to new bit 7
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 bytes

    uint8_t bit0, val, flag;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    bit0 = val & 0x01;
    bit0 = bit0<<7;

    val = val>>1;
    val = val | bit0;

    flag = getFlag('C');

    if( flag == 0 )     val = val & 0x7F;
    else                val = val | 0X80;

    mainMemory.writeToAddress(addr, val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit0 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 16;    
}

int cpu::op_RR_A(void)
{
    // opCode 0xCB 0x1F
    // RR A
    //
    // Shifts register A right
    // by 1 bit. Previous C flag
    // value written to new bit 7
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 0 data
    // 8 Cycles, 2 bytes

    uint8_t bit7, val, flag;

    bit7 = registers["AF"]->rotateHighRight();
    val  = registers["AF"]->getHighValue();
    flag = getFlag('C');

    if( flag == 0 )     val = val & 0x7F;
    else                val = val | 0X80;

    registers["AF"]->setHighValue(val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( bit7 == 0 )     resetFlag('C');
    else                setFlag('C');

    return 8;    
}

int cpu::op_SLA_B(void)
{
    // opCode 0xCB 0x20
    // SLA B
    //
    // Shifts register B left
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["BC"]->shiftHighLeft();
    val = registers["BC"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SLA_C(void)
{
    // opCode 0xCB 0x21
    // SLA C
    //
    // Shifts register C left
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["BC"]->shiftLowLeft();
    val = registers["BC"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SLA_D(void)
{
    // opCode 0xCB 0x22
    // SLA D
    //
    // Shifts register D left
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["DE"]->shiftHighLeft();
    val = registers["DE"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SLA_E(void)
{
    // opCode 0xCB 0x23
    // SLA E
    //
    // Shifts register E left
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["DE"]->shiftLowLeft();
    val = registers["DE"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SLA_H(void)
{
    // opCode 0xCB 0x24
    // SLA H
    //
    // Shifts register H left
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["HL"]->shiftHighLeft();
    val = registers["HL"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SLA_L(void)
{
    // opCode 0xCB 0x25
    // SLA L
    //
    // Shifts register L left
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["HL"]->shiftLowLeft();
    val = registers["HL"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SLA_HLaddr(void)
{
    // opCode 0xCB 0x26
    // SLA (HL)
    //
    // Shifts the value at memory address
    // register HL points to left by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val, temp;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);
    
    carry = val & 0x80;

    val = val<<1;
    val = val & 0xFE;

    mainMemory.writeToAddress(addr, val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 16;
}

int cpu::op_SLA_A(void)
{
    // opCode 0xCB 0x27
    // SLA A
    //
    // Shifts register A left
    // by 1 bit
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["AF"]->shiftHighLeft();
    val = registers["AF"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SRA_B(void)
{
    // opCode 0xCB 0x28
    // SRA B
    //
    // Shifts register B right
    // by 1 bit
    // Contents of bit 7 are unchanged
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["BC"]->shiftHighRight(0);
    val = registers["BC"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SRA_C(void)
{
    // opCode 0xCB 0x29
    // SRA C
    //
    // Shifts register C right
    // by 1 bit
    // Contents of bit 7 are unchanged
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["BC"]->shiftLowRight(0);
    val = registers["BC"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SRA_D(void)
{
    // opCode 0xCB 0x2A
    // SRA D
    //
    // Shifts register D right
    // by 1 bit
    // Contents of bit 7 are unchanged
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["DE"]->shiftHighRight(0);
    val = registers["DE"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SRA_E(void)
{
    // opCode 0xCB 0x2B
    // SRA E
    //
    // Shifts register E right
    // by 1 bit
    // Contents of bit 7 are unchanged
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["DE"]->shiftLowRight(0);
    val = registers["DE"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SRA_H(void)
{
    // opCode 0xCB 0x2C
    // SRA H
    //
    // Shifts register H right
    // by 1 bit
    // Contents of bit 7 are unchanged
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["HL"]->shiftHighRight(0);
    val = registers["HL"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SRA_L(void)
{
    // opCode 0xCB 0x2D
    // SRA L
    //
    // Shifts register L right
    // by 1 bit
    // Contents of bit 7 are unchanged
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["HL"]->shiftLowRight(0);
    val = registers["HL"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SRA_HLaddr(void)
{
    // opCode 0xCB 0x2E
    // SRA (HL)
    //
    // Shifts the value at memory address
    // register HL points to right by 1 bit
    // Contents of bit 7 are unchanged
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val, bit7;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);
    
    carry = val & 0x01;
    bit7 = val & 0x80;

    val = val>>1;
    val = val & 0x7F;
    val = val | bit7;

    mainMemory.writeToAddress(addr, val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 16;
}

int cpu::op_SRA_A(void)
{
    // opCode 0xCB 0x2F
    // SRA A
    //
    // Shifts register A right
    // by 1 bit
    // Contents of bit 7 are unchanged
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["AF"]->shiftHighRight(0);
    val = registers["AF"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SWAP_B(void)
{
    // opCode 0xCB 0x30
    // SWAP B
    // Swaps the 4 lower bits of register B
    // with its 4 higher bits
    // Flags:
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - Reset C
    // 8 Cycles, 2 bytes

    uint8_t val;

    registers["BC"]->swapNibblesHigh();
    val = registers["BC"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C');

    return 8;
}

int cpu::op_SWAP_C(void)
{
    // opCode 0xCB 0x31
    // SWAP C
    // Swaps the 4 lower bits of register C
    // with its 4 higher bits
    // Flags:
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - Reset C
    // 8 Cycles, 2 bytes

    uint8_t val;

    registers["BC"]->swapNibblesLow();
    val = registers["BC"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C');

    return 8;
}

int cpu::op_SWAP_D(void)
{
    // opCode 0xCB 0x32
    // SWAP D
    // Swaps the 4 lower bits of register D
    // with its 4 higher bits
    // Flags:
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - Reset C
    // 8 Cycles, 2 bytes

    uint8_t val;

    registers["DE"]->swapNibblesHigh();
    val = registers["DE"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C');

    return 8;
}

int cpu::op_SWAP_E(void)
{
    // opCode 0xCB 0x33
    // SWAP E
    // Swaps the 4 lower bits of register E
    // with its 4 higher bits
    // Flags:
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - Reset C
    // 8 Cycles, 2 bytes

    uint8_t val;

    registers["DE"]->swapNibblesLow();
    val = registers["DE"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C');

    return 8;
}

int cpu::op_SWAP_H(void)
{
    // opCode 0xCB 0x34
    // SWAP H
    // Swaps the 4 lower bits of register H
    // with its 4 higher bits
    // Flags:
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - Reset C
    // 8 Cycles, 2 bytes

    uint8_t val;

    registers["HL"]->swapNibblesHigh();
    val = registers["HL"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C');

    return 8;
}

int cpu::op_SWAP_L(void)
{
    // opCode 0xCB 0x35
    // SWAP L
    // Swaps the 4 lower bits of register L
    // with its 4 higher bits
    // Flags:
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - Reset C
    // 8 Cycles, 2 bytes

    uint8_t val;

    registers["HL"]->swapNibblesLow();
    val = registers["HL"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C');

    return 8;
}

int cpu::op_SWAP_HLaddr(void)
{
    // opCode 0xCB 0x36
    // SWAP (HL)
    // Swaps the 4 lower bits of value at address
    // register HL points to with its 4 higher bits
    // Flags:
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - Reset C
    // 8 Cycles, 2 bytes

    uint8_t val,temp;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = val & 0x0F;
    val = val>>4;
    temp = temp<<4;

    val = ( ( val & 0x0F) & (temp & 0xF0) );

    mainMemory.writeToAddress(addr,val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C');

    return 8;
}

int cpu::op_SWAP_A(void)
{
    // opCode 0xCB 0x37
    // SWAP A
    // Swaps the 4 lower bits of register A
    // with its 4 higher bits
    // Flags:
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - Reset C
    // 8 Cycles, 2 bytes

    uint8_t val;

    registers["AF"]->swapNibblesHigh();
    val = registers["AF"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');
    resetFlag('C');

    return 8;
}

int cpu::op_SRL_B(void)
{
    // opCode 0xCB 0x38
    // SRL B
    //
    // Shifts register B right
    // by 1 bit
    // Contents of bit 7 are reset
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["BC"]->shiftHighRight(1);
    val = registers["BC"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SRL_C(void)
{
    // opCode 0xCB 0x39
    // SRL C
    //
    // Shifts register C right
    // by 1 bit
    // Contents of bit 7 are reset
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["BC"]->shiftLowRight(1);
    val = registers["BC"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SRL_D(void)
{
    // opCode 0xCB 0x3A
    // SRL D
    //
    // Shifts register D right
    // by 1 bit
    // Contents of bit 7 are reset
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["DE"]->shiftHighRight(1);
    val = registers["DE"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SRL_E(void)
{
    // opCode 0xCB 0x3B
    // SRL E
    //
    // Shifts register E right
    // by 1 bit
    // Contents of bit 7 are reset
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["DE"]->shiftLowRight(1);
    val = registers["DE"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SRL_H(void)
{
    // opCode 0xCB 0x3C
    // SRL H
    //
    // Shifts register H right
    // by 1 bit
    // Contents of bit 7 are reset
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["HL"]->shiftHighRight(1);
    val = registers["HL"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SRL_L(void)
{
    // opCode 0xCB 0x3D
    // SRL L
    //
    // Shifts register L right
    // by 1 bit
    // Contents of bit 7 are reset
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["HL"]->shiftLowRight(1);
    val = registers["HL"]->getLowValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_SRL_HLaddr(void)
{
    // opCode 0xCB 0x3E
    // SRL (HL)
    //
    // Shifts the value at memory address
    // register HL points to right by 1 bit
    // Contents of bit 7 are reset
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val, bit7;
    uint16_t addr;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);
    
    carry = val & 0x01;

    val = val>>1;
    val = val & 0x7F;

    mainMemory.writeToAddress(addr, val);

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 16;
}

int cpu::op_SRL_A(void)
{
    // opCode 0xCB 0x3F
    // SRL A
    //
    // Shifts register A right
    // by 1 bit
    // Contents of bit 7 are reset
    // Flags: 
    //      - Sets Z if results is Zero; Otherwise Resets
    //      - Reset N
    //      - Reset H
    //      - C Contains old bit 7 data
    // 8 Cycles, 2 bytes

    uint8_t carry, val;

    carry = registers["AF"]->shiftHighRight(1);
    val = registers["AF"]->getHighValue();

    if( val == 0 )      setFlag('Z');
    else                resetFlag('Z');

    resetFlag('N');
    resetFlag('H');

    if( carry == 0 )    resetFlag('C');
    else                setFlag('C');

    return 8;
}

int cpu::op_BIT_0B(void)
{
    // opCode 0xCB 0x40
    // BIT 0, B
    //
    // Copies complement of bit 0
    // of register B
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitHigh(0);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_0C(void)
{
    // opCode 0xCB 0x41
    // BIT 0, C
    //
    // Copies complement of bit 0
    // of register C
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitLow(0);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_0D(void)
{
    // opCode 0xCB 0x42
    // BIT 0, D
    //
    // Copies complement of bit 0
    // of register D
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitHigh(0);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_0E(void)
{
    // opCode 0xCB 0x43
    // BIT 0, E
    //
    // Copies complement of bit 0
    // of register E
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitLow(0);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_0H(void)
{
    // opCode 0xCB 0x44
    // BIT 0, H
    //
    // Copies complement of bit 0
    // of register H
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitHigh(0);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_0L(void)
{
    // opCode 0xCB 0x45
    // BIT 0, L
    //
    // Copies complement of bit 0
    // of register L
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitLow(0);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_0HLaddr(void)
{
    // opCode 0xCB 0x46
    // BIT 0, (Hl)
    //
    // Copies complement of bit 0
    // of value in memory location
    // register HL points to 
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t bit;

    addr = registers["HL"]->getTotalValue();
    bit = mainMemory.readAddress(addr);

    bit = bit & 0x01;

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 16;
}

int cpu::op_BIT_0A(void)
{
    // opCode 0xCB 0x47
    // BIT 0, A
    //
    // Copies complement of bit 0
    // of register A
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["AF"]->getnthBitHigh(0);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_1B(void)
{
    // opCode 0xCB 0x48
    // BIT 1, B
    //
    // Copies complement of bit 1
    // of register B
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitHigh(1);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_1C(void)
{
    // opCode 0xCB 0x49
    // BIT 1, C
    //
    // Copies complement of bit 1
    // of register C
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitLow(1);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_1D(void)
{
    // opCode 0xCB 0x4A
    // BIT 1, D
    //
    // Copies complement of bit 1
    // of register D
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitHigh(1);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_1E(void)
{
    // opCode 0xCB 0x4B
    // BIT 1, E
    //
    // Copies complement of bit 1
    // of register E
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitLow(1);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_1H(void)
{
    // opCode 0xCB 0x4C
    // BIT 1, H
    //
    // Copies complement of bit 1
    // of register H
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitHigh(1);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_1L(void)
{
    // opCode 0xCB 0x4D
    // BIT 1, L
    //
    // Copies complement of bit 1
    // of register L
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitLow(1);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_1HLaddr(void)
{
    // opCode 0xCB 0x4E
    // BIT 1, (Hl)
    //
    // Copies complement of bit 1
    // of value in memory location
    // register HL points to 
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t bit;

    addr = registers["HL"]->getTotalValue();
    bit = mainMemory.readAddress(addr);

    bit = bit>>1;
    bit = bit & 0x01;

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 16;
}

int cpu::op_BIT_1A(void)
{
    // opCode 0xCB 0x4F
    // BIT 1, A
    //
    // Copies complement of bit 1
    // of register A
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["AF"]->getnthBitHigh(1);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_2B(void)
{
    // opCode 0xCB 0x50
    // BIT 2, B
    //
    // Copies complement of bit 2
    // of register B
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitHigh(2);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_2C(void)
{
    // opCode 0xCB 0x51
    // BIT 2, C
    //
    // Copies complement of bit 2
    // of register C
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitLow(2);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_2D(void)
{
    // opCode 0xCB 0x52
    // BIT 2, D
    //
    // Copies complement of bit 2
    // of register D
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitHigh(2);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_2E(void)
{
    // opCode 0xCB 0x53
    // BIT 2, E
    //
    // Copies complement of bit 2
    // of register E
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitLow(2);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_2H(void)
{
    // opCode 0xCB 0x54
    // BIT 2, H
    //
    // Copies complement of bit 2
    // of register H
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitHigh(2);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_2L(void)
{
    // opCode 0xCB 0x55
    // BIT 2, L
    //
    // Copies complement of bit 2
    // of register L
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitLow(2);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_2HLaddr(void)
{
    // opCode 0xCB 0x56
    // BIT 2, (Hl)
    //
    // Copies complement of bit 2
    // of value in memory location
    // register HL points to 
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t bit;

    addr = registers["HL"]->getTotalValue();
    bit = mainMemory.readAddress(addr);

    bit = bit>>2;
    bit = bit & 0x01;

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 16;
}

int cpu::op_BIT_2A(void)
{
    // opCode 0xCB 0x57
    // BIT 2, A
    //
    // Copies complement of bit 2
    // of register A
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["AF"]->getnthBitHigh(2);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_3B(void)
{
    // opCode 0xCB 0x58
    // BIT 3, B
    //
    // Copies complement of bit 3
    // of register B
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitHigh(3);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_3C(void)
{
    // opCode 0xCB 0x59
    // BIT 3, C
    //
    // Copies complement of bit 3
    // of register C
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitLow(3);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_3D(void)
{
    // opCode 0xCB 0x5A
    // BIT 3, D
    //
    // Copies complement of bit 3
    // of register D
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitHigh(3);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_3E(void)
{
    // opCode 0xCB 0x5B
    // BIT 3, E
    //
    // Copies complement of bit 3
    // of register E
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitLow(3);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_3H(void)
{
    // opCode 0xCB 0x5C
    // BIT 3, H
    //
    // Copies complement of bit 3
    // of register H
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitHigh(3);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_3L(void)
{
    // opCode 0xCB 0x5D
    // BIT 3, L
    //
    // Copies complement of bit 3
    // of register L
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitLow(3);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_3HLaddr(void)
{
    // opCode 0xCB 0x5E
    // BIT 3, (Hl)
    //
    // Copies complement of bit 3
    // of value in memory location
    // register HL points to 
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t bit;

    addr = registers["HL"]->getTotalValue();
    bit = mainMemory.readAddress(addr);

    bit = bit>>3;
    bit = bit & 0x01;

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 16;
}

int cpu::op_BIT_3A(void)
{
    // opCode 0xCB 0x5F
    // BIT 3, A
    //
    // Copies complement of bit 3
    // of register A
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["AF"]->getnthBitHigh(3);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}