#include "../header/cpu.hh"

int main(int argc, char const *argv[])
{
    cpu *CPU = new cpu();
    CPU->runFrame();
    delete CPU;
    return 0;
}
