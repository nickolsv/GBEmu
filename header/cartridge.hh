#ifndef __GB_CARTRIDGE_HH__
#define __GB_CARTRIDGE_HH__

#include <vector>
#include <string>
#include "memory.hh"

class cartridge
{
    private:
        // Contains the ROM binary split
        // into 16KB Chunks
        int bankCount;
        std::vector<ROMBank *> banks;
    public:
        cartridge(std::string);
        ~cartridge();
        ROMBank *getROMBank(int);
};

#endif
