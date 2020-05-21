#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../header/catch.hpp"

// By creating a dedicated source file that only contains the preprocessor directives
// for including the Catch2 Library and thus having separate test case files,
// we don't have to recompile the whole library when editing the test case source files
// therefore cutting down on the project compilation time