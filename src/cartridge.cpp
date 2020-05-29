#include <fstream>
#include <cstring>
#include <vector>
#include <cmath>
#include "../header/cartridge.hh"


cartridge::cartridge(std::string ROMFilename)
{
    // Gets Size of ROM File, calculates how many 16KB
    // chunks it can be broken down into then splits the file
    int size = 0;
    double chunks;
    ROMBank *temp;
    uint8_t *buf = new uint8_t[0x4000];

    // Seek to end to find file size then seek back to start of file
    std::ifstream rom(ROMFilename, std::ios::in | std::ios::binary);
    if( rom )
    {
        rom.seekg(0,rom.end);
        size = rom.tellg();
        rom.seekg(0,rom.beg);

        chunks = (double) ( ((double) size) / 0x4000);
        bankCount = ceil(chunks);

        for( int i = 0; i < bankCount; i++)
        {
            // For each chunk, read 16KB from the file
            // then creates a ROMBank with that data
            // which is pushed into the ROMBank vector
            rom.read(reinterpret_cast<char *>(buf),0x4000);
            temp = new ROMBank(0x4000);
            temp->fillBank(buf);
            banks.push_back(temp);
        }
    }

    delete buf;
}

cartridge::~cartridge()
{
    while( !banks.empty() )
    {
        delete banks.back();
        banks.pop_back();
    } 
}

ROMBank *cartridge::getROMBank(int id)
{
    try
    {
        return banks.at(id);
    }
    catch(const std::exception& e)
    {
        return 0;
    }
    

}