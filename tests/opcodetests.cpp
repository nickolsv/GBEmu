#include "../header/catch.hpp"
#include "../header/cpu.hh"

TEST_CASE("Instruction 0x0X Testing")
{
    cpu test;

    // 0x01

    test.setRegisterValue("PC",0x0001);
    test.setByteAtAddress(0x0001,0x12);
    test.setByteAtAddress(0x0002,0x34);
    test.setByteAtAddress(0x0003,0x56);
    test.setByteAtAddress(0x0004,0x78);
    test.op_LD_BCnn();
    REQUIRE( test.getRegisterValue("BC") == 0x3412 );

    // 0x02

    test.setHighRegisterValue("AF",0xEE);
    test.op_LD_BCA();
    REQUIRE( test.getByteAtAddress(0x3412) == 0xEE );

    // 0x03

    test.op_INC_BC();
    REQUIRE( test.getRegisterValue("BC") == 0x3413 );

    test.setRegisterValue("BC",0xFFFF);
    test.op_INC_BC();
    REQUIRE( test.getRegisterValue("BC") == 0x0000 );

    // 0x04

    REQUIRE( (test.getFlag('C') == 0 && test.getFlag('H') == 0 && test.getFlag('N') == 0 && test.getFlag('Z') == 0 ));

    test.setHighRegisterValue("BC", 0b11011111);
    test.op_INC_B();
    REQUIRE( test.getHighRegisterValue("BC") == 0b11100000 );
    REQUIRE( (test.getFlag('H') == 1 ));

    test.setHighRegisterValue("BC", 0xFF);
    test.op_INC_B();
    REQUIRE( (test.getFlag('Z') == 1 && test.getFlag('H') == 1  && test.getFlag('N') == 0));

    // 0x05

    test.op_DEC_B();
    REQUIRE( (test.getFlag('N') == 1 && test.getFlag('Z') == 0 && test.getFlag('H') == 1) );
    REQUIRE(test.getHighRegisterValue("BC") == 0xFF);

    // 0x06

    test.setRegisterValue("PC",0x0002);
    test.op_LD_Bn();
    REQUIRE(test.getHighRegisterValue("BC") == 0x34);
    REQUIRE(test.getRegisterValue("PC") == 0x0003);

    // 0x07

    test.setHighRegisterValue("AF", 0b10111011);
    test.resetFlag('C');
    test.op_RLC_A();
    REQUIRE(test.getHighRegisterValue("AF") == 0b01110111);
    REQUIRE(test.getFlag('C') == 1);

    // 0x08

    test.setRegisterValue("SP", 0x5612);
    test.setRegisterValue("PC", 0x0001);
    test.op_LD_aaSP();
    REQUIRE( test.getByteAtAddress(0x3412) == 0x12 );
    REQUIRE( test.getByteAtAddress(0x3413) == 0x56 );
    test.op_LD_aaSP();
    REQUIRE( test.getByteAtAddress(0x7856) == 0x12 );
    REQUIRE( test.getByteAtAddress(0x7857) == 0x56 );

    // 0x09
    
    test.setRegisterValue("HL",0x0000);
    test.setRegisterValue("BC",0xFFFF);
    test.op_ADD_HLBC();
    REQUIRE( test.getRegisterValue("HL") == 0xFFFF);
    REQUIRE( ( test.getFlag('C') == 0 && test.getFlag('H') == 0 && test.getFlag('N') == 0 ));

    test.op_ADD_HLBC();
    REQUIRE( test.getRegisterValue("HL") == 0xFFFE);
    REQUIRE( ( test.getFlag('C') == 1 && test.getFlag('H') == 1 && test.getFlag('N') == 0 ));

    // 0x0A

    test.setByteAtAddress(0x1234, 0xDD);
    test.setRegisterValue("BC",0x1234);
    test.op_LD_ABC();
    REQUIRE( test.getHighRegisterValue("AF") == 0xDD );

    // 0x0B

    test.op_DEC_BC();
    REQUIRE( test.getRegisterValue("BC") == 0x1233 );

    test.setRegisterValue("BC",0x0000);
    test.op_DEC_BC();
    REQUIRE( test.getRegisterValue("BC") == 0xFFFF );

    // 0x0C

    test.setLowRegisterValue("BC", 0xFF);
    test.op_INC_C();
    REQUIRE( test.getLowRegisterValue("BC") == 0x00 );
    REQUIRE( (test.getFlag('H') == 1 ));

    test.setLowRegisterValue("BC", 0x0F);
    test.op_INC_C();
    REQUIRE( (test.getFlag('Z') == 0 && test.getFlag('H') == 1  && test.getFlag('N') == 0));

    // 0x0D

    test.op_DEC_C();
    REQUIRE( (test.getFlag('N') == 1 && test.getFlag('Z') == 0 && test.getFlag('H') == 1) );
    REQUIRE(test.getLowRegisterValue("BC") == 0x0F);

    // 0x0E

}
