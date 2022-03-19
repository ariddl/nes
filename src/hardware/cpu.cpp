#include "cpu.h"
#include "system.h"

const cpu::instruction_handler cpu::s_handlers[4][8] = {
    {
		nullptr,
		&cpu::BIT,
		&cpu::JMP,
		&cpu::JMPABS,
		&cpu::STY,
		&cpu::LDY,
		&cpu::CPY,
		&cpu::CPX
    },
    {
		&cpu::ORA,
		&cpu::AND,
		&cpu::EOR,
		&cpu::ADC,
		&cpu::STA,
		&cpu::LDA,
		&cpu::CMP,
		&cpu::SBC
    },
    {
		&cpu::ASL,
		&cpu::ROL,
		&cpu::LSR,
		&cpu::ROR,
		&cpu::STX,
		&cpu::LDX,
		&cpu::DEC,
		&cpu::INC
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
bool cpu::BIT(int addrmode) {
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

bool cpu::JMP(int addrmode) {
	return false; // stub
}

bool cpu::JMPABS(int addrmode) {
	return false; // stub
}

bool cpu::STY(int addrmode) {
	return false; // stub
}

bool cpu::LDY(int addrmode) {
	return false; // stub
}

bool cpu::CPY(int addrmode) {
	return false; // stub
}

bool cpu::CPX(int addrmode) {
	return false; // stub
}

// cc == 01
bool cpu::ORA(int addrmode) {
	return false; // stub
}

bool cpu::AND(int addrmode) {
	return false; // stub
}

bool cpu::EOR(int addrmode) {
	return false; // stub
}

bool cpu::ADC(int addrmode) {
	return false; // stub
}

bool cpu::STA(int addrmode) {
	return false; // stub
}

bool cpu::LDA(int addrmode) {
	return false; // stub
}

bool cpu::CMP(int addrmode) {
	return false; // stub
}

bool cpu::SBC(int addrmode) {
	return false; // stub
}


// cc == 10
bool cpu::ASL(int addrmode) {
	return false; // stub
}

bool cpu::ROL(int addrmode) {
	return false; // stub
}

bool cpu::LSR(int addrmode) {
	return false; // stub
}

bool cpu::ROR(int addrmode) {
	return false; // stub
}

bool cpu::STX(int addrmode) {
	return false; // stub
}

bool cpu::LDX(int addrmode) {
	return false; // stub
}

bool cpu::DEC(int addrmode) {
	return false; // stub
}

bool cpu::INC(int addrmode) {
	return false; // stub
}