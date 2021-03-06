#include "../header/cpu.hh"

int cpu::op_NOOP(void)
{
    // opCode 0x00
    // Does Nothing
    // 4 Cycles, 1 byte

    return 4;
}

int cpu::op_LD_BCnn(void)
{
    // opCode 0x01
    // Loads next 2 bytes of memory
    // into BC register
    // 12 Cycles, 3 bytes

    uint16_t addr;
    uint8_t val;

    addr = registers["PC"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    registers["BC"]->setLowValue(val);
    registers["BC"]->incrementRegister();

    addr = registers["PC"]->getTotalValue();
    val = mainMemory.readAddress(addr);

    registers["BC"]->setHighValue(val);
    registers["BC"]->incrementRegister();

    return 12;
}

int cpu::op_LD_BCA(void)
{
    // opCode 0x02
    // Loads value in register A into
    // byte pointed to by register BC
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
    // Increments value in register BC by 1
    // 8 Cycles, 1 byte

    registers["BC"]->incrementRegister();

    return 8;
}

int cpu::op_INC_B(void)
{
    // opCode 0x04
    // Increments value in register B by 1
    // Possibly Sets Flags: Z,N,H
    // 4 Cycles, 1 byte

    // TODO: Implement

    return 4;
}

int cpu::op_DEC_B(void)
{
    // opCode 0x05
    // Decrements value in register B by 1
    // Possibly Sets Flags: Z,N,H
    // 4 Cycles, 1 byte

    // TODO: Implement

    return 4;
}

int cpu::op_LD_Bn(void)
{
    // opCode 0x06
    // Loads next byte of memory
    // into B register
    // 8 Cycles, 2 bytes

    // TODO: Implement

    return 8;
}

int cpu::op_RLC_A(void)
{
    // opCode 0x07
    // Rotate register A left
    // by 1 bit
    // Possibly Sets Flags: Z,N,H,C
    // 4 Cycles, 1 byte

    // TODO: Implement

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
    // Loads BC into A
    // 8 Cycles, 1 byte

    // TODO: Implement

    return 8;
}

int cpu::op_DEC_BC(void)
{
    // opCode 0x0B
    // Decrements value in register BC by 1
    // 8 Cycles, 1 byte

    // TODO: Implement

    return 8;
}

int cpu::op_INC_C(void)
{
    // opCode 0x0C
    // Increments value in register C by 1
    // Possibly Sets Flags: Z,N,H
    // 4 Cycles, 1 byte

    // TODO: Implement

    return 4;
}

int cpu::op_DEC_C(void)
{
    // opCode 0x0D
    // Decrements value in register C by 1
    // Possibly Sets Flags: Z,N,H
    // 4 Cycles, 1 byte

    // TODO: Implement

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
    // Possibly Sets Flags: Z,N,H,C
    // 4 Cycles, 1 byte

    // TODO: Implement

    return 4;
}