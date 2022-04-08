#ifndef CPU_H
#define CPU_H

#include "nes.h"
#include <vector> // temp

class system;
class cpu {
	using instruction_handler = bool (cpu::*)();
	using addrmode_handler = void (cpu::*)();
	static constexpr size_t memory_size = 32768;
	static constexpr size_t page_size = 256;
	static constexpr size_t page_count = memory_size/page_size;
	static constexpr size_t stack_size = page_size;

	struct instruction {
		const char *name;
		instruction_handler handler;
		u8 cycles;
	};

	struct addrmode {
		const char *name;
		addrmode_handler handler;
		u8 cycles;
	};

	struct group {
		instruction instructions[8];
		addrmode addressing_modes[8];
	};


public:
	cpu(system *sys);
	~cpu();

private:
	void reset();
	bool execute_next();

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

	// cc == 00
	// null
	bool BIT();
	bool JMP();
	bool JMPABS();
	bool STY();
	bool LDY();
	bool CPY();
	bool CPX();

	// cc == 01
	bool ORA();
	bool AND();
	bool EOR();
	bool ADC();
	bool STA();
	bool LDA();
	bool CMP();
	bool SBC();

	// cc == 10
	bool ASL();
	bool ROL();
	bool LSR();
	bool ROR();
	bool STX();
	bool LDX();
	bool DEC();
	bool INC();


	/* -- Need to implement please -- */
	void store_byte(u16 address, u8 byte);

	u8 get_byte(u16 address) const; // return byte from address
	u8 get_byte() { return get_byte(m_registers.PC++); }

	// cc = 11 
	// Used for 65C816 instructions, which the NES uses.
	// Currently not worrying about it.

	static const group s_handlers[4];

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
	bool add_cycle; // Used in addressing modes. True if crosses page.
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
