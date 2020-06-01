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

TEST_CASE("Instruction 0xCB 0x2X Testing")
{
    cpu test;

    test.setRegisterValue("BC",0x8000);
    test.setRegisterValue("DE",0x7FFE);
    test.setRegisterValue("HL",0x6001);
    test.setHighRegisterValue("AF",0xFF);

    test.setByteAtAddress(0xC002, 0x87);

    test.setLowRegisterValue("AF",0x00);

    // 0xCB 0x20

    test.op_SLA_B();
    REQUIRE( test.getHighRegisterValue("BC") == 0x00);
    REQUIRE( test.getFlag('C') == 1);
    REQUIRE( test.getFlag('Z') == 1);

    // 0xCB 0x21

    test.op_SLA_C();
    REQUIRE( test.getLowRegisterValue("BC") == 0x00);
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x22

    test.op_SLA_D();
    REQUIRE( test.getHighRegisterValue("DE") == 0xFE);
    REQUIRE( test.getFlag('C') == 0);
    REQUIRE( test.getFlag('Z') == 0);

    // 0xCB 0x23

    test.op_SLA_E();
    REQUIRE( test.getLowRegisterValue("DE") == 0xFC);
    REQUIRE( test.getFlag('C') == 1);

    // 0xCB 0x24

    test.op_SLA_H();
    REQUIRE( test.getHighRegisterValue("HL") == 0xC0);
    REQUIRE( test.getFlag('C') == 0);
    REQUIRE( test.getFlag('Z') == 0);

    // 0xCB 0x25

    test.op_SLA_L();
    REQUIRE( test.getLowRegisterValue("HL") == 0x02);
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x26

    test.op_SLA_HLaddr();
    REQUIRE( test.getByteAtAddress(0xC002) == 0x0E );
    REQUIRE( test.getFlag('C') == 1);

    // 0xCB 0x27

    test.op_SLA_A();
    REQUIRE( test.getHighRegisterValue("AF") == 0xFE);
    REQUIRE( test.getFlag('C') == 1);
    REQUIRE( test.getFlag('Z') == 0);

    // 0xCB 0x2F

    test.op_SRA_A();
    REQUIRE( test.getHighRegisterValue("AF") == 0xFF);
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x2E

    test.op_SRA_HLaddr();
    REQUIRE( test.getByteAtAddress(0xC002) == 0x07 );
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x2D

    test.op_SRA_L();
    REQUIRE( test.getLowRegisterValue("HL") == 0x01);
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x2C

    test.op_SRA_H();
    REQUIRE( test.getHighRegisterValue("HL") == 0xE0);
    REQUIRE( test.getFlag('C') == 0);
    REQUIRE( test.getFlag('Z') == 0);

    // 0xCB 0x2B

    test.op_SRA_E();
    REQUIRE( test.getLowRegisterValue("DE") == 0xFE);
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x2A

    test.op_SRA_D();
    REQUIRE( test.getHighRegisterValue("DE") == 0xFF);
    REQUIRE( test.getFlag('C') == 0);

    // 0xCB 0x29

    test.op_SRA_C();
    REQUIRE( test.getLowRegisterValue("BC") == 0x00);
    REQUIRE( test.getFlag('C') == 0);
    REQUIRE( test.getFlag('Z') == 1);

    // 0xCB 0x28

    test.op_SRA_B();
    REQUIRE( test.getHighRegisterValue("BC") == 0x00);

    REQUIRE( test.getRegisterValue("BC") == 0x0000 );
    REQUIRE( test.getRegisterValue("DE") == 0xFFFE );
    REQUIRE( test.getRegisterValue("HL") == 0xE001 );
    REQUIRE( test.getHighRegisterValue("AF") == 0xFF );
    REQUIRE( test.getByteAtAddress(0xC002) == 0x07 );
}

