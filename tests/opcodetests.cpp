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

TEST_CASE("Instruction 0x2X Testing")
{
    cpu test;

    test.setRegisterValue("PC",0xC001);
    test.setByteAtAddress(0xC001,0x02);
    test.setByteAtAddress(0xC002,0xC0);
    test.setByteAtAddress(0xC003,0x56);
    test.setByteAtAddress(0xC004,0xD8);
    test.setLowRegisterValue("AF",0x00);

    
    // 0x21

    test.op_LD_HLnn();
    REQUIRE( test.getRegisterValue("HL") == 0xC002 );

    // 0X22

    test.setHighRegisterValue("AF",0xEE);
    test.op_LD_HLincA();
    REQUIRE( test.getByteAtAddress(0xC002) == 0xEE );
    REQUIRE( test.getRegisterValue("HL") == 0xC003 );

    // 0x23

    test.op_INC_HL();
    REQUIRE( test.getRegisterValue("HL") == 0xC004 );

    test.setRegisterValue("HL",0xFFFF);
    test.op_INC_HL();
    REQUIRE( test.getRegisterValue("HL") == 0x0000 );

    // 0X24

    REQUIRE( (test.getFlag('C') == 0 && test.getFlag('H') == 0 && test.getFlag('N') == 0 && test.getFlag('Z') == 0 ));

    test.setHighRegisterValue("HL", 0b11011111);
    test.op_INC_H();
    REQUIRE( test.getHighRegisterValue("HL") == 0b11100000 );
    REQUIRE( (test.getFlag('H') == 1 ));

    test.setHighRegisterValue("HL", 0xFF);
    test.op_INC_H();
    REQUIRE( (test.getFlag('Z') == 1 && test.getFlag('H') == 1  && test.getFlag('N') == 0));

    // 0x25

    test.op_DEC_H();
    REQUIRE( (test.getFlag('N') == 1 && test.getFlag('Z') == 0 && test.getFlag('H') == 1) );
    REQUIRE(test.getHighRegisterValue("HL") == 0xFF);

    // 0x26

    test.setRegisterValue("PC",0xC002);
    test.op_LD_Hn();
    REQUIRE(test.getHighRegisterValue("HL") == 0xEE);
    REQUIRE(test.getRegisterValue("PC") == 0xC003);

    // 0x29

    test.setRegisterValue("HL",0x0000);
    test.setRegisterValue("DE",0xFFFF);
    test.op_ADD_HLDE();
    REQUIRE( test.getRegisterValue("HL") == 0xFFFF);
    REQUIRE( ( test.getFlag('C') == 0 && test.getFlag('H') == 0 && test.getFlag('N') == 0 ));

    test.op_ADD_HLDE();
    REQUIRE( test.getRegisterValue("HL") == 0xFFFE);
    REQUIRE( ( test.getFlag('C') == 1 && test.getFlag('H') == 1 && test.getFlag('N') == 0 ));

    // 0x2A

    test.setByteAtAddress(0xD234, 0xDD);
    test.setRegisterValue("HL",0xD234);
    test.op_LD_AHLdec();
    REQUIRE( test.getHighRegisterValue("AF") == 0xDD );
    REQUIRE( test.getRegisterValue("HL") == 0xD233);

    // 0x2B

    test.op_DEC_HL();
    REQUIRE( test.getRegisterValue("HL") == 0xD232 );

    test.setRegisterValue("HL",0x0000);
    test.op_DEC_HL();
    REQUIRE( test.getRegisterValue("HL") == 0xFFFF );

    // 0x2C

    test.setLowRegisterValue("HL", 0xFF);
    test.op_INC_L();
    REQUIRE( test.getLowRegisterValue("HL") == 0x00 );
    REQUIRE( (test.getFlag('H') == 1 ));

    test.setLowRegisterValue("HL", 0x0F);
    test.op_INC_L();
    REQUIRE( (test.getFlag('Z') == 0 && test.getFlag('H') == 1  && test.getFlag('N') == 0));

    // 0x2D

    test.op_DEC_L();
    REQUIRE( (test.getFlag('N') == 1 && test.getFlag('Z') == 0 && test.getFlag('H') == 1) );
    REQUIRE(test.getLowRegisterValue("HL") == 0x0F);

    // 0x2E

    test.setRegisterValue("PC",0xC002);
    test.op_LD_Ln();
    REQUIRE(test.getLowRegisterValue("HL") == 0xEE);
    REQUIRE(test.getRegisterValue("PC") == 0xC003);

    // 0x2F

    test.setHighRegisterValue("AF",0b10101010);
    test.op_CPL();
    REQUIRE(test.getHighRegisterValue("AF") == 0b01010101);
    REQUIRE( (test.getFlag('N') == 1 && test.getFlag('H') == 1));

    test.setHighRegisterValue("AF",0xFF);
    test.op_CPL();
    REQUIRE(test.getHighRegisterValue("AF") == 0x00);

    // 0x28

    test.setRegisterValue("PC",0xC00E);
    test.setByteAtAddress(0xC00E,0x00);
    test.setByteAtAddress(0xC00F,0xF0);
    test.resetFlag('Z');

    test.op_JR_Zn();
    REQUIRE(test.getRegisterValue("PC") == 0xC00F);
    test.op_JR_Zn();
    REQUIRE(test.getRegisterValue("PC") == 0xC010);

    test.setRegisterValue("PC",0xC00E);
    test.setFlag('Z');

    test.op_JR_Zn();
    REQUIRE(test.getRegisterValue("PC") == 0xC00F);
    test.op_JR_Zn();
    REQUIRE(test.getRegisterValue("PC") == 0xC000);

    // 0x20

    test.setRegisterValue("PC",0xC00E);
    test.setFlag('Z');

    test.op_JR_NZn();
    REQUIRE(test.getRegisterValue("PC") == 0xC00F);
    test.op_JR_NZn();
    REQUIRE(test.getRegisterValue("PC") == 0xC010);

    test.setRegisterValue("PC",0xC00E);
    test.resetFlag('Z');

    test.op_JR_NZn();
    REQUIRE(test.getRegisterValue("PC") == 0xC00F);
    test.op_JR_NZn();
    REQUIRE(test.getRegisterValue("PC") == 0xC000);
}

