#include "../header/catch.hpp"
#include "../header/registers.hh"

TEST_CASE("Getters & Setters")
{
    register16 test;

    test.setHighValue(0x12);
    test.setLowValue(0x34);
    REQUIRE( test.getTotalValue() == 0x1234 );
    
    test.setTotalValue(0x4321);
    REQUIRE( test.getHighValue() == 0x43 );
    REQUIRE( test.getLowValue() == 0x21 );
}

TEST_CASE("8Bit Register Functions")
{
    register8 test;

    test.setValue(0x0F);
    test.incrementRegister();

    REQUIRE( test.getValue() == 0x10 );

    test.decrementRegister();
    REQUIRE( test.getValue() == 0x0F );

    test.rotateRight();
    REQUIRE( test.getValue() == 0x87 );

    test.rotateLeft();
    REQUIRE( test.getValue() == 0x0F );


    test.setValue(0xFF);
    test.incrementRegister();
    REQUIRE( test.getValue() == 0x00 );

    test.decrementRegister();
    REQUIRE( test.getValue() == 0xFF );

    test.rotateLeft();
    REQUIRE( test.getValue() == 0xFF );

    test.rotateRight();
    REQUIRE( test.getValue() == 0xFF );
}

TEST_CASE("16Bit Register Functions")
{
    register16 test;

    test.setTotalValue(0xFFFF);
    test.incrementRegister();
    REQUIRE( test.getTotalValue() == 0x0000 );

    test.decrementRegister();
    REQUIRE( test.getTotalValue() == 0xFFFF );

    test.incrementHighRegister();
    test.decrementLowRegister();
    REQUIRE( test.getTotalValue() == 0x00FE );
}