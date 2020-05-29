#ifndef __GB_MEMORY_HH__
#define __GB_MEMORY_HH__

#include <stdint.h>

class cartridge;

class memoryBank
{
    protected:
        int memSize;
        uint8_t* memArray;
    public:
        memoryBank(uint16_t size);
        ~memoryBank();
        uint8_t readAddress(uint16_t);
        virtual void writeToAddress(uint16_t, uint8_t);
};

class ROMBank : public memoryBank
{
    public:
        ROMBank(uint16_t size);
        ~ROMBank();
        void fillBank(uint8_t *buf);
};

class RAMBank : public memoryBank
{
    public:
        RAMBank(uint16_t size);
        ~RAMBank();
        virtual void writeToAddress(uint16_t, uint8_t);
};

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
    // 0xFE00 - 0xFE9F  :  OAM (Sprite RAM)
    // 0xFEA0 - 0xFEFF  :  Unused
    // 0xFF00 - 0xFF7F  :  Hardware I/O Registers
    // 0xFF80 - 0xFFFE  :  High RAM Area
    // 0xFFFF           :  Interrupt Enable Register
    
    private:
        int memSize;
        uint8_t* memArray;

        memoryBank *ROM0;                  // 16KB
        memoryBank *ROMn;                  // 16KB
        memoryBank *vRAM;                  // 8KB
        memoryBank *cartridgeRAM;          // 8KB
        memoryBank *internalRAM;           // 8KB
        memoryBank *echoRAM;               // 7KB + 512 bytes
        memoryBank *spriteRAM;             // 256 bytes
        memoryBank *HWRegisters;           // 128 bytes
        memoryBank *highRAM;               // 127 bytes
        uint8_t interruptRegister;
        
    public:
        memory();
        ~memory();
        uint8_t readAddress(uint16_t);
        void writeToAddress(uint16_t,uint8_t);
        void loadROM(cartridge *);
};

#endif