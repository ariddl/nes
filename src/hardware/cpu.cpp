#include "cpu.h"
#include "system.h"

// TODO: Find number of cycles per instruction.
const cpu::group cpu::s_handlers[4] = {
	// cc == 00
    {
		{
			{"UNK", nullptr,   0}, {"BIT",    &cpu::BIT,    0}, 
			{"JMP", &cpu::JMP, 0}, {"JMPABS", &cpu::JMPABS, 0},
			{"STY", &cpu::STY, 0}, {"LDY",    &cpu::LDY,    0},
			{"CPY", &cpu::CPY, 0}, {"CPX",    &cpu::CPX,    0}
		},
		{
			{"IMM", &cpu::IMM, 0}, {"ZP",  &cpu::ZP,  0},
			{"UNK", nullptr,   0}, {"ABS", &cpu::ABS, 0}, 
			{"UNK", nullptr,   0}, {"ZPX", &cpu::ZPX, 0},
			{"UNK", nullptr,   0}, {"ABX", &cpu::ABX, 0}
		}
    },
	// cc == 01
	{
		{
			{"ORA", &cpu::ORA, 0}, {"AND", &cpu::AND, 0},
			{"EOR", &cpu::EOR, 0}, {"ADC", &cpu::ADC, 0},
			{"STA", &cpu::STA, 0}, {"LDA", &cpu::LDA, 0},
			{"CMP", &cpu::CMP, 0}, {"SBC", &cpu::SBC, 0}
		},
		{
			{"IDZPX", &cpu::IDZPX,  0}, {"ZP",  &cpu::ZP,  0},
			{"IMM",   &cpu::IMM,    0}, {"ABS", &cpu::ABS, 0},
			{"IDZPY", &cpu::IDZPY,  0}, {"ZPX", &cpu::ZPX, 0},
			{"ABY",   &cpu::ABY,    0}, {"ABX", &cpu::ABX, 0}	 
		}
	},
	// cc == 10
	{
		{
			{"ASL", &cpu::ASL, 0}, {"ROL", &cpu::ROL, 0},
			{"LSR", &cpu::LSR, 0}, {"ROR", &cpu::ROR, 0},
			{"STX", &cpu::STX, 0}, {"LDX", &cpu::LDX, 0},
			{"DEC", &cpu::DEC, 0}, {"INC", &cpu::INC, 0},
		},
		{
			{"IMM", &cpu::IMM, 0}, {"ZP",  &cpu::ZP,  0},
			{"ACC", &cpu::ACC, 0}, {"ABS", &cpu::ABS, 0}, 
			{"UNK", nullptr,   0}, {"ZPX", &cpu::ZPX, 0},
			{"ABX", &cpu::ABX, 0}, {"UNK", nullptr,   0}
		}
	},
	// cc == 11
	{
		{
			// TODO: NES Specific instructions?
			{"UNK", nullptr, 0}, {"UNK", nullptr, 0},
			{"UNK", nullptr, 0}, {"UNK", nullptr, 0},
			{"UNK", nullptr, 0}, {"UNK", nullptr, 0},
			{"UNK", nullptr, 0}, {"UNK", nullptr, 0},
		},
		{
			{"UNK", nullptr, 0}, {"UNK", nullptr, 0},
			{"UNK", nullptr, 0}, {"UNK", nullptr, 0},
			{"UNK", nullptr, 0}, {"UNK", nullptr, 0},
			{"UNK", nullptr, 0}, {"UNK", nullptr, 0},
		}
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
	// We need an actual clock. For now this will get us by to test individual
	// instructions.
	if (m_registers.PC >= m_code.size())
		return false;
	
	// The instruction handler will move PC as necessary for additional bytes.
	// Opcodes are in the format: aaabbbcc. aaa = group, bbb = addr mode, cc =
	// group.
	u8 opcode = m_code[m_registers.PC++];
	u8 operation = (opcode >> 5) & 0x7;
	u8 addrmode = (opcode >> 2) & 0x7;
	u8 tab = opcode & 0x3;
	if (tab >= 4 || operation >= 8) // TODO: Constants!
		return false;
	
	// TODO: Account for cycles from these addressing mode and instruction
	// overhead.
	const group &g = s_handlers[tab];
	(this->*g.addressing_modes[addrmode].handler)();
	return (this->*g.instructions[operation].handler)();
}

// Currently we are making the assumption that each instruction belongs to only
// one group and thus can only have one set of addressing modes. Need to
// confirm. So far it looks like this is the case.

// Each addressing mode takes its own number of cycles to process. For a full
// breakdown for each instruction, see:
// https://www.masswerk.at/6502/6502_instruction_set.html#layout

// Timing is very important in emulation and we must be sure we are
// cycle-to-cycle accurate. More thought must go into this before we continue
// this implementation.

// Addressing modes: 
void cpu::IMM() {
	u8 immediate = m_code[m_registers.PC + 1];
	instr_arg = immediate;
}

void cpu::ZP() {
	u8 address = m_code[m_registers.PC + 1];
	instr_arg = memory[0][address];
}

void cpu::ABS() {
	// For JMP the PC is set to address: u16 address = (byte1 << 8) + byte2; 
	u8 byte1 = m_code[m_registers.PC + 1];
	u8 byte2 = m_code[m_registers.PC + 2];
	instr_arg = memory[byte2][byte1];
}

void cpu::ZPX() {
	u8 contents = m_registers.X;
	u8 byte = m_code[m_registers.PC + 1];
	u8 address = byte + contents;
	instr_arg = memory[0][address];
}

void cpu::ABX() {
	u8 contents = m_registers.Y;
	u8 byte1 = m_code[m_registers.PC + 1];
	u8 byte2 = m_code[m_registers.PC + 2];
	u16 address = ((byte2 << 8) + byte1) + contents;
	instr_arg = memory[address >> 8][address << 8];
}

void cpu::ABY() {
	u8 contents = m_registers.X;
	u8 byte1 = m_code[m_registers.PC + 1];
	u8 byte2 = m_code[m_registers.PC + 2];
	u16 address = ((byte2 << 8) + byte1) + contents;
	instr_arg = memory[address >> 8][address << 8];

}

void cpu::ZPY() {
	u8 contents = m_registers.Y;
	u8 byte = m_code[m_registers.PC + 1];
	u8 address = byte + contents; // must be u8 because 00xx
	instr_arg = memory[0][address];
}

void cpu::ACC() {
	u8 contents = m_registers.A;
	instr_arg = contents;
}

void cpu::IDZPX() {
	u8 contents = m_registers.X;
	u8 byte = m_code[m_registers.PC + 1];
	u8 z_address = contents + byte;
	u8 address_byte1 = memory[0][z_address];
	u8 address_byte2 = memory[0][z_address + 1];
	instr_arg = memory[address_byte2][address_byte1];
}

void cpu::IDZPY() {
	u8 contents = m_registers.Y;
	u8 byte = m_code[m_registers.PC + 1];
	u8 address_byte1 = memory[0][byte];
	u8 address_byte2 = memory[0][byte + 1];
	u16 address = ((address_byte2 << 8) + address_byte1) + contents;
	instr_arg = memory[address >> 8][address << 8];
}

// cc == 00
bool cpu::BIT() {
	return false; // stub
}

bool cpu::JMP() {
	return false; // stub
}

bool cpu::JMPABS() {
	return false; // stub
}

bool cpu::STY() {
	return false; // stub
}

bool cpu::LDY() {
	return false; // stub
}

bool cpu::CPY() {
	return false; // stub
}

bool cpu::CPX() {
	return false; // stub
}

// cc == 01
bool cpu::ORA() {
	return false; // stub
}

bool cpu::AND() {
	return false; // stub
}

bool cpu::EOR() {
	return false; // stub
}

bool cpu::ADC() {
	return false; // stub
}

bool cpu::STA() {
	return false; // stub
}

bool cpu::LDA() {
	return false; // stub
}

bool cpu::CMP() {
	return false; // stub
}

bool cpu::SBC() {
	return false; // stub
}


// cc == 10
bool cpu::ASL() {
	return false; // stub
}

bool cpu::ROL() {
	return false; // stub
}

bool cpu::LSR() {
	return false; // stub
}

bool cpu::ROR() {
	return false; // stub
}

bool cpu::STX() {
	return false; // stub
}

bool cpu::LDX() {
	return false; // stub
}

bool cpu::DEC() {
	return false; // stub
}

bool cpu::INC() {
	return false; // stub
}