TEST_CASE("Instruction 0xCB 0x3X Testing")
{
    cpu test;

    test.setRegisterValue("BC",0x8000);
    test.setRegisterValue("DE",0x7FFE);
    test.setRegisterValue("HL",0xC0FF);
    test.setHighRegisterValue("AF",0x1F);

    test.setByteAtAddress(0xC0FF, 0x87);

    test.setLowRegisterValue("AF",0x00);

    SECTION("SWAP Tests")
    {
        SECTION("SWAP B")
        {
            test.op_SWAP_B();
            REQUIRE(test.getHighRegisterValue("BC") == 0x08 );
            REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0 && test.getFlag('C') == 0));
            REQUIRE(test.getFlag('Z') == 0);
        }

        SECTION("SWAP C")
        {
            test.op_SWAP_C();
            REQUIRE(test.getLowRegisterValue("BC") == 0x00 );
            REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0 && test.getFlag('C') == 0));
            REQUIRE(test.getFlag('Z') == 1);
        }

        SECTION("SWAP D")
        {
            test.op_SWAP_D();
            REQUIRE(test.getHighRegisterValue("DE") == 0xF7 );
            REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0 && test.getFlag('C') == 0));
            REQUIRE(test.getFlag('Z') == 0);
        }

        SECTION("SWAP E")
        {
            test.op_SWAP_E();
            REQUIRE(test.getLowRegisterValue("DE") == 0xEF );
            REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0 && test.getFlag('C') == 0));
            REQUIRE(test.getFlag('Z') == 0 );
        }
 
        SECTION("SWAP H")
        {
            test.op_SWAP_H();
            REQUIRE(test.getHighRegisterValue("HL") == 0x0C );
            REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0 && test.getFlag('C') == 0));
            REQUIRE(test.getFlag('Z') == 0);
        }

        SECTION("SWAP L")
        {
            test.op_SWAP_L();
            REQUIRE(test.getLowRegisterValue("HL") == 0xFF );
            REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0 && test.getFlag('C') == 0));
            REQUIRE(test.getFlag('Z') == 0);
        }

        SECTION("SWAP A")
        {
            test.op_SWAP_A();
            REQUIRE(test.getHighRegisterValue("AF") == 0xF1 );
            REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0 && test.getFlag('C') == 0));
            REQUIRE(test.getFlag('Z') == 0);
        }

        SECTION("SWAP (HL)")
        {
            REQUIRE(test.getByteAtAddress(0xC0FF) == 0x87 );
            test.op_SWAP_HLaddr();
            REQUIRE(test.getByteAtAddress(0xC0FF) == 0x78 );
            REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0 && test.getFlag('C') == 0));
            REQUIRE(test.getFlag('Z') == 0);
        }
   }

   SECTION("SRL Instructions")
   {
       test.op_SRL_B();
       REQUIRE(test.getHighRegisterValue("BC") == 0x40);
       REQUIRE((test.getFlag('Z') == 0 && test.getFlag('C') == 0));
       REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0));

       test.op_SRL_C();
       REQUIRE(test.getLowRegisterValue("BC") == 0x00);
       REQUIRE((test.getFlag('Z') == 1 && test.getFlag('C') == 0));
       REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0));

       test.op_SRL_D();
       REQUIRE(test.getHighRegisterValue("DE") == 0x3F);
       REQUIRE((test.getFlag('Z') == 0 && test.getFlag('C') == 1));
       REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0));

       test.op_SRL_E();
       REQUIRE(test.getLowRegisterValue("DE") == 0x7F);
       REQUIRE((test.getFlag('Z') == 0 && test.getFlag('C') == 0));
       REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0));

       test.op_SRL_HLaddr();
       REQUIRE(test.getByteAtAddress(0xC0FF) == 0x43);
       REQUIRE((test.getFlag('Z') == 0 && test.getFlag('C') == 1));
       REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0));       

       test.op_SRL_H();
       REQUIRE(test.getHighRegisterValue("HL") == 0x60);
       REQUIRE((test.getFlag('Z') == 0 && test.getFlag('C') == 0));
       REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0));

       test.op_SRL_L();
       REQUIRE(test.getLowRegisterValue("HL") == 0x7F);
       REQUIRE((test.getFlag('Z') == 0 && test.getFlag('C') == 1));
       REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0));

       test.op_SRL_A();
       REQUIRE(test.getHighRegisterValue("AF") == 0x0F);
       REQUIRE((test.getFlag('Z') == 0 && test.getFlag('C') == 1));
       REQUIRE((test.getFlag('N') == 0 && test.getFlag('H') == 0));
   }
}

