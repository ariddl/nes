#include "cpu.h"
#include "system.h"

void cpu::setup()
{
	opcode_set[0] = {"BRK", &cpu::BRK, &cpu::REL, 0};
}

cpu::cpu(system *sys) 
    : m_registers{}
	, m_system(sys)
	, instr_arg(0)
	, cross_page(false)
	, branch(false)
	, memory{}
	, memory_map{} {
	setup();
	reset();
}

cpu::~cpu() {
	delete[] memory;
}

void cpu::reset() {
	// We need the reset vector to start executing instructions.
	// Note that the PPU is needed for any games to run instructions
	// since the game will wait for the PPU to be ready first.
	
	// When the CPU boots up, it reads the Reset vector, located at FFFC. 
	// That contains a 16-bit value which tells the CPU where to jump to.
    m_registers.S = stack_size - 1; // $FF
	delete[] memory;
	memory = new u8[0xffff];
}

bool cpu::execute_next() {
	// We need an actual clock. For now this will get us by to test individual
	// instructions.
	if (m_registers.PC == 0xffff)
		return false;
	
	// The instruction handler will move PC as necessary for additional bytes.
	// Opcodes are in the format: aaabbbcc. aaa = group, bbb = addr mode, cc =
	// group.
	u8 opcode_byte = get_byte();

	
	// TODO: Account for cycles from these addressing mode and instruction
	// overhead.
	const opcode &o = opcode_set[opcode_byte];
	total_cycles = opcode_set[opcode_byte].cycles; 
	cross_page = false; branch = false;
	(this->*o.addr_handler)(); bool return_val = (this->*o.instr_handler)();
	total_cycles += cross_page + branch;
	return return_val;
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
	u8 immediate = get_byte();
	instr_arg = immediate;
}

void cpu::ZP() {
	u8 address = get_byte();
	instr_arg = get_byte(address);
}

void cpu::ABS() {
	// For JMP the PC is set to address: u16 address = (byte2 << 8) | byte1; 
	u8 byte1 = get_byte();
	u8 byte2 = get_byte();
	instr_arg = get_byte((byte2 << 8) | byte1);
}

void cpu::ZPX() {
	u8 contents = m_registers.X;
	u8 byte = get_byte(m_registers.PC + 1);
	u8 address = byte + contents;
	instr_arg = get_byte(address);
}

void cpu::ABX() {
	u8 contents = m_registers.X;
	u8 byte1 = get_byte();
	u8 byte2 = get_byte();
	u16 address = ((byte2 << 8) + byte1) + contents;
	instr_arg = get_byte(address);
}

void cpu::ABY() {
	u8 contents = m_registers.Y;
	u8 byte1 = get_byte();
	u8 byte2 = get_byte();
	u16 address = ((byte2 << 8) + byte1) + contents;
	instr_arg = get_byte(address);

}

void cpu::ZPY() {
	u8 contents = m_registers.Y;
	u8 byte = get_byte();
	u8 address = byte + contents; // must be u8 because 00xx
	instr_arg = get_byte(address);
}

void cpu::ACC() {
	u8 contents = m_registers.A;
	instr_arg = contents;
}

void cpu::IDZPX() {
	u8 contents = m_registers.X;
	u8 byte = get_byte();
	u8 z_address = contents + byte;
	u8 address_byte1 = get_byte(z_address);
	u8 address_byte2 = get_byte(z_address + 1);
	instr_arg = get_byte((address_byte2 << 8) | address_byte1);
}

void cpu::IDZPY() {
	u8 contents1 = m_registers.Y;
	u8 byte = get_byte();
	u8 contents2 = get_byte(byte);
	bool carry = (contents1 + contents2 > 0xFF);
	u8 address_byte1 = contents1 + contents2;
	u8 address_byte2 = get_byte(byte + 1) + carry;
	instr_arg = get_byte((address_byte2 << 8) | address_byte1);
}

void cpu::REL() {
	// stub
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
	// Flags: N, Z
	u8 contents = instr_arg;
	m_registers.status.N = contents < 0 ? 1 : 0;
	m_registers.status.Z = contents == 0 ? 1 : 0;
	m_registers.Y = contents;
	return true;
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
	// Flags: N, Z
	u8 contents = instr_arg;
	m_registers.status.N = contents < 0 ? 1 : 0;
	m_registers.status.Z = contents == 0 ? 1 : 0;
	m_registers.A = contents;
	return true;
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
	// Flags: N, Z
	u8 contents = instr_arg;
	m_registers.status.N = contents < 0 ? 1 : 0;
	m_registers.status.Z = contents == 0 ? 1 : 0;
	m_registers.X = contents;
	return true;
}

bool cpu::DEC() {
	return false; // stub
}

bool cpu::INC() {
	return false; // stub
}

bool cpu::BPL() {
	return false; // stub
}

bool cpu::BMI() {
	return false; // stub
}

bool cpu::BVC() {
	return false; // stub
}

bool cpu::BVS() {
	return false; // stub
}

bool cpu::BCC() {
	return false; // stub
}

bool cpu::BCS() {
	return false; // stub
}

bool cpu::BNE() {
	return false; // stub
}

bool cpu::BEQ() {
	return false; // stub
}

bool cpu::BRK() {
	return false; // stub
}

bool cpu::JSRABS() {
	return false; // stub
}

bool cpu::RTI() {
	return false; // stub
}

bool cpu::RTS() {
	return false; // stub
}

bool cpu::PHP() {
	return false; // stub
}

bool cpu::CLC() {
	return false; // stub
}

bool cpu::PLP() {
	return false; // stub
}

bool cpu::SEC() {
	return false; // stub
}

bool cpu::PHA() {
	return false; // stub
}

bool cpu::CLI() {
	return false; // stub
}

bool cpu::PLA() {
	return false; // stub
}

bool cpu::SEI() {
	return false; // stub
}

bool cpu::DEY() {
	return false; // stub
}

bool cpu::TYA() {
	return false; // stub
}

bool cpu::TAY() {
	return false; // stub
}

bool cpu::CLV() {
	return false; // stub
}

bool cpu::INY() {
	return false; // stub
}

bool cpu::CLD() {
	return false; // stub
}

bool cpu::INX() {
	return false; // stub
}

bool cpu::SED() {
	return false; // stub
}

bool cpu::TXA() {
	return false; // stub
} 

bool cpu::TXS() {
	return false; // stub
} 

bool cpu::TAX() {
	return false; // stub
} 

bool cpu::TSX() {
	return false; // stub
} 

bool cpu::DEX() {
	return false; // stub
} 

bool cpu::NOP() {
	return false; // stub
} 



void cpu::store_byte(u16 address, u8 byte) {
	memory[address] = byte;
}

u8 cpu::get_byte(u16 address) const {
	// TODO: Instead of having bounds checking here, let's add a
	// new field to our instruction table with minimum number of bytes
	return memory[address];
}