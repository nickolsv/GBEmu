#include "../header/catch.hpp"
#include "../header/cpu.hh"

TEST_CASE("Instruction 0x0X Testing")
{
    cpu test;

    test.setRegisterValue("PC",0xC001);
    test.setByteAtAddress(0xC001,0x12);
    test.setByteAtAddress(0xC002,0xD4);
    test.setByteAtAddress(0xC003,0x56);
    test.setByteAtAddress(0xC004,0xD8);
    test.setLowRegisterValue("AF",0x00);

    // 0x01

    test.op_LD_BCnn();

    REQUIRE( test.getRegisterValue("BC") == 0xD412 );

    // 0x02

    test.setHighRegisterValue("AF",0xEE);
    test.op_LD_BCA();
    REQUIRE( test.getByteAtAddress(0xD412) == 0xEE );

    // 0x03

    test.op_INC_BC();
    REQUIRE( test.getRegisterValue("BC") == 0xD413 );

    test.setRegisterValue("BC",0xFFFF);
    test.op_INC_BC();
    REQUIRE( test.getRegisterValue("BC") == 0x0000 );


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

    test.setRegisterValue("PC",0xC002);
    test.op_LD_Bn();
    REQUIRE(test.getHighRegisterValue("BC") == 0xD4);
    REQUIRE(test.getRegisterValue("PC") == 0xC003);

    // 0x07

    test.setHighRegisterValue("AF", 0b10111011);
    test.resetFlag('C');
    test.op_RLCA();
    REQUIRE(test.getHighRegisterValue("AF") == 0b01110111);
    REQUIRE(test.getFlag('C') == 1);

    // 0x08

    test.setRegisterValue("SP", 0x5612);
    test.setRegisterValue("PC", 0xC001);
    test.op_LD_aaSP();
    REQUIRE( test.getByteAtAddress(0xD412) == 0x12 );
    REQUIRE( test.getByteAtAddress(0xD413) == 0x56 );
    test.op_LD_aaSP();
    REQUIRE( test.getByteAtAddress(0xD856) == 0x12 );
    REQUIRE( test.getByteAtAddress(0xD857) == 0x56 );

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

    test.setByteAtAddress(0xD234, 0xDD);
    test.setRegisterValue("BC",0xD234);
    test.op_LD_ABC();
    REQUIRE( test.getHighRegisterValue("AF") == 0xDD );

    // 0x0B

    test.op_DEC_BC();
    REQUIRE( test.getRegisterValue("BC") == 0xD233 );

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

    test.setRegisterValue("PC",0xC002);
    test.op_LD_Cn();
    REQUIRE(test.getLowRegisterValue("BC") == 0xD4);
    REQUIRE(test.getRegisterValue("PC") == 0xC003);

    // 0x0F

    test.setHighRegisterValue("AF", 0b10111011);
    test.resetFlag('C');
    test.op_RRCA();
    REQUIRE(test.getHighRegisterValue("AF") == 0b11011101);
    REQUIRE(test.getFlag('C') == 1);

}

