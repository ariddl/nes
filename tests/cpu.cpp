#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

struct CPU {
     
    int stack_pointer; // stack pointer  valid from [0 - 256]
    int stack[256]; // the stack
    int status_register[8]; // status registers
    int PC; // program counter
    int acc; // accumulator
    int y; // y register
    int x; // x register 
  
};


int main(int argc, char* argv[])
{
    // Read data from file: 
    std::ifstream input(argv[1], std::ios::binary);
    std::vector<char> bytes(
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>()));
    input.close();

    std::cout << bytes[0];
    CPU cpu; 
    cpu.stack_pointer = 0;
    std::cout << cpu.stack_pointer; 

    for (int i = 0; i < bytes.size(); i++)
    {
        // do stuff 
    }
    return 0;
}

