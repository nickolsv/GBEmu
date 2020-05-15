#include <cstring>
#include "../header/memory.hh"

memory::memory()
{
    memSize = 0xFFFF;
    memArray = new uint8_t[memSize];

    std::memset(memArray, 0, memSize*sizeof(uint8_t));
}

memory::~memory()
{
    delete memArray;
}

uint8_t memory::readAddress(uint16_t address)
{
    return memArray[address];
}


void memory::writeToAddress(uint16_t address, uint8_t value)
{
    memArray[address] = value;
}