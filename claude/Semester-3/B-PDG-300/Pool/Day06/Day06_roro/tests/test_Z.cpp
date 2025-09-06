/*
** EPITECH PROJECT, 2025
** Day06 - Tests
** File description:
** Unit tests for Z program
*/

#include <criterion/criterion.h>
#include <cstdlib>
#include <string>

// Helper function to run Z program and capture output
std::string run_Z(const std::string &input) {
    std::string command = "./ex00/Z \"" + input + "\"";
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe) return "";
    
    char buffer[128];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }
    pclose(pipe);
    
    // Remove trailing newline if present
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    
    return result;
}

Test(Z, valid_hex_id)
{
    std::string result = run_Z("0x42242112");
    cr_assert_str_eq(result.c_str(), "z");
}

Test(Z, invalid_id)
{
    std::string result = run_Z("invalid_ID");
    cr_assert_str_eq(result.c_str(), "z");
}

Test(Z, another_valid_hex)
{
    std::string result = run_Z("0xABCDEF");
    cr_assert_str_eq(result.c_str(), "z");
}

Test(Z, empty_hex)
{
    std::string result = run_Z("0x");
    cr_assert_str_eq(result.c_str(), "z");
}