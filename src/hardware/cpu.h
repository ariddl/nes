#ifndef CPU_H
#define CPU_H

#include "nes.h"
#include <vector> // temp

class system;
class cpu {
	using instruction_handler = void (cpu::*)();
	using addrmode_handler = void (cpu::*)();
	static constexpr size_t memory_size = 32768;
	static constexpr size_t page_size = 256;
	static constexpr size_t page_count = memory_size/page_size;
	static constexpr size_t stack_size = page_size;

	struct opcode { 
		const char *name;
		instruction_handler instr_handler;
		addrmode_handler addr_handler;
		u8 cycles;
		u8 bytes;
	};

public:
	cpu(system *sys);
	~cpu();
	
	void init(const u8 *mem, size_t sz);

	const auto get_registers() const { return m_registers; }
	const u8 *get_mem() const { return memory; }

	bool execute_next();
private:
	void reset();

	void IMM();
	void ZP();
	void ABS();
	void ZPX();
	void ABX();
	void ABY();
	void ZPY();
	void ACC();
	void IDZPX();
	void IDZPY();
	void REL(); // relative
	void IMP(); // implied
	void IDABS(); 

	// cc == 00
	// null
	void BIT();
	void JMP();
	void JMPABS();
	void STY();
	void LDY();
	void CPY();
	void CPX();

	// cc == 01
	void ORA();
	void AND();
	void EOR();
	void ADC();
	void STA();
	void LDA();
	void CMP();
	void SBC();

	// cc == 10
	void ASL();
	void ROL();
	void LSR();
	void ROR();
	void STX();
	void LDX();
	void DEC();
	void INC();

	// cc = 11 
	// Used for 65C816 instructions, which the NES uses.
	// Currently not worrying about it.

	// Branch xxy1 0000
	void BPL();
	void BMI();
	void BVC();
	void BVS();
	void BCC();
	void BCS();
	void BNE();
	void BEQ();

	// Interrupt/subroutine no pattern
	void BRK();
	void JSR();
	void RTI();
	void RTS();

	// Single-byte instructions 
	// iiii1000
	void PHP();
	void CLC();
	void PLP();
	void SEC();
	void PHA();
	void CLI();
	void PLA();
	void SEI();
	void DEY();
	void TYA();
	void TAY();
	void CLV();
	void INY();
	void CLD();
	void INX();
	void SED();

	//jjjj1010 does not include all jjjj
	void TXA(); // 0x8A
	void TXS(); // 0x9A
	void TAX(); // 0xAA
	void TSX(); // 0xBA
	void DEX(); // 0xCA
	void NOP(); // 0xEA

	/* -- Need to implement please -- */
	void store_byte(u16 address, u8 byte);

	u8 get_byte(u16 address) const; // return byte from address
	u8 get_byte() { return get_byte(m_registers.PC++); }

	void push(u8 b) { memory[0x100 + m_registers.S--] = b; }
	u8 pop() { return memory[0x100 + ++m_registers.S]; }

	opcode opcode_set[256];
	void setup();

	struct {
		// Accumulator
		u8 A;
		// Indexes
		u8 X;
		u8 Y;
		// Program Counter
		u16 PC;
		// Stack Pointer
		u8 S;
		// Status
		union {
			struct {
				u8 N : 1; // Negative
				u8 V : 1; // Overflow
				u8 U : 2; // Unused
				u8 D : 1; // Decimal
				u8 I : 1; // Interrupt disable
				u8 Z : 1; // Zero
				u8 C : 1; // Carry 
			};
			u8 flags; // Flags
		} status; // Status
	} m_registers;

	u16 instr_arg; // Used in addressing modes. Returns byte loaded. 
	u16 instr_addr; // Used in addressing modes. Needed for store instruction. 9
	bool cross_page; // True if address crosses page.
	bool branch; // True if branch taken. 
	u64 total_cycles; // 

	/*
		0000-07FF is RAM, 0800-1FFF are mirrors of RAM (you AND the address with
		07FF to get the effective address)

		2000-2007 is how the CPU writes to the PPU, 2008-3FFF are mirrors of
		that address range.

		4000-401F is for IO ports and sound

		4020-4FFF is rarely used, but can be used by some cartridges

		5000-5FFF is rarely used, but can be used by some cartridges, often as
		bank switching registers, not actual memory, but some cartridges put RAM
		there

		6000-7FFF is often cartridge WRAM. Since emulators usually emulate this
		whether it actually exists in the cartridge or not, there's a little bit
		of controversy about NES headers not adequately representing a
		cartridge.

		8000-FFFF is the main area the cartridge ROM is mapped to in memory.
		Sometimes it can be bank switched, usually in 32k, 16k, or 8k sized
		banks.
	*/
	u8 *memory;
	u8 *memory_map[256];

	system *m_system;
};

#endif
