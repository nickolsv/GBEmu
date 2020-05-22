#include "../header/catch.hpp"
#include "../header/memory.hh"

TEST_CASE("Reads & Writes")
{
    memory mem;

    mem.writeToAddress(0x1234,0x55);
    mem.writeToAddress(0x4321,0x44);

    REQUIRE( mem.readAddress(0x1234) == 0x55 );
    REQUIRE( mem.readAddress(0x4321) == 0x44 );

    mem.writeToAddress(0x1234,0xFF);

    REQUIRE( mem.readAddress(0x1234) == 0xFF );
}