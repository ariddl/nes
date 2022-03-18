#include "cpu.h"

const cpu::instruction_handler cpu::s_handlers[4][8] = {
    {
		nullptr,
		&cpu::bit,
		&cpu::jmp,
		&cpu::jmp_abs,
		&cpu::sty,
		&cpu::ldy,
		&cpu::cpy,
		&cpu::cpx
    },
    {
		&cpu::ora,
		&cpu::and,
		&cpu::eor,
		&cpu::adc,
		&cpu::sta,
		&cpu::lda,
		&cpu::cmp,
		&cpu::sbc
    },
    {
		&cpu::asl,
		&cpu::rol,
		&cpu::lsr,
		&cpu::ror,
		&cpu::stx,
		&cpu::ldx,
		&cpu::dec,
		&cpu::inc
    },
    {
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		nullptr
    }
};

bool cpu::ora(int addrmode)
{

}


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