TEST_CASE("BIT Instructions")
{
    cpu test;

    SECTION("Register B")
    {
        test.setHighRegisterValue("BC",0b01010101);

        test.op_BIT_0B();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_1B();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_2B();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_3B();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_4B();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_5B();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_6B();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_7B();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));
    }

    SECTION("Register C")
    {
        test.setLowRegisterValue("BC",0b00000000);

        test.op_BIT_0C();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_1C();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_2C();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_3C();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_4C();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_5C();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_6C();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_7C();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));
    }

    SECTION("Register D")
    {
        test.setHighRegisterValue("DE",0b11111111);

        test.op_BIT_0D();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_1D();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_2D();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_3D();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_4D();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_5D();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_6D();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_7D();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));
    }

    SECTION("Register E")
    {
        test.setLowRegisterValue("DE",0b10101010);

        test.op_BIT_0E();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_1E();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_2E();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_3E();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_4E();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_5E();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_6E();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_7E();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));
    }

    SECTION("Register H")
    {
        test.setHighRegisterValue("HL",0b11110000);

        test.op_BIT_0H();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_1H();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_2H();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_3H();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_4H();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_5H();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_6H();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_7H();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));
    }

    SECTION("Register L")
    {
        test.setLowRegisterValue("HL",0b00001111);

        test.op_BIT_0L();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_1L();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_2L();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_3L();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_4L();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_5L();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_6L();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_7L();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));
    }

    SECTION("Register A")
    {
        test.setHighRegisterValue("AF",0b00110011);

        test.op_BIT_0A();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_1A();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_2A();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_3A();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_4A();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_5A();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_6A();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_7A();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));
    }

    SECTION("(HL)")
    {
        test.setRegisterValue("HL",0xC010);
        test.setByteAtAddress(0xC010, 0b11001100);

        test.op_BIT_0HLaddr();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_1HLaddr();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_2HLaddr();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_3HLaddr();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_4HLaddr();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_5HLaddr();
        REQUIRE((test.getFlag('Z') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_6HLaddr();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));

        test.op_BIT_7HLaddr();
        REQUIRE((test.getFlag('Z') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 1));
    }
}

TEST_CASE("SET Instructions")
{
    cpu test;

    SECTION("Register B")
    {
        test.setHighRegisterValue("BC",0b00000000);

        test.op_SET_0B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b00000001);

        test.op_SET_1B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b00000011);

        test.op_SET_2B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b00000111);

        test.op_SET_3B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b00001111);

        test.op_SET_4B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b00011111);

        test.op_SET_5B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b00111111);

        test.op_SET_6B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b01111111);

        test.op_SET_7B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b11111111);
    }

    SECTION("Register C")
    {
        test.setLowRegisterValue("BC",0b00000000);

        test.op_SET_7C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b10000000);

        test.op_SET_6C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b11000000);

        test.op_SET_5C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b11100000);

        test.op_SET_4C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b11110000);

        test.op_SET_3C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b11111000);

        test.op_SET_2C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b11111100);

        test.op_SET_1C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b11111110);

        test.op_SET_0C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b11111111);
    }

    SECTION("Register D")
    {
        test.setHighRegisterValue("DE",0b01010101);

        test.op_SET_0D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b01010101);

        test.op_SET_1D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b01010111);

        test.op_SET_2D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b01010111);

        test.op_SET_3D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b01011111);

        test.op_SET_4D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b01011111);

        test.op_SET_5D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b01111111);

        test.op_SET_6D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b01111111);

        test.op_SET_7D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b11111111);
    }

    SECTION("Register E")
    {
        test.setLowRegisterValue("DE",0b01010101);

        test.op_SET_7E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b11010101);

        test.op_SET_6E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b11010101);

        test.op_SET_5E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b11110101);

        test.op_SET_4E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b11110101);

        test.op_SET_3E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b11111101);

        test.op_SET_2E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b11111101);

        test.op_SET_1E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b11111111);

        test.op_SET_0E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b11111111);
    }

    SECTION("Register H")
    {
        test.setHighRegisterValue("HL",0b01001001);

        test.op_SET_0H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b01001001);

        test.op_SET_1H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b01001011);

        test.op_SET_2H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b01001111);

        test.op_SET_3H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b01001111);

        test.op_SET_4H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b01011111);

        test.op_SET_5H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b01111111);

        test.op_SET_6H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b01111111);

        test.op_SET_7H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b11111111);
    }

    SECTION("Register L")
    {
        test.setLowRegisterValue("HL",0b01001001);

        test.op_SET_7L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b11001001);

        test.op_SET_6L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b11001001);

        test.op_SET_5L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b11101001);

        test.op_SET_4L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b11111001);

        test.op_SET_3L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b11111001);

        test.op_SET_2L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b11111101);

        test.op_SET_1L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b11111111);

        test.op_SET_0L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b11111111);
    }

    SECTION("Register A")
    {
        test.setHighRegisterValue("AF",0b00000000);

        test.op_SET_0A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b00000001);

        test.op_SET_1A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b00000011);

        test.op_SET_2A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b00000111);

        test.op_SET_3A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b00001111);

        test.op_SET_4A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b00011111);

        test.op_SET_5A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b00111111);

        test.op_SET_6A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b01111111);

        test.op_SET_7A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b11111111);
    }

    SECTION("(HL)")
    {
        test.setRegisterValue("HL",0xC010);
        test.setByteAtAddress(0xC010, 0b00000000);
        
        test.op_SET_2HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b00000100);

        test.op_SET_7HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b10000100);

        test.op_SET_5HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b10100100);

        test.op_SET_4HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b10110100);

        test.op_SET_0HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b10110101);

        test.op_SET_1HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b10110111);

        test.op_SET_6HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b11110111);

        test.op_SET_3HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b11111111);

    }
}

