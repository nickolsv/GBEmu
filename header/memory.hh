#ifndef __GB_MEMORY_HH__
#define __GB_MEMORY_HH__

#include <stdint.h>


class memory
{
    // Memory Map:
    // 0x0000 - 0x00FF  :  Restart and Interrupt Vectors
    // 0x0100 - 0x014F  :  Cartridge Header
    // 0x0150 - 0x3FFF  :  ROM Bank 0
    // 0x4000 - 0x7FFF  :  ROM Bank N  (Swappable)
    // 0x8000 - 0x97FF  :  Tile RAM
    // 0x9800 - 0x9BFF  :  BG Map Data 1
    // 0x9C00 - 0x9FFF  :  BG Map Data 2
    // 0xA000 - 0xBFFF  :  Cartridge RAM ( If present )
    // 0xC000 - 0xDFFF  :  Internal Work RAM
    // 0xE000 - 0xFDFF  :  Echo RAM
    // 0xFE00 - 0xFE9F  :  0AM (Sprite RAM)
    // 0xFEA0 - 0xFEFF  :  Unused
    // 0xFF00 - 0xFF7F  :  Hardware I/O Registers
    // 0xFF80 - 0xFFFE  :  High RAM Area
    // 0xFFFF           :  Interrupt Enable Register
    
    private:
        int memSize;
        uint8_t* memArray;
    public:
        memory();
        ~memory();
        uint8_t readAddress(uint16_t);
        void writeToAddress(uint16_t,uint8_t);
};

#endif