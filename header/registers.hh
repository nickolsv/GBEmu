#ifndef __GB_REGISTERS_HH__
#define __GB_REGISTERS_HH__

#include <stdint.h>

class register8
{
    private:
        uint8_t data; 
    public:
        register8();
        ~register8();
        uint8_t getValue();
        void setValue(uint8_t);
        
        void incrementRegister();
        void decrementRegister();

        uint8_t rotateLeft();
        uint8_t rotateRight();

        uint8_t shiftLeft();
        uint8_t shiftRight(uint8_t);

        void swapNibbles();

        uint8_t getnthBit(uint8_t);
        void setnthBit(uint8_t);
        void resetnthBit(uint8_t);

};

// The Gameboy has eight 8-bit ( A,B,C,D,E,H,L )
// and two 16-bit registers ( Stack Pointer / Program Counter)
// However, pairs of 8-bit registers can be used as 16-bit 
// registers by some instructions. Therefore, the CPU's ten registers
// can be modelled as six 16-bit registers, ( AF,BC,DE,HL,PC,SP )
// each one of which consists of a high and a low 8-bit register

class register16
{
    private:
        register8 high;
        register8 low;
    public:
        register16();
        ~register16();

        uint8_t getHighValue();
        void setHighValue(uint8_t);
        uint8_t getLowValue();
        void setLowValue(uint8_t);

        uint16_t getTotalValue();
        void setTotalValue(uint16_t);

        void incrementRegister();
        void incrementHighRegister();
        void incrementLowRegister();

        void decrementRegister();
        void decrementHighRegister();
        void decrementLowRegister();

        uint8_t rotateHighLeft();
        uint8_t rotateHighRight();
        uint8_t rotateLowLeft();
        uint8_t rotateLowRight();

        uint8_t shiftHighLeft();
        uint8_t shiftHighRight(uint8_t);
        uint8_t shiftLowLeft();
        uint8_t shiftLowRight(uint8_t);

        void swapNibblesHigh();
        void swapNibblesLow();

        uint8_t getnthBitLow(uint8_t);
        uint8_t getnthBitHigh(uint8_t);
        void setnthBitLow(uint8_t);
        void setnthBitHigh(uint8_t);
        void resetnthBitLow(uint8_t);
        void resetnthBitHigh(uint8_t);

};

#endif