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

    return reg & 0x01;
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
        case 'Z': val = val<<1;
        case 'N': val = val<<1;
        case 'H': val = val<<1;
        case 'C': break;
        default: break;
    }

    reg = val | reg;

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
        case 'Z': val = val<<1;
        case 'N': val = val<<1;
        case 'H': val = val<<1;
        case 'C': break;
        default: break;
    }

    val = val^0xFF;
    reg = val & reg;

    registers["AF"]->setLowValue(reg);
}

uint8_t cpu::getByteAtAddress(uint16_t addr)
{
    return mainMemory.readAddress(addr);
}

void cpu::setByteAtAddress(uint16_t addr, uint8_t val)
{
    mainMemory.writeToAddress(addr,val);
}

uint8_t cpu::getHighRegisterValue(std::string regName)
{
    return registers[regName]->getHighValue();
}

uint8_t cpu::getLowRegisterValue(std::string regName)
{
    return registers[regName]->getLowValue();
}

uint16_t cpu::getRegisterValue(std::string regName)
{
    return registers[regName]->getTotalValue();
}

void cpu::setHighRegisterValue(std::string regName, uint8_t val)
{
    registers[regName]->setHighValue(val);
}

void cpu::setLowRegisterValue(std::string regName, uint8_t val)
{
    registers[regName]->setLowValue(val);
}