TEST_CASE("Instruction 0x1X Testing")
{
    cpu test;

    test.setRegisterValue("PC",0xC001);
    test.setByteAtAddress(0xC001,0x12);
    test.setByteAtAddress(0xC002,0xD4);
    test.setByteAtAddress(0xC003,0x56);
    test.setByteAtAddress(0xC004,0xD8);
    test.setLowRegisterValue("AF",0x00);

    // 0x10

    // 0x11

    test.op_LD_DEnn();

    REQUIRE( test.getRegisterValue("DE") == 0xD412 );

    // 0X12

    test.setHighRegisterValue("AF",0xEE);
    test.op_LD_DEA();
    REQUIRE( test.getByteAtAddress(0xD412) == 0xEE );

    // 0x13

    test.op_INC_DE();
    REQUIRE( test.getRegisterValue("DE") == 0xD413 );

    test.setRegisterValue("DE",0xFFFF);
    test.op_INC_DE();
    REQUIRE( test.getRegisterValue("DE") == 0x0000 );

    // 0X14

    REQUIRE( (test.getFlag('C') == 0 && test.getFlag('H') == 0 && test.getFlag('N') == 0 && test.getFlag('Z') == 0 ));

    test.setHighRegisterValue("DE", 0b11011111);
    test.op_INC_D();
    REQUIRE( test.getHighRegisterValue("DE") == 0b11100000 );
    REQUIRE( (test.getFlag('H') == 1 ));

    test.setHighRegisterValue("DE", 0xFF);
    test.op_INC_D();
    REQUIRE( (test.getFlag('Z') == 1 && test.getFlag('H') == 1  && test.getFlag('N') == 0));

    // 0x15

    test.op_DEC_D();
    REQUIRE( (test.getFlag('N') == 1 && test.getFlag('Z') == 0 && test.getFlag('H') == 1) );
    REQUIRE(test.getHighRegisterValue("DE") == 0xFF);

    // 0x16

    test.setRegisterValue("PC",0xC002);
    test.op_LD_Dn();
    REQUIRE(test.getHighRegisterValue("DE") == 0xD4);
    REQUIRE(test.getRegisterValue("PC") == 0xC003);

    // 0x17

    test.setHighRegisterValue("AF", 0b10111011);
    test.resetFlag('C');
    test.op_RLA();
    REQUIRE(test.getHighRegisterValue("AF") == 0b01110110);
    REQUIRE(test.getFlag('C') == 1);

    // 0x19
    
    test.setRegisterValue("HL",0x0000);
    test.setRegisterValue("DE",0xFFFF);
    test.op_ADD_HLDE();
    REQUIRE( test.getRegisterValue("HL") == 0xFFFF);
    REQUIRE( ( test.getFlag('C') == 0 && test.getFlag('H') == 0 && test.getFlag('N') == 0 ));

    test.op_ADD_HLDE();
    REQUIRE( test.getRegisterValue("HL") == 0xFFFE);
    REQUIRE( ( test.getFlag('C') == 1 && test.getFlag('H') == 1 && test.getFlag('N') == 0 ));

    // 0x1A

    test.setByteAtAddress(0xD234, 0xDD);
    test.setRegisterValue("DE",0xD234);
    test.op_LD_ADE();
    REQUIRE( test.getHighRegisterValue("AF") == 0xDD );

    // 0x1B

    test.op_DEC_DE();
    REQUIRE( test.getRegisterValue("DE") == 0xD233 );

    test.setRegisterValue("DE",0x0000);
    test.op_DEC_DE();
    REQUIRE( test.getRegisterValue("DE") == 0xFFFF );

    // 0x1C

    test.setLowRegisterValue("DE", 0xFF);
    test.op_INC_E();
    REQUIRE( test.getLowRegisterValue("DE") == 0x00 );
    REQUIRE( (test.getFlag('H') == 1 ));

    test.setLowRegisterValue("DE", 0x0F);
    test.op_INC_E();
    REQUIRE( (test.getFlag('Z') == 0 && test.getFlag('H') == 1  && test.getFlag('N') == 0));

    // 0x1D

    test.op_DEC_E();
    REQUIRE( (test.getFlag('N') == 1 && test.getFlag('Z') == 0 && test.getFlag('H') == 1) );
    REQUIRE(test.getLowRegisterValue("DE") == 0x0F);

    // 0x1E

    test.setRegisterValue("PC",0xC002);
    test.op_LD_En();
    REQUIRE(test.getLowRegisterValue("DE") == 0xD4);
    REQUIRE(test.getRegisterValue("PC") == 0xC003);

    // 0x1F

    test.setHighRegisterValue("AF", 0b10111011);
    test.resetFlag('C');
    test.op_RRA();
    REQUIRE(test.getHighRegisterValue("AF") == 0b01011101);
    REQUIRE(test.getFlag('C') == 1);

    // 0x18

    test.setRegisterValue("PC",0xC00E);
    test.setByteAtAddress(0xC00E,0x00);
    test.setByteAtAddress(0xC00F,0xF0);

    test.op_JR_n();
    REQUIRE(test.getRegisterValue("PC") == 0xC00F);
    test.op_JR_n();
    REQUIRE(test.getRegisterValue("PC") == 0xC000);

}