TEST_CASE("Instruction 0x3X Testing")
{
    cpu test;

    test.setRegisterValue("PC",0xC001);
    test.setByteAtAddress(0xC001,0x02);
    test.setByteAtAddress(0xC002,0xC0);
    test.setByteAtAddress(0xC003,0x56);
    test.setByteAtAddress(0xC004,0xD8);
    test.setLowRegisterValue("AF",0x00);

    
    // 0x31

    test.op_LD_SPnn();
    REQUIRE( test.getRegisterValue("SP") == 0xC002 );

    // 0X32

    test.setHighRegisterValue("AF",0xEE);
    test.setRegisterValue("HL",0xC002);
    test.op_LD_HLdecA();
    REQUIRE( test.getByteAtAddress(0xC002) == 0xEE );
    REQUIRE( test.getRegisterValue("HL") == 0xC001 );

    // 0x33

    test.op_INC_SP();
    REQUIRE( test.getRegisterValue("SP") == 0xC003 );

    test.setRegisterValue("SP",0xFFFF);
    test.op_INC_SP();
    REQUIRE( test.getRegisterValue("SP") == 0x0000 );

    // 0X34

    test.op_INC_HLaddr();
    REQUIRE(test.getByteAtAddress(0xc001) == 0x03);

    // 0x35

    test.op_DEC_HLaddr();
    REQUIRE(test.getByteAtAddress(0xc001) == 0x02);

    // 0x36

    test.setRegisterValue("PC",0xC002);
    test.setRegisterValue("HL",0xC001);
    test.setByteAtAddress(0xC002,0xC0);
    test.op_LD_HLaddrn();
    REQUIRE(test.getByteAtAddress(0xC001) == 0xC0);

    // 0x37

    test.resetFlag('C');
    test.op_SCF();
    REQUIRE((test.getFlag('C') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 0));

    // 0x39

    test.setRegisterValue("SP",0xFFFF);
    test.setRegisterValue("HL",0x0000);
    test.op_ADD_HLSP();
    REQUIRE( test.getRegisterValue("HL") == 0xFFFF);
    REQUIRE( ( test.getFlag('C') == 0 && test.getFlag('H') == 0 && test.getFlag('N') == 0 ));

    test.op_ADD_HLSP();
    REQUIRE( test.getRegisterValue("HL") == 0xFFFE);
    REQUIRE( ( test.getFlag('C') == 1 && test.getFlag('H') == 1 && test.getFlag('N') == 0 ));

    // 0x3A

    test.setByteAtAddress(0xFFFE,0xCC);
    test.op_LD_AHLdec();
    REQUIRE( test.getRegisterValue("HL") == 0xFFFD );
    REQUIRE( test.getHighRegisterValue("AF") == 0xCC );

    // 0x3B

    test.op_DEC_SP();
    REQUIRE(test.getRegisterValue("SP") == 0xFFFE);

    // 0x3C

    test.setHighRegisterValue("AF", 0xFF);
    test.op_INC_A();
    REQUIRE( test.getHighRegisterValue("AF") == 0x00 );
    REQUIRE( (test.getFlag('H') == 1 ));

    test.setHighRegisterValue("AF", 0x0F);
    test.op_INC_A();
    REQUIRE( (test.getFlag('Z') == 0 && test.getFlag('H') == 1  && test.getFlag('N') == 0));

    // 0x3D

    test.op_DEC_A();
    REQUIRE( (test.getFlag('N') == 1 && test.getFlag('Z') == 0 && test.getFlag('H') == 1) );
    REQUIRE(test.getHighRegisterValue("AF") == 0x0F);

    // 0x3E

    test.setByteAtAddress(0xC010, 0xBB);
    test.setRegisterValue("PC",0xC010);
    test.op_LD_An();
    REQUIRE(test.getHighRegisterValue("AF") == 0xBB);

    // 0x3F

    test.setFlag('C');
    test.op_CCF();
    REQUIRE((test.getFlag('C') == 0 && test.getFlag('N') == 0 && test.getFlag('H') == 0 ));
    
    test.resetFlag('C');
    test.op_CCF();
    REQUIRE((test.getFlag('C') == 1 && test.getFlag('N') == 0 && test.getFlag('H') == 0 ));

    // 0x38

    test.setRegisterValue("PC",0xC00E);
    test.setByteAtAddress(0xC00E,0x00);
    test.setByteAtAddress(0xC00F,0xF0);
    test.resetFlag('C');

    test.op_JR_Cn();
    REQUIRE(test.getRegisterValue("PC") == 0xC00F);
    test.op_JR_Cn();
    REQUIRE(test.getRegisterValue("PC") == 0xC010);

    test.setRegisterValue("PC",0xC00E);
    test.setFlag('C');

    test.op_JR_Cn();
    REQUIRE(test.getRegisterValue("PC") == 0xC00F);
    test.op_JR_Cn();
    REQUIRE(test.getRegisterValue("PC") == 0xC000);

    // 0x30

    test.setRegisterValue("PC",0xC00E);
    test.setFlag('C');

    test.op_JR_NCn();
    REQUIRE(test.getRegisterValue("PC") == 0xC00F);
    test.op_JR_NCn();
    REQUIRE(test.getRegisterValue("PC") == 0xC010);

    test.setRegisterValue("PC",0xC00E);
    test.resetFlag('C');

    test.op_JR_NCn();
    REQUIRE(test.getRegisterValue("PC") == 0xC00F);
    test.op_JR_NCn();
    REQUIRE(test.getRegisterValue("PC") == 0xC000);
}

