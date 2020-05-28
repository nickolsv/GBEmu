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
    // BIT 0, (HL)
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
    // BIT 1, (HL)
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
    // BIT 2, (HL)
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
    // BIT 3, (HL)
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

int cpu::op_BIT_4B(void)
{
    // opCode 0xCB 0x60
    // BIT 4, B
    //
    // Copies complement of bit 4
    // of register B
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitHigh(4);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_4C(void)
{
    // opCode 0xCB 0x61
    // BIT 4, C
    //
    // Copies complement of bit 4
    // of register C
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitLow(4);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_4D(void)
{
    // opCode 0xCB 0x62
    // BIT 4, D
    //
    // Copies complement of bit 4
    // of register D
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitHigh(4);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_4E(void)
{
    // opCode 0xCB 0x63
    // BIT 4, E
    //
    // Copies complement of bit 4
    // of register E
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitLow(4);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_4H(void)
{
    // opCode 0xCB 0x64
    // BIT 4, H
    //
    // Copies complement of bit 4
    // of register H
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitHigh(4);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_4L(void)
{
    // opCode 0xCB 0x65
    // BIT 4, L
    //
    // Copies complement of bit 4
    // of register L
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitLow(4);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_4HLaddr(void)
{
    // opCode 0xCB 0x66
    // BIT 4, (HL)
    //
    // Copies complement of bit 4
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

    bit = bit>>4;
    bit = bit & 0x01;

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 16;
}

int cpu::op_BIT_4A(void)
{
    // opCode 0xCB 0x67
    // BIT 4, A
    //
    // Copies complement of bit 4
    // of register A
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["AF"]->getnthBitHigh(4);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_5B(void)
{
    // opCode 0xCB 0x68
    // BIT 5, B
    //
    // Copies complement of bit 5
    // of register B
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitHigh(5);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_5C(void)
{
    // opCode 0xCB 0x69
    // BIT 5, C
    //
    // Copies complement of bit 5
    // of register C
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitLow(5);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_5D(void)
{
    // opCode 0xCB 0x6A
    // BIT 5, D
    //
    // Copies complement of bit 5
    // of register D
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitHigh(5);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_5E(void)
{
    // opCode 0xCB 0x6B
    // BIT 5, E
    //
    // Copies complement of bit 5
    // of register E
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitLow(5);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_5H(void)
{
    // opCode 0xCB 0x6C
    // BIT 5, H
    //
    // Copies complement of bit 5
    // of register H
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitHigh(5);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_5L(void)
{
    // opCode 0xCB 0x6D
    // BIT 5, L
    //
    // Copies complement of bit 5
    // of register L
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitLow(5);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_5HLaddr(void)
{
    // opCode 0xCB 0x6E
    // BIT 5, (HL)
    //
    // Copies complement of bit 5
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

    bit = bit>>5;
    bit = bit & 0x01;

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 16;
}

int cpu::op_BIT_5A(void)
{
    // opCode 0xCB 0x6F
    // BIT 5, A
    //
    // Copies complement of bit 5
    // of register A
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["AF"]->getnthBitHigh(5);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_6B(void)
{
    // opCode 0xCB 0x70
    // BIT 6, B
    //
    // Copies complement of bit 6
    // of register B
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitHigh(6);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_6C(void)
{
    // opCode 0xCB 0x71
    // BIT 6, C
    //
    // Copies complement of bit 6
    // of register C
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitLow(6);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_6D(void)
{
    // opCode 0xCB 0x72
    // BIT 6, D
    //
    // Copies complement of bit 6
    // of register D
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitHigh(6);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_6E(void)
{
    // opCode 0xCB 0x73
    // BIT 6, E
    //
    // Copies complement of bit 6
    // of register E
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitLow(6);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_6H(void)
{
    // opCode 0xCB 0x74
    // BIT 6, H
    //
    // Copies complement of bit 6
    // of register H
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitHigh(6);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_6L(void)
{
    // opCode 0xCB 0x75
    // BIT 6, L
    //
    // Copies complement of bit 6
    // of register L
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitLow(6);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_6HLaddr(void)
{
    // opCode 0xCB 0x76
    // BIT 6, (HL)
    //
    // Copies complement of bit 6
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

    bit = bit>>6;
    bit = bit & 0x01;

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 16;
}

int cpu::op_BIT_6A(void)
{
    // opCode 0xCB 0x77
    // BIT 6, A
    //
    // Copies complement of bit 6
    // of register A
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["AF"]->getnthBitHigh(6);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_7B(void)
{
    // opCode 0xCB 0x78
    // BIT 7, B
    //
    // Copies complement of bit 7
    // of register B
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitHigh(7);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_7C(void)
{
    // opCode 0xCB 0x79
    // BIT 7, C
    //
    // Copies complement of bit 7
    // of register C
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["BC"]->getnthBitLow(7);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_7D(void)
{
    // opCode 0xCB 0x7A
    // BIT 7, D
    //
    // Copies complement of bit 7
    // of register D
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitHigh(7);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_7E(void)
{
    // opCode 0xCB 0x7B
    // BIT 7, E
    //
    // Copies complement of bit 7
    // of register E
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["DE"]->getnthBitLow(7);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_7H(void)
{
    // opCode 0xCB 0x7C
    // BIT 7, H
    //
    // Copies complement of bit 7
    // of register H
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitHigh(7);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_7L(void)
{
    // opCode 0xCB 0x7D
    // BIT 7, L
    //
    // Copies complement of bit 7
    // of register L
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["HL"]->getnthBitLow(7);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_BIT_7HLaddr(void)
{
    // opCode 0xCB 0x7E
    // BIT 7, (HL)
    //
    // Copies complement of bit 7
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

    bit = bit>>7;
    bit = bit & 0x01;

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 16;
}

int cpu::op_BIT_7A(void)
{
    // opCode 0xCB 0x7F
    // BIT 7, A
    //
    // Copies complement of bit 7
    // of register A
    // to flag Z
    // Flags:
    //      - Sets Z if 0; otherwise Reset
    //      - Resets N
    //      - Sets H
    // 8 Cycles, 2 bytes

    uint8_t bit = registers["AF"]->getnthBitHigh(7);

    if( bit == 0 )      setFlag('C');
    else                resetFlag('C');

    resetFlag('N');
    setFlag('H');

    return 8;
}

int cpu::op_RES_0B(void)
{
    // opCode 0xCB 0x80
    // RES 0, B
    //
    // Resets bit 0
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitHigh(0);

    return 8;
}

int cpu::op_RES_0C(void)
{
    // opCode 0xCB 0x81
    // RES 0, C
    //
    // Resets bit 0
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitLow(0);

    return 8;
}

int cpu::op_RES_0D(void)
{
    // opCode 0xCB 0x82
    // RES 0, D
    //
    // Resets bit 0
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitHigh(0);

    return 8;
}

int cpu::op_RES_0E(void)
{
    // opCode 0xCB 0x83
    // RES 0, E
    //
    // Resets bit 0
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitLow(0);

    return 8;
}

int cpu::op_RES_0H(void)
{
    // opCode 0xCB 0x84
    // RES 0, H
    //
    // Resets bit 0
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitHigh(0);

    return 8;
}

int cpu::op_RES_0L(void)
{
    // opCode 0xCB 0x85
    // RES 0, L
    //
    // Resets bit 0
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitLow(0);

    return 8;
}

int cpu::op_RES_0HLaddr(void)
{
    // opCode 0xCB 0x86
    // RES 0, (HL)
    //
    // Resets bit 0
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    temp = temp^0xFF;
    val = val & temp;

    mainMemory.writeToAddress(addr,val);


    return 16;
}

int cpu::op_RES_0A(void)
{
    // opCode 0xCB 0x87
    // RES 0, A
    //
    // Resets bit 0
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->resetnthBitHigh(0);

    return 8;
}

int cpu::op_RES_1B(void)
{
    // opCode 0xCB 0x88
    // RES 1, B
    //
    // Resets bit 1
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitHigh(1);

    return 8;
}

int cpu::op_RES_1C(void)
{
    // opCode 0xCB 0x89
    // RES 1, C
    //
    // Resets bit 1
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitLow(1);

    return 8;
}

int cpu::op_RES_1D(void)
{
    // opCode 0xCB 0x8A
    // RES 1, D
    //
    // Resets bit 1
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitHigh(1);

    return 8;
}

int cpu::op_RES_1E(void)
{
    // opCode 0xCB 0x8B
    // RES 1, E
    //
    // Resets bit 1
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitLow(1);

    return 8;
}

int cpu::op_RES_1H(void)
{
    // opCode 0xCB 0x8C
    // RES 1, H
    //
    // Resets bit 1
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitHigh(1);

    return 8;
}

int cpu::op_RES_1L(void)
{
    // opCode 0xCB 0x8D
    // RES 1, L
    //
    // Resets bit 1
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitLow(1);

    return 8;
}

int cpu::op_RES_1HLaddr(void)
{
    // opCode 0xCB 0x8E
    // RES 1, (HL)
    //
    // Resets bit 1
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    temp = temp<<1;
    temp = temp^0xFF;
    val = val & temp;

    mainMemory.writeToAddress(addr,val);

    return 16;
}

int cpu::op_RES_1A(void)
{
    // opCode 0xCB 0x8F
    // RES 1, A
    //
    // Resets bit 1
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->resetnthBitHigh(1);

    return 8;
}

int cpu::op_RES_2B(void)
{
    // opCode 0xCB 0x90
    // RES 2, B
    //
    // Resets bit 2
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitHigh(2);

    return 8;
}

int cpu::op_RES_2C(void)
{
    // opCode 0xCB 0x91
    // RES 2, C
    //
    // Resets bit 2
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitLow(2);

    return 8;
}

int cpu::op_RES_2D(void)
{
    // opCode 0xCB 0x92
    // RES 2, D
    //
    // Resets bit 2
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitHigh(2);

    return 8;
}

int cpu::op_RES_2E(void)
{
    // opCode 0xCB 0x93
    // RES 2, E
    //
    // Resets bit 2
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitLow(2);

    return 8;
}

int cpu::op_RES_2H(void)
{
    // opCode 0xCB 0x94
    // RES 2, H
    //
    // Resets bit 2
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitHigh(2);

    return 8;
}

int cpu::op_RES_2L(void)
{
    // opCode 0xCB 0x95
    // RES 2, L
    //
    // Resets bit 2
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitLow(2);

    return 8;
}

int cpu::op_RES_2HLaddr(void)
{
    // opCode 0xCB 0x96
    // RES 2, (HL)
    //
    // Resets bit 2
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    temp = temp<<2;
    temp = temp^0xFF;
    val = val & temp;

    mainMemory.writeToAddress(addr,val);

    return 16;
}

int cpu::op_RES_2A(void)
{
    // opCode 0xCB 0x97
    // RES 2, A
    //
    // Resets bit 2
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->resetnthBitHigh(2);

    return 8;
}

int cpu::op_RES_3B(void)
{
    // opCode 0xCB 0x98
    // RES 3, B
    //
    // Resets bit 3
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitHigh(3);

    return 8;
}

int cpu::op_RES_3C(void)
{
    // opCode 0xCB 0x99
    // RES 3, C
    //
    // Resets bit 3
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitLow(3);

    return 8;
}

int cpu::op_RES_3D(void)
{
    // opCode 0xCB 0x9A
    // RES 3, D
    //
    // Resets bit 3
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitHigh(3);

    return 8;
}

int cpu::op_RES_3E(void)
{
    // opCode 0xCB 0x9B
    // RES 3, E
    //
    // Resets bit 3
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitLow(3);

    return 8;
}

int cpu::op_RES_3H(void)
{
    // opCode 0xCB 0x9C
    // RES 3, H
    //
    // Resets bit 3
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitHigh(3);

    return 8;
}

int cpu::op_RES_3L(void)
{
    // opCode 0xCB 0x9D
    // RES 3, L
    //
    // Resets bit 3
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitLow(3);

    return 8;
}

int cpu::op_RES_3HLaddr(void)
{
    // opCode 0xCB 0x9E
    // RES 3, (HL)
    //
    // Resets bit 3
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    temp = temp<<3;
    temp = temp^0xFF;
    val = val & temp;

    mainMemory.writeToAddress(addr,val);

    return 16;
}

int cpu::op_RES_3A(void)
{
    // opCode 0xCB 0x9F
    // RES 3, A
    //
    // Resets bit 3
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->resetnthBitHigh(3);

    return 8;
}

int cpu::op_RES_4B(void)
{
    // opCode 0xCB 0xA0
    // RES 4, B
    //
    // Resets bit 4
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitHigh(4);

    return 8;
}

int cpu::op_RES_4C(void)
{
    // opCode 0xCB 0xA1
    // RES 4, C
    //
    // Resets bit 4
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitLow(4);

    return 8;
}

int cpu::op_RES_4D(void)
{
    // opCode 0xCB 0xA2
    // RES 4, D
    //
    // Resets bit 4
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitHigh(4);

    return 8;
}

int cpu::op_RES_4E(void)
{
    // opCode 0xCB 0xA3
    // RES 4, E
    //
    // Resets bit 4
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitLow(4);

    return 8;
}

int cpu::op_RES_4H(void)
{
    // opCode 0xCB 0xA4
    // RES 4, H
    //
    // Resets bit 4
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitHigh(4);

    return 8;
}

int cpu::op_RES_4L(void)
{
    // opCode 0xCB 0xA5
    // RES 4, L
    //
    // Resets bit 4
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitLow(4);

    return 8;
}

int cpu::op_RES_4HLaddr(void)
{
    // opCode 0xCB 0xA6
    // RES 4, (HL)
    //
    // Resets bit 4
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    temp = temp<<4;
    temp = temp^0xFF;
    val = val & temp;

    mainMemory.writeToAddress(addr,val);

    return 16;
}

int cpu::op_RES_4A(void)
{
    // opCode 0xCB 0xA7
    // RES 4, A
    //
    // Resets bit 4
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->resetnthBitHigh(4);

    return 8;
}

int cpu::op_RES_5B(void)
{
    // opCode 0xCB 0xA8
    // RES 5, B
    //
    // Resets bit 5
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitHigh(5);

    return 8;
}

int cpu::op_RES_5C(void)
{
    // opCode 0xCB 0xA9
    // RES 5, C
    //
    // Resets bit 5
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitLow(5);

    return 8;
}

int cpu::op_RES_5D(void)
{
    // opCode 0xCB 0xAA
    // RES 5, D
    //
    // Resets bit 5
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitHigh(5);

    return 8;
}

int cpu::op_RES_5E(void)
{
    // opCode 0xCB 0xAB
    // RES 5, E
    //
    // Resets bit 5
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitLow(5);

    return 8;
}

int cpu::op_RES_5H(void)
{
    // opCode 0xCB 0xAC
    // RES 5, H
    //
    // Resets bit 5
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitHigh(5);

    return 8;
}

int cpu::op_RES_5L(void)
{
    // opCode 0xCB 0xAD
    // RES 5, L
    //
    // Resets bit 5
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitLow(5);

    return 8;
}

int cpu::op_RES_5HLaddr(void)
{
    // opCode 0xCB 0xAE
    // RES 5, (HL)
    //
    // Resets bit 5
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    temp = temp<<5;
    temp = temp^0xFF;
    val = val & temp;

    mainMemory.writeToAddress(addr,val);

    return 16;
}

int cpu::op_RES_5A(void)
{
    // opCode 0xCB 0xAF
    // RES 5, A
    //
    // Resets bit 5
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->resetnthBitHigh(5);

    return 8;
}

int cpu::op_RES_6B(void)
{
    // opCode 0xCB 0XB0
    // RES 6, B
    //
    // Resets bit 6
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitHigh(6);

    return 8;
}

int cpu::op_RES_6C(void)
{
    // opCode 0xCB 0XB1
    // RES 6, C
    //
    // Resets bit 6
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitLow(6);

    return 8;
}

int cpu::op_RES_6D(void)
{
    // opCode 0xCB 0XB2
    // RES 6, D
    //
    // Resets bit 6
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitHigh(6);

    return 8;
}

int cpu::op_RES_6E(void)
{
    // opCode 0xCB 0XB3
    // RES 6, E
    //
    // Resets bit 6
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitLow(6);

    return 8;
}

int cpu::op_RES_6H(void)
{
    // opCode 0xCB 0XB4
    // RES 6, H
    //
    // Resets bit 6
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitHigh(6);

    return 8;
}

int cpu::op_RES_6L(void)
{
    // opCode 0xCB 0XB5
    // RES 6, L
    //
    // Resets bit 6
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitLow(6);

    return 8;
}

int cpu::op_RES_6HLaddr(void)
{
    // opCode 0xCB 0XB6
    // RES 6, (HL)
    //
    // Resets bit 6
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    temp = temp<<6;
    temp = temp^0xFF;
    val = val & temp;

    mainMemory.writeToAddress(addr,val);

    return 16;
}

int cpu::op_RES_6A(void)
{
    // opCode 0xCB 0XB7
    // RES 6, A
    //
    // Resets bit 6
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->resetnthBitHigh(6);

    return 8;
}

int cpu::op_RES_7B(void)
{
    // opCode 0xCB 0XB8
    // RES 7, B
    //
    // Resets bit 7
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitHigh(7);

    return 8;
}

int cpu::op_RES_7C(void)
{
    // opCode 0xCB 0XB9
    // RES 7, C
    //
    // Resets bit 7
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->resetnthBitLow(7);

    return 8;
}

int cpu::op_RES_7D(void)
{
    // opCode 0xCB 0XBA
    // RES 7, D
    //
    // Resets bit 7
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitHigh(7);

    return 8;
}

int cpu::op_RES_7E(void)
{
    // opCode 0xCB 0XBB
    // RES 7, E
    //
    // Resets bit 7
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->resetnthBitLow(7);

    return 8;
}

int cpu::op_RES_7H(void)
{
    // opCode 0xCB 0XBC
    // RES 7, H
    //
    // Resets bit 7
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitHigh(7);

    return 8;
}

int cpu::op_RES_7L(void)
{
    // opCode 0xCB 0XBD
    // RES 7, L
    //
    // Resets bit 7
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->resetnthBitLow(7);

    return 8;
}

int cpu::op_RES_7HLaddr(void)
{
    // opCode 0xCB 0XBE
    // RES 7, (HL)
    //
    // Resets bit 7
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    temp = temp<<7;
    temp = temp^0xFF;
    val = val & temp;

    mainMemory.writeToAddress(addr,val);

    return 16;
}

int cpu::op_RES_7A(void)
{
    // opCode 0xCB 0XBF
    // RES 7, A
    //
    // Resets bit 7
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->resetnthBitHigh(7);

    return 8;
}

int cpu::op_SET_0B(void)
{
    // opCode 0xCB 0xC0
    // SET 0, B
    //
    // Sets bit 0
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitHigh(0);

    return 8;
}

int cpu::op_SET_0C(void)
{
    // opCode 0xCB 0xC1
    // SET 0, C
    //
    // Sets bit 0
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitLow(0);

    return 8;
}

int cpu::op_SET_0D(void)
{
    // opCode 0xCB 0xC2
    // SET 0, D
    //
    // Sets bit 0
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitHigh(0);

    return 8;
}

int cpu::op_SET_0E(void)
{
    // opCode 0xCB 0xC3
    // SET 0, E
    //
    // Sets bit 0
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitLow(0);

    return 8;
}

int cpu::op_SET_0H(void)
{
    // opCode 0xCB 0xC4
    // SET 0, H
    //
    // Sets bit 0
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitHigh(0);

    return 8;
}

int cpu::op_SET_0L(void)
{
    // opCode 0xCB 0xC5
    // SET 0, L
    //
    // Sets bit 0
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitLow(0);

    return 8;
}

int cpu::op_SET_0HLaddr(void)
{
    // opCode 0xCB 0xC6
    // SET 0, (HL)
    //
    // Sets bit 0
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    val = val | temp;

    mainMemory.writeToAddress(addr,val);


    return 16;
}

int cpu::op_SET_0A(void)
{
    // opCode 0xCB 0xC7
    // SET 0, A
    //
    // Sets bit 0
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->setnthBitHigh(0);

    return 8;
}

int cpu::op_SET_1B(void)
{
    // opCode 0xCB 0xC8
    // SET 1, B
    //
    // Sets bit 1
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitHigh(1);

    return 8;
}

int cpu::op_SET_1C(void)
{
    // opCode 0xCB 0xC9
    // SET 1, C
    //
    // Sets bit 1
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitLow(1);

    return 8;
}

int cpu::op_SET_1D(void)
{
    // opCode 0xCB 0xCA
    // SET 1, D
    //
    // Sets bit 1
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitHigh(1);

    return 8;
}

int cpu::op_SET_1E(void)
{
    // opCode 0xCB 0xCB
    // SET 1, E
    //
    // Sets bit 1
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitLow(1);

    return 8;
}

int cpu::op_SET_1H(void)
{
    // opCode 0xCB 0xCC
    // SET 1, H
    //
    // Sets bit 1
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitHigh(1);

    return 8;
}

int cpu::op_SET_1L(void)
{
    // opCode 0xCB 0xCD
    // SET 1, L
    //
    // Sets bit 1
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitLow(1);

    return 8;
}

int cpu::op_SET_1HLaddr(void)
{
    // opCode 0xCB 0xCE
    // SET 1, (HL)
    //
    // Sets bit 1
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    temp = temp<<1;
    val = val | temp;

    mainMemory.writeToAddress(addr,val);

    return 16;
}

int cpu::op_SET_1A(void)
{
    // opCode 0xCB 0xCF
    // SET 1, A
    //
    // Sets bit 1
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->setnthBitHigh(1);

    return 8;
}

int cpu::op_SET_2B(void)
{
    // opCode 0xCB 0xD0
    // SET 2, B
    //
    // Sets bit 2
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitHigh(2);

    return 8;
}

int cpu::op_SET_2C(void)
{
    // opCode 0xCB 0xD1
    // SET 2, C
    //
    // Sets bit 2
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitLow(2);

    return 8;
}

int cpu::op_SET_2D(void)
{
    // opCode 0xCB 0xD2
    // SET 2, D
    //
    // Sets bit 2
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitHigh(2);

    return 8;
}

int cpu::op_SET_2E(void)
{
    // opCode 0xCB 0xD3
    // SET 2, E
    //
    // Sets bit 2
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitLow(2);

    return 8;
}

int cpu::op_SET_2H(void)
{
    // opCode 0xCB 0xD4
    // SET 2, H
    //
    // Sets bit 2
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitHigh(2);

    return 8;
}

int cpu::op_SET_2L(void)
{
    // opCode 0xCB 0xD5
    // SET 2, L
    //
    // Sets bit 2
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitLow(2);

    return 8;
}

int cpu::op_SET_2HLaddr(void)
{
    // opCode 0xCB 0xD6
    // SET 2, (HL)
    //
    // Sets bit 2
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    temp = temp<<2;
    val = val | temp;

    mainMemory.writeToAddress(addr,val);

    return 16;
}

int cpu::op_SET_2A(void)
{
    // opCode 0xCB 0xD7
    // SET 2, A
    //
    // Sets bit 2
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->setnthBitHigh(2);

    return 8;
}

int cpu::op_SET_3B(void)
{
    // opCode 0xCB 0xD8
    // SET 3, B
    //
    // Sets bit 3
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitHigh(3);

    return 8;
}

int cpu::op_SET_3C(void)
{
    // opCode 0xCB 0xD9
    // SET 3, C
    //
    // Sets bit 3
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitLow(3);

    return 8;
}

int cpu::op_SET_3D(void)
{
    // opCode 0xCB 0xDA
    // SET 3, D
    //
    // Sets bit 3
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitHigh(3);

    return 8;
}

int cpu::op_SET_3E(void)
{
    // opCode 0xCB 0xDB
    // SET 3, E
    //
    // Sets bit 3
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitLow(3);

    return 8;
}

int cpu::op_SET_3H(void)
{
    // opCode 0xCB 0xDC
    // SET 3, H
    //
    // Sets bit 3
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitHigh(3);

    return 8;
}

int cpu::op_SET_3L(void)
{
    // opCode 0xCB 0xDD
    // SET 3, L
    //
    // Sets bit 3
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitLow(3);

    return 8;
}

int cpu::op_SET_3HLaddr(void)
{
    // opCode 0xCB 0xDE
    // SET 3, (HL)
    //
    // Sets bit 3
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    temp = temp<<3;
    val = val | temp;

    mainMemory.writeToAddress(addr,val);

    return 16;
}

int cpu::op_SET_3A(void)
{
    // opCode 0xCB 0xDF
    // SET 3, A
    //
    // Sets bit 3
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->setnthBitHigh(3);

    return 8;
}

int cpu::op_SET_4B(void)
{
    // opCode 0xCB 0xE0
    // SET 4, B
    //
    // Sets bit 4
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitHigh(4);

    return 8;
}

int cpu::op_SET_4C(void)
{
    // opCode 0xCB 0xE1
    // SET 4, C
    //
    // Sets bit 4
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitLow(4);

    return 8;
}

int cpu::op_SET_4D(void)
{
    // opCode 0xCB 0xE2
    // SET 4, D
    //
    // Sets bit 4
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitHigh(4);

    return 8;
}

int cpu::op_SET_4E(void)
{
    // opCode 0xCB 0xE3
    // SET 4, E
    //
    // Sets bit 4
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitLow(4);

    return 8;
}

int cpu::op_SET_4H(void)
{
    // opCode 0xCB 0xE4
    // SET 4, H
    //
    // Sets bit 4
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitHigh(4);

    return 8;
}

int cpu::op_SET_4L(void)
{
    // opCode 0xCB 0xE5
    // SET 4, L
    //
    // Sets bit 4
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitLow(4);

    return 8;
}

int cpu::op_SET_4HLaddr(void)
{
    // opCode 0xCB 0xE6
    // SET 4, (HL)
    //
    // Sets bit 4
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    temp = temp<<4;
    val = val | temp;

    mainMemory.writeToAddress(addr,val);

    return 16;
}

int cpu::op_SET_4A(void)
{
    // opCode 0xCB 0xE7
    // SET 4, A
    //
    // Sets bit 4
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->setnthBitHigh(4);

    return 8;
}

int cpu::op_SET_5B(void)
{
    // opCode 0xCB 0xE8
    // SET 5, B
    //
    // Sets bit 5
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitHigh(5);

    return 8;
}

int cpu::op_SET_5C(void)
{
    // opCode 0xCB 0xE9
    // SET 5, C
    //
    // Sets bit 5
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitLow(5);

    return 8;
}

int cpu::op_SET_5D(void)
{
    // opCode 0xCB 0xEA
    // SET 5, D
    //
    // Sets bit 5
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitHigh(5);

    return 8;
}

int cpu::op_SET_5E(void)
{
    // opCode 0xCB 0xEB
    // SET 5, E
    //
    // Sets bit 5
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitLow(5);

    return 8;
}

int cpu::op_SET_5H(void)
{
    // opCode 0xCB 0xEC
    // SET 5, H
    //
    // Sets bit 5
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitHigh(5);

    return 8;
}

int cpu::op_SET_5L(void)
{
    // opCode 0xCB 0xED
    // SET 5, L
    //
    // Sets bit 5
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitLow(5);

    return 8;
}

int cpu::op_SET_5HLaddr(void)
{
    // opCode 0xCB 0xEE
    // SET 5, (HL)
    //
    // Sets bit 5
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    temp = temp<<5;
    val = val | temp;

    mainMemory.writeToAddress(addr,val);

    return 16;
}

int cpu::op_SET_5A(void)
{
    // opCode 0xCB 0xEF
    // SET 5, A
    //
    // Sets bit 5
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->setnthBitHigh(5);

    return 8;
}

int cpu::op_SET_6B(void)
{
    // opCode 0xCB 0xF0
    // SET 6, B
    //
    // Sets bit 6
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitHigh(6);

    return 8;
}

int cpu::op_SET_6C(void)
{
    // opCode 0xCB 0xF1
    // SET 6, C
    //
    // Sets bit 6
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitLow(6);

    return 8;
}

int cpu::op_SET_6D(void)
{
    // opCode 0xCB 0xF2
    // SET 6, D
    //
    // Sets bit 6
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitHigh(6);

    return 8;
}

int cpu::op_SET_6E(void)
{
    // opCode 0xCB 0xF3
    // SET 6, E
    //
    // Sets bit 6
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitLow(6);

    return 8;
}

int cpu::op_SET_6H(void)
{
    // opCode 0xCB 0xF4
    // SET 6, H
    //
    // Sets bit 6
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitHigh(6);

    return 8;
}

int cpu::op_SET_6L(void)
{
    // opCode 0xCB 0xF5
    // SET 6, L
    //
    // Sets bit 6
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitLow(6);

    return 8;
}

int cpu::op_SET_6HLaddr(void)
{
    // opCode 0xCB 0xF6
    // SET 6, (HL)
    //
    // Sets bit 6
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    temp = temp<<6;
    val = val | temp;

    mainMemory.writeToAddress(addr,val);

    return 16;
}

int cpu::op_SET_6A(void)
{
    // opCode 0xCB 0xF7
    // SET 6, A
    //
    // Sets bit 6
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->setnthBitHigh(6);

    return 8;
}

int cpu::op_SET_7B(void)
{
    // opCode 0xCB 0xF8
    // SET 7, B
    //
    // Sets bit 7
    // of register B
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitHigh(7);

    return 8;
}

int cpu::op_SET_7C(void)
{
    // opCode 0xCB 0xF9
    // SET 7, C
    //
    // Sets bit 7
    // of register C
    // 8 Cycles, 2 bytes

    registers["BC"]->setnthBitLow(7);

    return 8;
}

int cpu::op_SET_7D(void)
{
    // opCode 0xCB 0xFA
    // SET 7, D
    //
    // Sets bit 7
    // of register D
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitHigh(7);

    return 8;
}

int cpu::op_SET_7E(void)
{
    // opCode 0xCB 0xFB
    // SET 7, E
    //
    // Sets bit 7
    // of register E
    // 8 Cycles, 2 bytes

    registers["DE"]->setnthBitLow(7);

    return 8;
}

int cpu::op_SET_7H(void)
{
    // opCode 0xCB 0xFC
    // SET 7, H
    //
    // Sets bit 7
    // of register H
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitHigh(7);

    return 8;
}

int cpu::op_SET_7L(void)
{
    // opCode 0xCB 0xFD
    // SET 7, L
    //
    // Sets bit 7
    // of register L
    // 8 Cycles, 2 bytes

    registers["HL"]->setnthBitLow(7);

    return 8;
}

int cpu::op_SET_7HLaddr(void)
{
    // opCode 0xCB 0xFE
    // SET 7, (HL)
    //
    // Sets bit 7
    // of value in memory location
    // register HL points to 
    // 16 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val, temp;

    addr = registers["HL"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    temp = 0x01;
    temp = temp<<7;
    val = val | temp;

    mainMemory.writeToAddress(addr,val);

    return 16;
}

int cpu::op_SET_7A(void)
{
    // opCode 0xCB 0xFF
    // SET 7, A
    //
    // Sets bit 7
    // of register A
    // 8 Cycles, 2 bytes

    registers["AF"]->setnthBitHigh(7);

    return 8;
}