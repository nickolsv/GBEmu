#include <cstring>
#include "../header/memory.hh"
#include "../header/cartridge.hh"

memory::memory()
{
    memSize = 0xFFFF;
    memArray = new uint8_t[memSize];

    std::memset(memArray, 0, memSize*sizeof(uint8_t));

    // ROM Banks will be created when a ROM is loaded
    vRAM = new RAMBank(0x2000);
    cartridgeRAM = new RAMBank(0x2000);     // TODO: Change when implementing MBC
    internalRAM = new RAMBank(0x2000);
    echoRAM = internalRAM;
    spriteRAM = new RAMBank(0x00FF);
    HWRegisters = new RAMBank(0x008F);
    highRAM = new RAMBank(0x008E);

}

memory::~memory()
{
    delete vRAM;
    delete cartridgeRAM;
    delete internalRAM;
    delete spriteRAM;
    delete HWRegisters;
    delete highRAM;
    
    delete memArray;
}

void memory::loadROM(cartridge *ROM)
{
    ROM0 = ROM->getROMBank(0);
    ROMn = ROM->getROMBank(1);
}

uint8_t memory::readAddress(uint16_t address)
{
    if( address < 0x4000 )
    {
        if( ROM0 == 0 ) return 0x00;
        return ROM0->readAddress(address);
    }
    else if( address < 0x8000 )
    {
        if( ROM0 == 0 ) return 0x00;
        return ROMn->readAddress(address & 0x3FFF);
    }
    else if( address < 0xA000 )
    {
        return vRAM->readAddress(address & 0x1FFF);
    }
    else if( address < 0xC000 )
    {
        return cartridgeRAM->readAddress(address & 0x1FFF);
    }
    else if( address < 0xE000 )
    {
        return internalRAM->readAddress(address & 0x1FFF);
    }
    else if( address < 0xFE00 )
    {
        return echoRAM->readAddress(address & 0x1FFF);
    }
    else if( address < 0xFEA0 )
    {
        return spriteRAM->readAddress(address & 0x0100);
    }
    else if( address < 0xFF00 )
    {
        // TODO: Maybe error?
        return 0x00;
    }
    else if( address < 0xFF80 )
    {
        return HWRegisters->readAddress(address & 0x007F);
    }
    else if( address < 0xFFFF )
    {
        return highRAM->readAddress(address & 0x007F);   
    }
    return interruptRegister;
}

void memory::writeToAddress(uint16_t address, uint8_t value)
{
    if( address < 0x4000 )
    {
        //TODO: MBC Stuff
    }
    else if( address < 0x8000 )
    {
        //TODO: MBC Stuff
    }
    else if( address < 0xA000 )
    {
        vRAM->writeToAddress(address & 0x1FFF,value);
    }
    else if( address < 0xC000 )
    {
        cartridgeRAM->writeToAddress(address & 0x1FFF,value);
    }
    else if( address < 0xE000 )
    {
        internalRAM->writeToAddress(address & 0x1FFF,value);
    }
    else if( address < 0xFE00 )
    {
        // TODO: Maybe error?
        echoRAM->writeToAddress(address & 0x1FFF,value);
    }
    else if( address < 0xFEA0 )
    {
        spriteRAM->writeToAddress(address & 0x0100,value);
    }
    else if( address < 0xFF00 )
    {
        // TODO: Maybe error?
    }
    else if( address < 0xFF80 )
    {
        HWRegisters->writeToAddress(address & 0x007F,value);
    }
    else if( address < 0xFFFF )
    {
        highRAM->writeToAddress(address & 0x007F,value);   
    }
    interruptRegister = value;
}

memoryBank::memoryBank(uint16_t size) : memSize{size}
{
    memArray = new uint8_t[memSize];
    std::memset(memArray, 0, memSize*sizeof(uint8_t));

}

memoryBank::~memoryBank()
{
    delete memArray;
}

uint8_t memoryBank::readAddress(uint16_t addr)
{
    return memArray[addr];
}

void memoryBank::writeToAddress(uint16_t addr, uint8_t val)
{}

ROMBank::ROMBank(uint16_t size) : memoryBank(size)
{}

ROMBank::~ROMBank()
{}

void ROMBank::fillBank(uint8_t *buf)
{
    std::memcpy(memArray,buf,0x4000);
}

RAMBank::RAMBank(uint16_t size) : memoryBank(size)
{}

RAMBank::~RAMBank()
{}

void RAMBank::writeToAddress(uint16_t addr, uint8_t val)
{
    memArray[addr] = val;
}