TEST_CASE("Register8 Load Tests")
{
    cpu test;

    test.setRegisterValue("BC", 0x1122);
    test.setRegisterValue("DE", 0x3344);
    test.setRegisterValue("HL", 0x5566);
    test.setHighRegisterValue("AF", 0xFF);

    SECTION("Load to B")
    {
        test.op_LD_BB();
        REQUIRE( test.getHighRegisterValue("BC") == 0x11);

        test.op_LD_BC();
        REQUIRE( test.getHighRegisterValue("BC") == 0x22);

        test.op_LD_BD();
        REQUIRE( test.getHighRegisterValue("BC") == 0x33);

        test.op_LD_BE();
        REQUIRE( test.getHighRegisterValue("BC") == 0x44);

        test.op_LD_BH();
        REQUIRE( test.getHighRegisterValue("BC") == 0x55);

        test.op_LD_BL();
        REQUIRE( test.getHighRegisterValue("BC") == 0x66);

        test.op_LD_BA();
        REQUIRE( test.getHighRegisterValue("BC") == 0xFF);
    }

    SECTION("Load to C")
    {
        test.op_LD_CC();
        REQUIRE( test.getLowRegisterValue("BC") == 0x22);

        test.op_LD_CB();
        REQUIRE( test.getLowRegisterValue("BC") == 0x11);

        test.op_LD_CD();
        REQUIRE( test.getLowRegisterValue("BC") == 0x33);

        test.op_LD_CE();
        REQUIRE( test.getLowRegisterValue("BC") == 0x44);

        test.op_LD_CH();
        REQUIRE( test.getLowRegisterValue("BC") == 0x55);

        test.op_LD_CL();
        REQUIRE( test.getLowRegisterValue("BC") == 0x66);

        test.op_LD_CA();
        REQUIRE( test.getLowRegisterValue("BC") == 0xFF);
    }

    SECTION("Load to D")
    {
        test.op_LD_DD();
        REQUIRE( test.getHighRegisterValue("DE") == 0x33);

        test.op_LD_DB();
        REQUIRE( test.getHighRegisterValue("DE") == 0x11);

        test.op_LD_DC();
        REQUIRE( test.getHighRegisterValue("DE") == 0x22);

        test.op_LD_DE();
        REQUIRE( test.getHighRegisterValue("DE") == 0x44);

        test.op_LD_DH();
        REQUIRE( test.getHighRegisterValue("DE") == 0x55);

        test.op_LD_DL();
        REQUIRE( test.getHighRegisterValue("DE") == 0x66);

        test.op_LD_DA();
        REQUIRE( test.getHighRegisterValue("DE") == 0xFF);
    }

    SECTION("Load to E")
    {
        test.op_LD_EE();
        REQUIRE( test.getLowRegisterValue("DE") == 0x44);

        test.op_LD_EB();
        REQUIRE( test.getLowRegisterValue("DE") == 0x11);

        test.op_LD_EC();
        REQUIRE( test.getLowRegisterValue("DE") == 0x22);

        test.op_LD_ED();
        REQUIRE( test.getLowRegisterValue("DE") == 0x33);

        test.op_LD_EH();
        REQUIRE( test.getLowRegisterValue("DE") == 0x55);

        test.op_LD_EL();
        REQUIRE( test.getLowRegisterValue("DE") == 0x66);

        test.op_LD_EA();
        REQUIRE( test.getLowRegisterValue("DE") == 0xFF);
    }

    SECTION("Load to H")
    {
        test.op_LD_HH();
        REQUIRE( test.getHighRegisterValue("HL") == 0x55);

        test.op_LD_HB();
        REQUIRE( test.getHighRegisterValue("HL") == 0x11);

        test.op_LD_HC();
        REQUIRE( test.getHighRegisterValue("HL") == 0x22);

        test.op_LD_HD();
        REQUIRE( test.getHighRegisterValue("HL") == 0x33);

        test.op_LD_HE();
        REQUIRE( test.getHighRegisterValue("HL") == 0x44);

        test.op_LD_HL();
        REQUIRE( test.getHighRegisterValue("HL") == 0x66);

        test.op_LD_HA();
        REQUIRE( test.getHighRegisterValue("HL") == 0xFF);
    }

    SECTION("Load to L")
    {
        test.op_LD_LL();
        REQUIRE( test.getLowRegisterValue("HL") == 0x66);

        test.op_LD_LB();
        REQUIRE( test.getLowRegisterValue("HL") == 0x11);

        test.op_LD_LC();
        REQUIRE( test.getLowRegisterValue("HL") == 0x22);

        test.op_LD_LD();
        REQUIRE( test.getLowRegisterValue("HL") == 0x33);

        test.op_LD_LE();
        REQUIRE( test.getLowRegisterValue("HL") == 0x44);

        test.op_LD_LH();
        REQUIRE( test.getLowRegisterValue("HL") == 0x55);

        test.op_LD_LA();
        REQUIRE( test.getLowRegisterValue("HL") == 0xFF);
    }

    SECTION("Load to A")
    {
        test.op_LD_AA();
        REQUIRE( test.getHighRegisterValue("AF") == 0xFF);
        
        test.op_LD_AB();
        REQUIRE( test.getHighRegisterValue("AF") == 0x11);

        test.op_LD_AC();
        REQUIRE( test.getHighRegisterValue("AF") == 0x22);

        test.op_LD_AD();
        REQUIRE( test.getHighRegisterValue("AF") == 0x33);

        test.op_LD_AE();
        REQUIRE( test.getHighRegisterValue("AF") == 0x44);

        test.op_LD_AH();
        REQUIRE( test.getHighRegisterValue("AF") == 0x55);

        test.op_LD_AL();
        REQUIRE( test.getHighRegisterValue("AF") == 0x66);
    }
}

