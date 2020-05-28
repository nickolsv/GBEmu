#include "./header/memory.hh"
#include "./header/cartridge.hh"
#include "./header/cpu.hh"
#include "./header/memory.hh"
#include "./header/registers.hh"

#include <iostream>

int main(void)
{
    memory mem;
    
    mem.writeToAddress(0xCDEF,0x55);
    mem.writeToAddress(0xCDDD,0x44);

    std::cout << std::hex << (int) mem.readAddress(0xCDEF) << std::endl;
    std::cout << std::hex << (int) mem.readAddress(0xCDDD) << std::endl;

    mem.writeToAddress(0xCDEF,0xFF);

    std::cout << std::hex << (int) mem.readAddress(0xCDEF) << std::endl;
    return 0;
}