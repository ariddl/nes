#ifndef CPU_H
#define CPU_H

#include "nes.h"
#include <vector> // temp

class system;
class mem;
class cpu {
	friend class instructions;
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
	
	void init();

	const auto get_registers() const { return m_registers; }

	bool execute_next();
private:
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

	/* Bus */
	void write(u16 address, u8 byte);
	u8 read(u8 lo, u8 hi) const;
	u8 read(u16 address) const;
	u8 read();

	/* Stack */
	void push(u8 b);
	u8 pop();

	opcode opcode_set[256];

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
	u64 total_cycles;

	system *m_system;
	mem &m_mem;
};

#endif
