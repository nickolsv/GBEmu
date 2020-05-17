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

        incrementPC();

        frameCycles += opCycles;
    }
    frameCycles-= 70244;
}


void cpu::load16BitRegister(std::string registerName, uint16_t value)
{
    registers[registerName]->setTotalValue(value);
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

void cpu::setFlag(char flag, uint8_t flagValue)
{
    //  Flag Register Bits:
    //  7 6 5 4 3 2 1 0
    //  Z N H C 0 0 0 0

    // TODO: Implement
}