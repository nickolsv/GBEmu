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