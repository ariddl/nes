#include "cpu.h"

const cpu::instruction_handler cpu::s_handlers[4][8] = {
    {
    },
    {
        &cpu::ora,
        &cpu::and,
    },
    {

    },
    {

    }
};

cpu::cpu(const std::vector<u8> &data) 
    : m_registers{}
    , m_stack{}
    , m_code(data) {
        reset();

    //u8 opcode=0;
    //(this->*s_handlers[opcode & 0xff][opcode >> 20])((opcode >> 8) & 0xfff);
}

void cpu::reset() {
    m_registers.S = stack_size - 1; // $FF
}