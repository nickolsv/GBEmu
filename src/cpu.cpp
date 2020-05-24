#include <iostream>
#include <unistd.h>
#include "../header/cpu.hh"
#include "../header/registers.hh"
cpu::cpu()
{
    for( int i = 0 ; i < 6 ; i++)
        registers.insert(std::make_pair(regnames[i],new register16()));
    frameCycles = 0;
    initializeInstructionTable();
}

cpu::~cpu()
{
    for( int i = 0; i < 6 ; i++)
        delete registers[regnames[i]];
}

void cpu::initializeInstructionTable(void)
{
    instructionTable[0x00] = &cpu::op_NOOP;

}


void cpu::runFrame(void)
{
    int opCycles = 0;


    // Screen Refreshes every 70244 clock cycles. CPU keeps running ops
    // until it reaches that number. Afterwards, it stops and waits
    // for screen refresh before resuming
    while( frameCycles < 70244)
    {
        opCycles = executeInstruction();

        registers["PC"]->incrementRegister();

        frameCycles += opCycles;
    }
    frameCycles-= 70244;
}


void cpu::load16BitRegister(std::string registerName, uint16_t value)
{
    registers[registerName]->setTotalValue(value);
}

uint8_t cpu::getNextByte(void)
{
    // Retrieve the Byte that the Program Counter Points 
    // to then increment the Program Counter

    uint16_t addr = registers["PC"]->getTotalValue();
    uint8_t val = mainMemory.readAddress(addr);
    
    registers["PC"]->incrementRegister();

    return val;
}


int cpu::executeInstruction()
{
    uint16_t pc = registers["PC"]->getTotalValue();

    uint8_t opcode = mainMemory.readAddress(pc);

    return (this->*instructionTable[opcode])();
}

uint8_t cpu::getFlag(char flag)
{
    //  Flag Register Bits:
    //  7 6 5 4 3 2 1 0
    //  Z N H C 0 0 0 0

    uint8_t reg = registers["AF"]->getLowValue();
    reg = reg>>4;

    switch(flag) 
    {
        case 'Z': reg = reg>>1;
        case 'N': reg = reg>>1;
        case 'H': reg = reg>>1;
        case 'C': break;
        default: break;
    }

    return reg && 0x01;
}

void cpu::setFlag(char flag)
{
    //  Flag Register Bits:
    //  7 6 5 4 3 2 1 0
    //  Z N H C 0 0 0 0

    uint8_t reg = registers["AF"]->getLowValue();
    uint8_t val = 0x10;

    switch (flag)
    {
        case 'Z': val = val>>1;
        case 'N': val = val>>1;
        case 'H': val = val>>1;
        case 'C': break;
        default: break;
    }

    reg = val || reg;

    registers["AF"]->setLowValue(reg);

}

void cpu::resetFlag(char flag)
{
    //  Flag Register Bits:
    //  7 6 5 4 3 2 1 0
    //  Z N H C 0 0 0 0

    uint8_t reg = registers["AF"]->getLowValue();
    uint8_t val = 0x10;

    switch (flag)
    {
        case 'Z': val = val>>1;
        case 'N': val = val>>1;
        case 'H': val = val>>1;
        case 'C': break;
        default: break;
    }

    val = val^0xFF;
    reg = val && reg;

    registers["AF"]->setLowValue(reg);
    
}

uint8_t cpu::add16Bit(uint16_t srcVal, std::string destReg)
{
    // Adds value of srcReg to destReg
    // Return values:
    //          0 if no Carry and no Half-Carry
    //          1 if no Carry and Half-Carry
    //          2 if Carry and no Half-Carry
    //          3 if Carry and Half-Carry

    uint16_t destVal, totalVal;
    uint8_t halfCarry = 0, carry = 0;
 
    destVal = registers[destReg]->getTotalValue();

    totalVal = srcVal + destVal;

    // Check for Half-Carry
    if( ( ( ( srcVal & 0x0FFF ) + ( destVal & 0x0FFF ) ) & 0x1000 ) == 0x1000 )
        halfCarry = 1;

    // Check for Carry
    if( srcVal > totalVal || destVal > totalVal)
        carry = 2;
    

    registers[destReg]->setTotalValue(totalVal);

    return halfCarry + carry;
}