TEST_CASE("RESET Instructions")
{
    cpu test;

    SECTION("Register B")
    {
        test.setHighRegisterValue("BC",0b11111111);

        test.op_RES_0B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b11111110);

        test.op_RES_1B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b11111100);

        test.op_RES_2B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b11111000);

        test.op_RES_3B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b11110000);

        test.op_RES_4B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b11100000);

        test.op_RES_5B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b11000000);

        test.op_RES_6B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b10000000);

        test.op_RES_7B();
        REQUIRE(test.getHighRegisterValue("BC") == 0b00000000);
    }

    SECTION("Register C")
    {
        test.setLowRegisterValue("BC",0b11111111);

        test.op_RES_7C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b01111111);

        test.op_RES_6C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b00111111);

        test.op_RES_5C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b00011111);

        test.op_RES_4C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b00001111);

        test.op_RES_3C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b00000111);

        test.op_RES_2C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b00000011);

        test.op_RES_1C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b00000001);

        test.op_RES_0C();
        REQUIRE(test.getLowRegisterValue("BC") == 0b00000000);
    }

    SECTION("Register D")
    {
        test.setHighRegisterValue("DE",0b01010101);

        test.op_RES_0D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b01010100);

        test.op_RES_1D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b01010100);

        test.op_RES_2D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b01010000);

        test.op_RES_3D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b01010000);

        test.op_RES_4D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b01000000);

        test.op_RES_5D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b01000000);

        test.op_RES_6D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b00000000);

        test.op_RES_7D();
        REQUIRE(test.getHighRegisterValue("DE") == 0b00000000);
    }

    SECTION("Register E")
    {
        test.setLowRegisterValue("DE",0b01010101);

        test.op_RES_7E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b01010101);

        test.op_RES_6E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b00010101);

        test.op_RES_5E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b00010101);

        test.op_RES_4E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b00000101);

        test.op_RES_3E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b00000101);

        test.op_RES_2E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b00000001);

        test.op_RES_1E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b00000001);

        test.op_RES_0E();
        REQUIRE(test.getLowRegisterValue("DE") == 0b00000000);
    }

    SECTION("Register H")
    {
        test.setHighRegisterValue("HL",0b01001001);

        test.op_RES_0H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b01001000);

        test.op_RES_1H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b01001000);

        test.op_RES_2H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b01001000);

        test.op_RES_3H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b01000000);

        test.op_RES_4H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b01000000);

        test.op_RES_5H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b01000000);

        test.op_RES_6H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b00000000);

        test.op_RES_7H();
        REQUIRE(test.getHighRegisterValue("HL") == 0b00000000);
    }

    SECTION("Register L")
    {
        test.setLowRegisterValue("HL",0b01001001);

        test.op_RES_7L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b01001001);

        test.op_RES_6L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b00001001);

        test.op_RES_5L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b00001001);

        test.op_RES_4L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b00001001);

        test.op_RES_3L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b00000001);

        test.op_RES_2L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b00000001);

        test.op_RES_1L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b00000001);

        test.op_RES_0L();
        REQUIRE(test.getLowRegisterValue("HL") == 0b00000000);
    }

    SECTION("Register A")
    {
        test.setHighRegisterValue("AF",0b11111111);

        test.op_RES_0A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b11111110);

        test.op_RES_1A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b11111100);

        test.op_RES_2A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b11111000);

        test.op_RES_3A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b11110000);

        test.op_RES_4A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b11100000);

        test.op_RES_5A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b11000000);

        test.op_RES_6A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b10000000);

        test.op_RES_7A();
        REQUIRE(test.getHighRegisterValue("AF") == 0b00000000);
    }

    SECTION("(HL)")
    {
        test.setRegisterValue("HL",0xC010);
        test.setByteAtAddress(0xC010, 0b11111111);
        
        test.op_RES_2HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b11111011);

        test.op_RES_7HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b01111011);

        test.op_RES_5HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b01011011);

        test.op_RES_4HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b01001011);

        test.op_RES_0HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b01001010);

        test.op_RES_1HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b01001000);

        test.op_RES_6HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b00001000);

        test.op_RES_3HLaddr();
        REQUIRE(test.getByteAtAddress(0xC010) == 0b00000000);

    }
}