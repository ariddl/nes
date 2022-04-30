#include "cpu.h"
#include "instructions.h"
#include "system.h"
#include "mem.h"
#include <cstdio>

cpu::cpu(system *sys)
    : m_registers{}
	, m_system(sys)
	, instr_arg(0)
	, cross_page(false)
	, branch(false)
	, m_mem(*sys->get_mem()) {
	instructions::init_table(opcode_set);
}

cpu::~cpu() {
}

void cpu::init() {
	// This will be called on reset.
	// We need the reset vector to start executing instructions.
	// Note that the PPU is needed for any games to run instructions
	// since the game will wait for the PPU to be ready first.
	
	// When the CPU boots up, it reads the Reset vector, located at FFFC. 
	// That contains a 16-bit value which tells the CPU where to jump to.
    m_registers.S = stack_size - 1; // $FF
	m_registers.PC = 0x2000;
}

bool cpu::execute_next() {
	if (m_mem.read(m_registers.PC) == 0) {printf("\n");return false;}
	
	u8 opcode_byte = read();
	const opcode &o = opcode_set[opcode_byte];
	if (0xffff - m_registers.PC <= o.bytes)
		return false;
	
	cross_page = branch = false;
	(this->*o.addr_handler)();
	(this->*o.instr_handler)();
	printf("%s ", o.name);
	total_cycles += o.cycles + cross_page + branch;
	return true;
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

/** Addressing Modes: **/

void cpu::IMM() {
	u8 immediate = read();
	instr_arg = immediate;
}

void cpu::ZP() {
	u8 address = read();
	instr_addr = address;
	instr_arg = read(address);
}

void cpu::ABS() {
	// For JMP the PC is set to address: u16 address = (byte2 << 8) | byte1; 
	u8 byte1 = read(), byte2 = read();
	instr_addr = (byte2 << 8) | byte1;
	instr_arg = read(byte1, byte2);
}

void cpu::ZPX() {
	u8 contents = m_registers.X;
	u8 byte = read(m_registers.PC + 1);
	u8 address = byte + contents;
	instr_addr = address;
	instr_arg = read(address);
}

void cpu::ABX() {
	u8 contents = m_registers.X;
	u8 byte1 = read(), byte2 = read();
	bool carry = (byte1 + contents > 0xFF);
	m_registers.status.C = carry; // might not be needed.
	cross_page = carry;
	u8 address_byte1 = byte1 + contents;
	u8 address_byte2 = byte2 + carry;
	instr_addr = (address_byte2 << 8) | address_byte1;
	instr_arg = read(address_byte1, address_byte2);
}

void cpu::ABY() {
	u8 contents = m_registers.Y;
	u8 byte1 = read(), byte2 = read();
	bool carry = (byte1 + contents > 0xFF);
	m_registers.status.C = carry; // might not be needed.
	cross_page = carry;
	u8 address_byte1 = byte1 + contents;
	u8 address_byte2 = byte2 + carry;
	instr_addr = (address_byte2 << 8) | address_byte1;
	instr_arg = read(address_byte1, address_byte2);
}

void cpu::ZPY() {
	u8 contents = m_registers.Y;
	u8 byte = read();
	u8 address = byte + contents; // must be u8 because 00xx
	instr_addr = address;
	instr_arg = read(address);
}

void cpu::ACC() {
	u8 contents = m_registers.A;
	instr_arg = contents;
}

void cpu::IDZPX() {
	u8 contents = m_registers.X;
	u8 byte = read();
	u8 z_address = contents + byte;
	u8 address_byte1 = read(z_address);
	u8 address_byte2 = read(z_address + 1);
	instr_addr = (address_byte2 << 8) | address_byte1;
	instr_arg = read(address_byte1, address_byte2);
}

void cpu::IDZPY() {
	u8 contents1 = m_registers.Y;
	u8 byte = read();
	u8 contents2 = read(byte);
	bool carry = (contents1 + contents2 > 0xFF);
	m_registers.status.C = carry; // might not be needed.
	cross_page = carry;
	u8 address_byte1 = contents1 + contents2;
	u8 address_byte2 = read(byte + 1) + carry;
	instr_addr = (address_byte2 << 8) | address_byte1;
	instr_arg = read(address_byte1, address_byte2);
}

void cpu::REL() {
	s8 offset = read();
	u8 low_byte = (u8)m_registers.PC;
	cross_page |= low_byte + offset < 0 || low_byte + offset > 0xFF;
	u16 new_address = m_registers.PC + offset;
	instr_addr = new_address;
	instr_arg = new_address;
}

void cpu::IMP() {
	// Nothing should be here.
}

void cpu::IDABS() {
	u8 byte1 = read(), byte2 = read();
	u16 address = (byte2 << 8) | byte1;
	u8 address_byte1 = read(address);
	u8 address_byte2 = read(address + 1);
	instr_addr = (address_byte2 << 8) | address_byte1;
	instr_arg = instr_addr; 
}


/** Instructions: **/

void cpu::BIT() {
	// Flags: N, V, Z
	u8 contents = m_registers.A;
	u8 result = instr_arg & contents;
	m_registers.status.N = result < 0 ? 1 : 0;
	m_registers.status.V = result & (1 << 6); // set to 6th bit
	m_registers.status.Z = result == 0 ? 1 : 0;
}

void cpu::JMP() {
	m_registers.PC = instr_arg;
}

void cpu::STY() {
	// Flags: none
	u8 contents = m_registers.Y; 
	write(instr_addr, contents);
}

void cpu::LDY() {
	// Flags: N, Z
	u8 contents = instr_arg;
	m_registers.status.N = contents < 0 ? 1 : 0;
	m_registers.status.Z = contents == 0 ? 1 : 0;
	m_registers.Y = contents;
}

void cpu::CPY() {
	// Flags: N, Z, C
	u8 A = m_registers.Y;
	u8 B = ~instr_arg; // inverted for subtracting. 
	bool carry = (A + B > 0xFF);
	u8 C = A + B;
	m_registers.status.N = C < 0 ? 1 : 0;
	m_registers.status.Z = C == 0 ? 1 : 0;
	m_registers.status.C = carry;
}

void cpu::CPX() {
	// Flags: N, Z, C
	u8 A = m_registers.X;
	u8 B = ~instr_arg; // inverted for subtracting. 
	bool carry = (A + B > 0xFF);
	u8 C = A + B;
	m_registers.status.N = C < 0 ? 1 : 0;
	m_registers.status.Z = C == 0 ? 1 : 0;
	m_registers.status.C = carry;
}

void cpu::ORA() {
	// Flags: N, Z
	u8 contents = m_registers.A;
	u8 result = instr_arg | contents;
	m_registers.status.N = result < 0 ? 1 : 0;
	m_registers.status.V = result & (1 << 6); // set to 6th bit
	m_registers.status.Z = result == 0 ? 1 : 0;
}

void cpu::AND() {
	// Flags: N, Z
	u8 contents = m_registers.A;
	u8 result = instr_arg & contents;
	m_registers.status.N = result < 0 ? 1 : 0;
	m_registers.status.Z = result == 0 ? 1 : 0;
	m_registers.A = result;
}

void cpu::EOR() {
	// Flags: N, Z
	u8 contents = m_registers.A;
	u8 result = instr_arg ^ contents;
	m_registers.status.N = result < 0 ? 1 : 0;
	m_registers.status.V = result & (1 << 6); // set to 6th bit
	m_registers.status.Z = result == 0 ? 1 : 0;
}

void cpu::ADC() {
	// Flags: N, V, Z, C
	u8 A = m_registers.A;
	u8 B = instr_arg; 
	bool carry = (A + B > 0xFF);
	u8 C = A + B + m_registers.status.C;
	m_registers.A = C;

	m_registers.status.N = C < 0 ? 1 : 0;
	m_registers.status.V = (~(A ^ B)) & (A ^ C) & 0x80;
	m_registers.status.Z = C == 0 ? 1 : 0;
	m_registers.status.C = carry;
}

void cpu::STA() {
	// Flags: none
	u8 contents = m_registers.A; 
	write(instr_addr, contents);
}

void cpu::LDA() {
	// Flags: N, Z
	u8 contents = instr_arg;
	m_registers.status.N = contents < 0 ? 1 : 0;
	m_registers.status.Z = contents == 0 ? 1 : 0;
	m_registers.A = contents;
}

void cpu::CMP() {
	// Flags: N, Z, C
	u8 A = m_registers.A;
	u8 B = ~instr_arg; // inverted for subtracting. 
	bool carry = (A + B > 0xFF);
	u8 C = A + B;
	m_registers.status.N = C < 0 ? 1 : 0;
	m_registers.status.Z = C == 0 ? 1 : 0;
	m_registers.status.C = carry;
}

void cpu::SBC() {
	// Flags: N, V, Z, C
	u8 A = m_registers.A;
	u8 B = ~instr_arg; // inverted for subtracting. 
	bool carry = (A + B > 0xFF);
	u8 C = A + B + m_registers.status.C;
	m_registers.A = C;

	m_registers.status.N = C < 0 ? 1 : 0;
	m_registers.status.V = (~(A ^ B)) & (A ^ C) & 0x80;
	m_registers.status.Z = C == 0 ? 1 : 0;
	m_registers.status.C = carry;
}

void cpu::ASL() {
	u16 tmp = static_cast<u16>(read(instr_arg)) << 1;
	m_registers.status.C = (tmp >> 8) > 0;
	m_registers.status.Z = (tmp & 0xff) == 0;
	m_registers.status.N = tmp & 0x80;
	write(instr_arg, tmp & 0xff);
}

void cpu::ROL() {
	u16 tmp = static_cast<u16>(read(instr_arg)) << 1 | m_registers.status.C;
	m_registers.status.C = tmp >> 8;
	m_registers.status.Z = (tmp & 0xff) == 0;
	m_registers.status.N = tmp & 0x80;
	write(instr_arg, tmp & 0xff);
}

void cpu::LSR() {
	u8 arg = read(instr_arg);
	m_registers.status.C = arg & 1;
	arg >>= 1;
	m_registers.status.Z = (arg & 0xff) == 0;
	m_registers.status.N = arg & 0x80;
	write(instr_arg, arg & 0xff);
}

void cpu::ROR() {
	u8 arg = read(instr_arg);
	u16 tmp = static_cast<u16>(m_registers.status.C << 7) | (arg >> 1);
	m_registers.status.C = arg & 1;
	m_registers.status.Z = (tmp & 0xff) == 0;
	m_registers.status.N = tmp & 0x80;
	write(instr_arg, tmp & 0xff);
}

void cpu::STX() {
	// Flags: none
	u8 contents = m_registers.X; 
	write(instr_addr, contents);
}

void cpu::LDX() {
	// Flags: N, Z
	u8 contents = instr_arg;
	m_registers.status.N = contents < 0 ? 1 : 0;
	m_registers.status.Z = contents == 0 ? 1 : 0;
	m_registers.X = contents;
}

void cpu::DEC() {
	u8 val = read(instr_arg) - 1; // TODO: wrong type
	write(instr_arg, val);
	m_registers.status.Z = m_registers.A == 0;
	m_registers.status.N = m_registers.A & 0x80;
}

void cpu::INC() {
	u8 val = read(instr_arg) + 1; // wrong type
	write(instr_arg, val);
	m_registers.status.Z = m_registers.A == 0;
	m_registers.status.N = m_registers.A & 0x80;
}

void cpu::BPL() {
	if (!m_registers.status.N)
		m_registers.PC = instr_arg;
}

void cpu::BMI() {
	if (m_registers.status.N)
		m_registers.PC = instr_arg;
}

void cpu::BVC() {
	if (!m_registers.status.V)
		m_registers.PC = instr_arg;
}

void cpu::BVS() {
	if (m_registers.status.V)
		m_registers.PC = instr_arg;
}

void cpu::BCC() {
	if (!m_registers.status.C)
		m_registers.PC = instr_arg;
}

void cpu::BCS() {
	if (m_registers.status.C)
		m_registers.PC = instr_arg;
}

void cpu::BNE() {
	if (!m_registers.status.Z)
		m_registers.PC = instr_arg;
}

void cpu::BEQ() {
	if (m_registers.status.Z)
		m_registers.PC = instr_arg;
}

void cpu::BRK() {
	m_registers.status.I = 1;
	push(m_registers.PC >> 8);
	push(m_registers.PC & 0xff);
	push(m_registers.status.flags);
	m_registers.PC = static_cast<u16>(read(0xfffe)) | static_cast<u16>(read(0xffff)) << 8;
}

void cpu::JSR() {
	// TODO: Do we need to adjust PC here?
	push(m_registers.PC >> 8);
	push(m_registers.PC & 0xff);
	m_registers.PC = instr_arg;
}

void cpu::RTI() {
	m_registers.status.flags = pop();
	m_registers.PC = static_cast<u16>(pop()) | static_cast<u16>(pop()) << 8;
}

void cpu::RTS() {
	m_registers.PC = static_cast<u16>(pop()) | static_cast<u16>(pop()) << 8;
}

void cpu::PHP() {
	push(m_registers.status.flags);
}

void cpu::CLC() {
	// Flags: C
	m_registers.status.C = 0;
}

void cpu::PLP() {
	m_registers.status.flags = pop();
}

void cpu::SEC() {
	// Flags: C
	m_registers.status.C = 1;
}

void cpu::PHA() {
	push(m_registers.A);
}

void cpu::CLI() {
	// Flags: I
	m_registers.status.I = 0;
}

void cpu::PLA() {
	m_registers.A = pop();
	m_registers.status.Z = m_registers.A == 0;
	m_registers.status.N = m_registers.A & 0x80;
}

void cpu::SEI() {
	// Flags: I
	m_registers.status.I = 1;
}

void cpu::DEY() {
	--m_registers.Y;
	m_registers.status.Z = m_registers.Y == 0;
	m_registers.status.N = m_registers.Y & 0x80;
}

void cpu::TYA() {
	// Flags: N, Z
	u8 contents = m_registers.Y;
	m_registers.A = contents;
	m_registers.status.N = contents < 0 ? 1 : 0;
	m_registers.status.Z = contents == 0 ? 1 : 0;
}

void cpu::TAY() {
	// Flags: N, Z
	u8 contents = m_registers.A;
	m_registers.Y = contents;
	m_registers.status.N = contents < 0 ? 1 : 0;
	m_registers.status.Z = contents == 0 ? 1 : 0;
}

void cpu::CLV() {
	// Flags: V
	m_registers.status.V = 0;
}

void cpu::INY() {
	++m_registers.Y;
	m_registers.status.Z = m_registers.Y == 0;
	m_registers.status.N = m_registers.Y & 0x80;
}

void cpu::CLD() {
	// Flags: D
	m_registers.status.D = 0;
}

void cpu::INX() {
	++m_registers.X;
	m_registers.status.Z = m_registers.X == 0;
	m_registers.status.N = m_registers.X & 0x80;
}

void cpu::SED() {
	// Flags: D
	m_registers.status.D = 1;
}

void cpu::TXA() {
	// Flags: N, Z
	u8 contents = m_registers.X;
	m_registers.A = contents;
	m_registers.status.N = contents < 0 ? 1 : 0;
	m_registers.status.Z = contents == 0 ? 1 : 0;
} 

void cpu::TXS() {
	// Flags: N, Z
	u8 contents = m_registers.X;
	m_registers.S = contents;
	m_registers.status.N = contents < 0 ? 1 : 0;
	m_registers.status.Z = contents == 0 ? 1 : 0;
} 

void cpu::TAX() {
	// Flags: N, Z
	u8 contents = m_registers.A;
	m_registers.X = contents;
	m_registers.status.N = contents < 0 ? 1 : 0;
	m_registers.status.Z = contents == 0 ? 1 : 0;
} 

void cpu::TSX() {
	// Flags: N, Z
	u8 contents = m_registers.S;
	m_registers.X = contents;
	m_registers.status.N = contents < 0 ? 1 : 0;
	m_registers.status.Z = contents == 0 ? 1 : 0;
} 

void cpu::DEX() {
	--m_registers.X;
	m_registers.status.Z = m_registers.X == 0;
	m_registers.status.N = m_registers.X & 0x80;
}

void cpu::NOP() {
	// Flags: None
}

/* Bus */
void cpu::write(u16 address, u8 byte) { m_mem.write(address, byte); }
u8 cpu::read(u8 lo, u8 hi) const { return m_mem.read(lo, hi); }
u8 cpu::read(u16 address) const { return m_mem.read(address); }
u8 cpu::read() { return m_mem.read(m_registers.PC++); }

/* Stack */
void cpu::push(u8 b) { m_mem.write(0x100 + m_registers.S--, b); }
u8 cpu::pop() { return m_mem.read(0x100 + m_registers.S++); }