#include "../header/registers.hh"

register16::register16() : high(), low()
{
}

register16::~register16()
{
}


uint8_t register16::getHighValue(void)
{
    return high.getValue();
}

void register16::setHighValue(uint8_t val)
{
    high.setValue(val);
}


uint8_t register16::getLowValue(void)
{
    return low.getValue();
}

void register16::setLowValue(uint8_t val)
{
    low.setValue(val);
}


uint16_t register16::getTotalValue(void)
{
    uint16_t value = getHighValue();
    value = value<<8;
    value+= getLowValue();

    return value;
}

void register16::setTotalValue(uint16_t val)
{
    uint8_t low = (uint8_t) val;
    uint16_t copy = val;
    copy = copy>>8;

    uint8_t hi = copy;

    setHighValue(hi);
    setLowValue(low);
}

void register16::incrementRegister(void)
{
    uint16_t regVal = getTotalValue();

    regVal++;
    setTotalValue(regVal);
}

void register16::incrementHighRegister(void)
{
    high.incrementRegister();
}

void register16::incrementLowRegister(void)
{
    low.incrementRegister();
}

void register16::decrementRegister(void)
{
    uint16_t regVal = getTotalValue();

    regVal--;
    setTotalValue(regVal);
}

void register16::decrementHighRegister(void)
{
    high.decrementRegister();
}

void register16::decrementLowRegister(void)
{
    low.decrementRegister();
}

uint8_t register16::rotateHighLeft()
{
    // Return value of previous bit 7
    // to set the carry flag 
    
    return high.rotateLeft();
}

uint8_t register16::rotateLowLeft()
{
    // Return value of previous bit 7
    // to set the carry flag 
    
    return low.rotateLeft();
}

uint8_t register16::rotateHighRight()
{
    // Return value of previous bit 0
    // to set the carry flag 
    
    return high.rotateRight();
}

uint8_t register16::rotateLowRight()
{
    // Return value of previous bit 0
    // to set the carry flag 
    
    return low.rotateRight();
}

uint8_t register16::shiftHighLeft()
{
    // Return value of previous bit 7
    // to set the carry flag 
    
    return high.shiftLeft();
}

uint8_t register16::shiftLowLeft()
{
    // Return value of previous bit 7
    // to set the carry flag 
    
    return low.shiftLeft();
}

uint8_t register16::shiftHighRight(uint8_t arg)
{
    // Return value of previous bit 0
    // to set the carry flag 
    
    return high.shiftRight(arg);
}

uint8_t register16::shiftLowRight(uint8_t arg)
{
    // Return value of previous bit 0
    // to set the carry flag
    // If arg is 0 (SRA):
    //  Bit 7 stays unchanged
    // If arg is 1 (SRL):
    //  Bit 7 is reset

    return low.shiftRight(arg);
}

void register16::swapNibblesHigh(void)
{
    high.swapNibbles();
}

void register16::swapNibblesLow(void)
{
    low.swapNibbles();
}

uint8_t register16::getnthBitLow(uint8_t n)
{
    // Returns the nth bit of the low register
    return low.getnthBit(n);
}

uint8_t register16::getnthBitHigh(uint8_t n)
{
    // Returns the nth bit of the high register
    return high.getnthBit(n);
}

void register16::setnthBitLow(uint8_t n)
{
    // Sets the nth bit of the low register
    low.setnthBit(n);
}

void register16::setnthBitHigh(uint8_t n)
{
    // Sets the nth bit of the high register
    high.setnthBit(n);
}

void register16::resetnthBitLow(uint8_t n)
{
    // Reset the nth bit of the low register
    low.setnthBit(n);
}

void register16::resetnthBitHigh(uint8_t n)
{
    // Reset the nth bit of the high register
    high.setnthBit(n);
}


register8::register8()
{
    setValue(0);
}


register8::~register8()
{
}

uint8_t register8::getValue()
{
    return data;
}

void register8::setValue(uint8_t val)
{
    data = val;
}

void register8::incrementRegister(void)
{
    data++;
}

void register8::decrementRegister(void)
{
    data--;
}

uint8_t register8::rotateLeft()
{
    // Return value of previous bit 7
    // to set the carry flag 
    
    uint8_t val  = getValue();
    uint8_t temp = val & 0x80;

    val = val<<1;
    temp = temp>>7;

    val = val | temp;

    setValue(val);

    return temp;
}

uint8_t register8::rotateRight()
{
    // Return value of previous bit 0
    // to set the carry flag 
    
    uint8_t val  = getValue();
    uint8_t temp = val & 0x01;

    val = val>>1;
    temp = temp<<7;

    setValue(temp | val);

    return temp;
}

uint8_t register8::shiftLeft()
{
    // Return value of previous bit 7
    // to set the carry flag 
    // Bit 0 set to 0
    
    uint8_t val  = getValue();
    uint8_t temp = val & 0x80;

    val = val<<1;
    val = val & 0xFE;
    setValue(val);

    return temp;
}

uint8_t register8::shiftRight(uint8_t arg)
{
    // Return value of previous bit 0
    // to set the carry flag 
    // If arg is 0 (SRA):
    //  Bit 7 stays unchanged
    // If arg is 1 (SRL):
    //  Bit 7 is reset

    uint8_t val  = getValue();
    uint8_t temp = val & 0x01;
    uint8_t bit7 = val & 0x80;

    val = val>>1;
    val = val & 0x7F;
    if( arg == 0)   val = val | bit7;
    setValue(val);

    return temp;
}

void register8::swapNibbles(void)
{
    // Swaps 4 lower bits of register
    // with its 4 higher  bits

    uint8_t val  = getValue();
    uint8_t temp = val & 0x0F;

    val = val>>4;
    temp = temp<<4;

    val = ( ( val & 0x0F) & (temp & 0xF0) );

    setValue(val);
}

uint8_t register8::getnthBit(uint8_t n)
{
    // Returns the value of the nth bit of register

    uint8_t val;

    val = getValue();
    val = val>>n;
    val = val & 0x01;

    return val;
}

void register8::setnthBit(uint8_t n)
{
    // Sets the nth bit of register

    uint8_t val, temp;

    val = getValue();
    
    temp = 0x01;
    temp = temp<<n;

    val = val | temp;

    setValue(val);
}

void register8::resetnthBit(uint8_t n)
{
    // Resets the nth bit of register

    uint8_t val, temp;

    val = getValue();

    temp = 0x01;
    temp = temp<<n;
    temp = temp^0xFF;

    val = val & temp;

    setValue(val);
}

