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

    uint16_t addr;
    uint8_t val;

    addr = registers["PC"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    registers["BC"]->setLowValue(val);
    registers["PC"]->incrementRegister();

    addr = registers["PC"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    registers["BC"]->setHighValue(val);
    registers["PC"]->incrementRegister();

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

    if( val == 0 )          setFlag('Z');
    else if( val % 8 == 0 ) setFlag('H');

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

    if( val == 0 )          setFlag('Z');
    else if( val % 8 == 7 ) setFlag('H');

    setFlag('N');

    return 4;
}

int cpu::op_LD_Bn(void)
{
    // opCode 0x06
    // Loads next byte of memory
    // into B register
    // 8 Cycles, 2 bytes

    uint16_t addr;
    uint8_t val;

    addr = registers["PC"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    registers["BC"]->setHighValue(val);
    registers["PC"]->incrementRegister();
    
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

    // TODO: Implement

    return 20;
}

int cpu::op_ADD_HLBC(void)
{
    // opCode 0x09
    // Add BC to HL
    // Possibly Sets Flags: N,H,C
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

    // TODO: Implement

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

    // TODO: Implement

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