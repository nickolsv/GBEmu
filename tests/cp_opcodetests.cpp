#include "../header/catch.hpp"
#include "../header/cpu.hh"

TEST_CASE("Instruction 0xCB 0x0X Testing")
{
    cpu test;

    test.setRegisterValue("BC",0x8000);
    test.setRegisterValue("DE",0x7FFE);
    test.setRegisterValue("HL",0x6001);
    test.setHighRegisterValue("AF",0xFF);

    test.setByteAtAddress(0xC002, 0x87);

    // 0xCB 0x00

    test.op_RLC_B();
    REQUIRE( test.getHighRegisterValue("BC") == 0x01);
    REQUIRE( test.getFlag('C') == 1);

    // 0xCB 0x01

    test.op_RLC_C();
    REQUIRE( test.getLowRegisterValue("BC") == 0x00);
    REQUIRE( test.getFlag('C') == 0);
    REQUIRE( test.getFlag('Z') == 1);

    // 0xCB 0x02

    test.op_RLC_D();
    REQUIRE( test.getHighRegisterValue("DE") == 0xFE);
    REQUIRE( test.getFlag('C') == 0);
    REQUIRE( test.getFlag('Z') == 0);

    // 0xCB 0x03

    test.op_RLC_E();
    REQUIRE( test.getLowRegisterValue("DE") == 0xFD);
    REQUIRE( test.getFlag('C') == 1);

    // 0xCB 0x04

    test.op_RLC_H();
    REQUIRE( test.getHighRegisterValue("HL") == 0xC0);
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x05

    test.op_RLC_L();
    REQUIRE( test.getLowRegisterValue("HL") == 0x02);
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x06

    test.op_RLC_HLaddr();
    REQUIRE( test.getByteAtAddress(0xC002) == 0x0F );
    REQUIRE( test.getFlag('C') == 1);

    // 0xCB 0x07

    test.op_RLC_A();
    REQUIRE( test.getHighRegisterValue("AF") == 0xFF);
    REQUIRE( test.getFlag('C') == 1);
    REQUIRE( test.getFlag('Z') == 0);

    // 0xCB 0x08

    test.op_RRC_B();
    REQUIRE( test.getHighRegisterValue("BC") == 0x80);
    REQUIRE( test.getFlag('C') == 1);

    // 0xCB 0x09

    test.op_RRC_C();
    REQUIRE( test.getLowRegisterValue("BC") == 0x00);
    REQUIRE( test.getFlag('C') == 0);
    REQUIRE( test.getFlag('Z') == 1);

    // 0xCB 0x0A

    test.op_RRC_D();
    REQUIRE( test.getHighRegisterValue("DE") == 0x7F);
    REQUIRE( test.getFlag('C') == 0);
    REQUIRE( test.getFlag('Z') == 0);

    // 0xCB 0x0B

    test.op_RRC_E();
    REQUIRE( test.getLowRegisterValue("DE") == 0xFE);
    REQUIRE( test.getFlag('C') == 1);

    // 0xCB 0x0E

    test.op_RRC_HLaddr();
    REQUIRE( test.getByteAtAddress(0xC002) == 0x87 );
    REQUIRE( test.getFlag('C') == 1);

    // 0xCB 0x0C

    test.op_RRC_H();
    REQUIRE( test.getHighRegisterValue("HL") == 0x60);
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x0D

    test.op_RRC_L();
    REQUIRE( test.getLowRegisterValue("HL") == 0x01);
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x0F

    test.op_RRC_A();
    REQUIRE( test.getHighRegisterValue("AF") == 0xFF);
    REQUIRE( test.getFlag('C') == 1);
    REQUIRE( test.getFlag('Z') == 0);

    REQUIRE( test.getRegisterValue("BC") == 0x8000 );
    REQUIRE( test.getRegisterValue("DE") == 0x7FFE );
    REQUIRE( test.getRegisterValue("HL") == 0x6001 );
    REQUIRE( test.getHighRegisterValue("AF") == 0xFF );
    REQUIRE( test.getByteAtAddress(0xC002) == 0x87 );

}