TEST_CASE("(HL) Load Tests")
{
    cpu test;

    test.setRegisterValue("BC", 0x1122);
    test.setRegisterValue("DE", 0x3344);
    test.setRegisterValue("HL", 0xCCDD);
    test.setHighRegisterValue("AF", 0xFF);

    test.setByteAtAddress(0xCCDD, 0xAB);

    SECTION("Loads to (HL)")
    {
        test.op_LD_HLB();
        REQUIRE(test.getByteAtAddress(0xCCDD) == 0x11);

        test.op_LD_HLC();
        REQUIRE(test.getByteAtAddress(0xCCDD) == 0x22);

        test.op_LD_HLD();
        REQUIRE(test.getByteAtAddress(0xCCDD) == 0x33);

        test.op_LD_HLE();
        REQUIRE(test.getByteAtAddress(0xCCDD) == 0x44);

        test.op_LD_HLH();
        REQUIRE(test.getByteAtAddress(0xCCDD) == 0xCC);

        test.op_LD_HLL();
        REQUIRE(test.getByteAtAddress(0xCCDD) == 0xDD);

        test.op_LD_HLA();
        REQUIRE(test.getByteAtAddress(0xCCDD) == 0xFF);
    }

    SECTION("Loads from (HL)")
    {
        test.op_LD_BHL();
        test.op_LD_CHL();
        REQUIRE( test.getRegisterValue("BC") == 0xABAB );

        test.op_LD_DHL();
        test.op_LD_EHL();
        REQUIRE( test.getRegisterValue("BC") == 0xABAB );

        test.op_LD_HHL();
        test.op_LD_LHL();
        REQUIRE( test.getRegisterValue("BC") == 0xABAB );

        test.op_LD_AHL();
        REQUIRE( test.getHighRegisterValue("BC") == 0xAB );

    }
}
