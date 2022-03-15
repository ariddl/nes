#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "opcodes.h"

struct CPU 
{
    int stack_pointer; // stack pointer  valid from [0 - 256]
    static const int stack_size = 256; // stack size. should stay at 256. 
    int stack[stack_size]; // the stack
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

    CPU cpu; 


    // read through the binary file and perform operations
    bool not_done = true;
    int current_byte = 0;
    bool op_code = true;

    while(not_done)
    {    
        std::cout << "ind: " << current_byte;
        if(op_code)
        {
            std::cout << std::endl <<  "opcode: " << (int)(bytes[current_byte]) + 256 << std::endl;
            op_code = false;
        }
        else
            std::cout << std::endl <<  "addr: " << (int)(bytes[current_byte]) << std::endl;

        // need some way to dynamically end.
        if(current_byte == bytes.size() - 1) // for now treat it like a for loop. 
            not_done = false;

        current_byte++;
    }


    for (int i = 0; i < bytes.size(); i++) // For some reason the opcodes are fff.. (2s comp.)
    {
    }
    return 0;
}

