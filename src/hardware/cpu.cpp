#include "cpu.h"
#include "system.h"

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
		&cpu::AND,
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

cpu::cpu(system *sys) 
    : m_registers{}
    , m_stack{}
	, m_system(sys) {
	reset();
}

void cpu::reset() {
    m_registers.S = stack_size - 1; // $FF
}

bool cpu::execute_next() {
	// We need an actual clock.
	// For now this will get us by to test individual instructions.
	if (m_registers.PC >= m_code.size())
		return false;
	
	// The instruction handler will move PC as necessary for additional bytes.
	// Opcodes are in the format: aaabbbcc. aaa = group, bbb = addr mode, cc = group.
	u8 opcode = m_code[m_registers.PC++];
	u8 operation = (opcode >> 5) & 0x7;
	u8 addrmode = (opcode >> 2) & 0x7;
	u8 tab = opcode & 0x3;
	if (tab >= 4 || operation >= 8) // TODO: Constants!
		return false;
	return (this->*s_handlers[tab][operation])(addrmode);
}

// cc == 00
bool cpu::bit(int addrmode) {
	// Currently we are making the assumption that each instruction belongs to only
	// one group and thus can only have one set of addressing modes. Need to confirm.
	// So far it looks like this is the case.

	// Each addressing mode takes its own number of cycles to process.
	// For a full breakdown for each instruction, see:
	// https://www.masswerk.at/6502/6502_instruction_set.html#layout
	
	// Timing is very important in emulation and we must be sure we are cycle-to-cycle
	// accurate. More thought must go into this before we continue this implementation.
	switch (addrmode) {
		case addrmode_cc00_immediate: break;
		case addrmode_cc00_zero_page: break;
		case addrmode_cc00_absolute: break;
		case addrmode_cc00_zero_page_x: break;
		case addrmode_cc00_absolute_x: break;
		default: break;
	}
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

bool cpu::AND(int addrmode) {
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