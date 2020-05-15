#ifndef __GB_MEMORY_HH__
#define __GB_MEMORY_HH__

#include <stdint.h>


class memory
{
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