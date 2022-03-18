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
		// TODO: NES Specific instructions?
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

cpu::cpu(const std::vector<u8> &data) 
    : m_registers{}
    , m_stack{}
    , m_code(data) {
    
	reset();
}

void cpu::reset() {
    m_registers.S = stack_size - 1; // $FF
}

bool cpu::bit(int addrmode) {
	return false; // stub
}

bool cpu::jmp(int addrmode) {
	return false; // stub
}

bool cpu::jmp_abs(int addrmode) {
	return false; // stub
}

bool cpu::sty(int addrmode) {
	return false; // stub
}

bool cpu::ldy(int addrmode) {
	return false; // stub
}

bool cpu::cpy(int addrmode) {
	return false; // stub
}

bool cpu::cpx(int addrmode) {
	return false; // stub
}

// cc == 01
bool cpu::ora(int addrmode) {
	return false; // stub
}

bool cpu::and(int addrmode) {
	return false; // stub
}

bool cpu::eor(int addrmode) {
	return false; // stub
}

bool cpu::adc(int addrmode) {
	return false; // stub
}

bool cpu::sta(int addrmode) {
	return false; // stub
}

bool cpu::lda(int addrmode) {
	return false; // stub
}

bool cpu::cmp(int addrmode) {
	return false; // stub
}

bool cpu::sbc(int addrmode) {
	return false; // stub
}


// cc == 10
bool cpu::asl(int addrmode) {
	return false; // stub
}

bool cpu::rol(int addrmode) {
	return false; // stub
}

bool cpu::lsr(int addrmode) {
	return false; // stub
}

bool cpu::ror(int addrmode) {
	return false; // stub
}

bool cpu::stx(int addrmode) {
	return false; // stub
}

bool cpu::ldx(int addrmode) {
	return false; // stub
}

bool cpu::dec(int addrmode) {
	return false; // stub
}

bool cpu::inc(int addrmode) {
	return false; // stub
}