TEST_CASE("Instruction 0xCB 0x1X Testing")
{
    cpu test;

    test.setRegisterValue("BC",0x8000);
    test.setRegisterValue("DE",0x7FFE);
    test.setRegisterValue("HL",0x6001);
    test.setHighRegisterValue("AF",0xFF);

    test.setByteAtAddress(0xC102, 0x87);

    test.setLowRegisterValue("AF",0x00);

    // 0xCB 0x10

    test.op_RL_B();
    REQUIRE( test.getHighRegisterValue("BC") == 0x00);
    REQUIRE( test.getFlag('C') == 1);
    REQUIRE( test.getFlag('Z') == 1);

    // 0xCB 0x11

    test.op_RL_C();
    REQUIRE( test.getLowRegisterValue("BC") == 0x01);
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x12

    test.op_RL_D();
    REQUIRE( test.getHighRegisterValue("DE") == 0xFE);
    REQUIRE( test.getFlag('C') == 0);
    REQUIRE( test.getFlag('Z') == 0);

    // 0xCB 0x13

    test.op_RL_E();
    REQUIRE( test.getLowRegisterValue("DE") == 0xFC);
    REQUIRE( test.getFlag('C') == 1);

    // 0xCB 0x14

    test.op_RL_H();
    REQUIRE( test.getHighRegisterValue("HL") == 0xC1);
    REQUIRE( test.getFlag('C') == 0);
    REQUIRE( test.getFlag('Z') == 0);

    // 0xCB 0x15

    test.op_RL_L();
    REQUIRE( test.getLowRegisterValue("HL") == 0x02);
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x16

    test.op_RL_HLaddr();
    REQUIRE( test.getByteAtAddress(0xC102) == 0x0E );
    REQUIRE( test.getFlag('C') == 1);

    // 0xCB 0x17

    test.op_RL_A();
    REQUIRE( test.getHighRegisterValue("AF") == 0xFF);
    REQUIRE( test.getFlag('C') == 1);
    REQUIRE( test.getFlag('Z') == 0);

    // 0xCB 0x1F

    test.op_RR_A();
    REQUIRE( test.getHighRegisterValue("AF") == 0xFF);
    REQUIRE( test.getFlag('C') == 1);

    // 0xCB 0x1E

    test.op_RR_HLaddr();
    REQUIRE( test.getByteAtAddress(0xC102) == 0x87 );
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x1D

    test.op_RR_L();
    REQUIRE( test.getLowRegisterValue("HL") == 0x01);
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x1C

    test.op_RR_H();
    REQUIRE( test.getHighRegisterValue("HL") == 0x60);
    REQUIRE( test.getFlag('C') == 1);
    REQUIRE( test.getFlag('Z') == 0);

    // 0xCB 0x1B

    test.op_RR_E();
    REQUIRE( test.getLowRegisterValue("DE") == 0xFE);
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x1A

    test.op_RR_D();
    REQUIRE( test.getHighRegisterValue("DE") == 0x7F);
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x19

    test.op_RR_C();
    REQUIRE( test.getLowRegisterValue("BC") == 0x00);
    REQUIRE( test.getFlag('C') == 1);
    REQUIRE( test.getFlag('Z') == 1);

    // 0xCB 0x18

    test.op_RR_B();
    REQUIRE( test.getHighRegisterValue("BC") == 0x80);

    REQUIRE( test.getRegisterValue("BC") == 0x8000 );
    REQUIRE( test.getRegisterValue("DE") == 0x7FFE );
    REQUIRE( test.getRegisterValue("HL") == 0x6001 );
    REQUIRE( test.getHighRegisterValue("AF") == 0xFF );
    REQUIRE( test.getByteAtAddress(0xC102) == 0x87 );
}