void cpu::setRegisterValue(std::string regName, uint16_t val)
{
    registers[regName]->setTotalValue(val);
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

uint8_t cpu::add8Bit(uint8_t srcVal, std::string destReg, uint8_t hiLo)
{
    // Adds srcVal to destReg, either to the high or low order byte,
    // depending on whether hiLo is 1 (high) or 0 (low)
    // Note: Should probably be only invoked as add8Bit(srcVal,"AF",1);
    // Since all ADD instructions add to the A register
    // Return values:
    //          0 if no Carry and no Half-Carry
    //          1 if no Carry and Half-Carry
    //          2 if Carry and no Half-Carry
    //          3 if Carry and Half-Carry

    uint8_t destVal, totalVal;
    uint8_t halfCarry = 0, carry = 0;

    if( hiLo == 0 ) destVal = registers[destReg]->getLowValue();
    else            destVal = registers[destReg]->getHighValue();

    totalVal = srcVal + destVal;

    // Check for Half-Carry
    if( ( ( ( srcVal & 0x0F ) + ( destVal & 0x0F ) ) & 0x10 ) == 0x10 )
        halfCarry = 1;

    // Check for Carry
    if( srcVal > totalVal || destVal > totalVal)
        carry = 2;

    if( hiLo == 0 ) registers[destReg]->setLowValue(totalVal);
    else            registers[destReg]->setHighValue(totalVal);

    return halfCarry + carry; 
}

uint8_t cpu::add8BitWithCarry(uint8_t srcVal, std::string destReg, uint8_t hiLo)
{
    // Adds srcVal plus the value of the carry flag
    // to destReg, either to the high or low order byte,
    // depending on whether hiLo is 1 (high) or 0 (low)
    // Note: Should probably be only invoked as add8BitWithCarry(srcVal,"AF",1);
    // Since all ADC instructions add to the A register
    // Return values:
    //          0 if no Carry and no Half-Carry
    //          1 if no Carry and Half-Carry
    //          2 if Carry and no Half-Carry
    //          3 if Carry and Half-Carry

    uint8_t destVal, totalVal;
    uint8_t halfCarry = 0, carry = 0, flags = 0;

    if( getFlag('C') != 0 )
    {
        srcVal++;

        if( srcVal == 0)            carry = 2;
        else if( srcVal % 16 == 0)  halfCarry = 1;          // When incrementing a number, the only case
                                                            // bit 3 can overflow is when a number of the form
                                                            // XXX01111 is incremented to XXX10000, therefore
                                                            // the result mod 16 equals 0
    }

    flags = add8Bit(srcVal, destReg, hiLo);

    return ( flags | (carry + halfCarry) );
}

uint8_t cpu::subtract8Bit(uint8_t srcVal, std::string destReg, uint8_t hiLo)
{
    // Subtracts srcVal from destReg, either from the high or low order byte,
    // depending on whether hiLo is 1 (high) or 0 (low)
    // Note: Should probably be only invoked as subtract8Bit(srcVal,"AF",1);
    // Since all SUB instructions subtract from the A register
    // Return values:
    //          0 if no Carry and no Half-Carry
    //          1 if no Carry and Half-Carry
    //          2 if Carry and no Half-Carry
    //          3 if Carry and Half-Carry

    uint8_t destVal, totalVal;
    uint8_t halfCarry = 0, carry = 0;

    if( hiLo == 0 ) destVal = registers[destReg]->getLowValue();
    else            destVal = registers[destReg]->getHighValue();

    totalVal = destVal - srcVal;

    // Check for Half-Carry
    if( ( srcVal & 0x0F ) > ( destVal & 0x0F ) )
        halfCarry = 1;

    // Check for Carry
    if( totalVal > destVal )
        carry = 2;

    if( hiLo == 0 ) registers[destReg]->setLowValue(totalVal);
    else            registers[destReg]->setHighValue(totalVal);

    return halfCarry + carry; 
}

uint8_t cpu::subtract8BitWithCarry(uint8_t srcVal, std::string destReg, uint8_t hiLo)
{
    // Subtracts srcVal plus the value of the carry flag from destReg, 
    // either from the high or low order byte,
    // depending on whether hiLo is 1 (high) or 0 (low)
    // Note: Should probably be only invoked as subtract8Bit(srcVal,"AF",1);
    // Since all SUB instructions subtract from the A register
    // Return values:
    //          0 if no Carry and no Half-Carry
    //          1 if no Carry and Half-Carry
    //          2 if Carry and no Half-Carry
    //          3 if Carry and Half-Carry

    uint8_t destVal, totalVal;
    uint8_t halfCarry = 0, carry = 0, flags = 0;

    if( getFlag('C') != 0 )
    {
        srcVal--;

        if( srcVal == 0)            carry = 2;
        else if( srcVal % 16 == 15)  halfCarry = 1;         // When decrementing a number, the only case
                                                            // bit 4 is borrowed from is when a number of the form
                                                            // XXX10000 is decremented to XXX01111, therefore
                                                            // the result mod 16 equals 15
    }

    flags = subtract8Bit(srcVal, destReg, hiLo);

    return ( flags | (carry + halfCarry) );  
}

uint8_t cpu::compare8Bit(uint8_t srcVal, std::string destReg, uint8_t hiLo)
{
    // Compares srcVal with the contents of destReg, either with the high or
    // low order byte, depengind on whether hiLo is 1 (high) or 0 (low)
    // Works exactly like subtract8Bit, however the result is discarded
    // and only the flag changes apply, also return the zero flag value
    // as there is no way to deduce it after the function has returned
    // Note: Should probably be only invoked as compare8Bit(srcVal,"AF",1);
    // Since all CP instructions compare with the A register
    // Return values:
    //          0 if no Carry, no Half-Carry and not Zero
    //          1 if no Carry, Half-Carry and not Zero
    //          2 if Carry, no Half-Carry and not Zero
    //          3 if Carry, Half-Carry and not Zero
    //          4 if no Carry, no Half-Carry and Zero
    //          5 if no Carry, Half-Carry and Zero
    //          6 if Carry, no Half-Carry and Zero
    //          7 if Carry, Half-Carry and Zero

    uint8_t destVal, totalVal;
    uint8_t halfCarry = 0, carry = 0, zero = 0;

    if( hiLo == 0 ) destVal = registers[destReg]->getLowValue();
    else            destVal = registers[destReg]->getHighValue();

    totalVal = destVal - srcVal;

    // Check for Half-Carry
    if( ( srcVal & 0x0F ) > ( destVal & 0x0F ) )
        halfCarry = 1;

    // Check for Carry
    if( totalVal > destVal )
        carry = 2;

    // Check for Zero
    if( totalVal == 0 )
        zero = 4;

    return zero + halfCarry + carry; 
}