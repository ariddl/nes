#ifndef CPU_H
#define CPU_H

#include "nes.h"
#include <vector> // temp

class system;
class cpu {
	using instruction_handler = bool (cpu::*)();
	using addrmode_handler = void (cpu::*)();
	static constexpr size_t stack_size = 256;

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

	enum addrmode_cc00 {
		addrmode_cc00_immediate,
		addrmode_cc00_zero_page,
		addrmode_cc00_absolute = 0b011,
		addrmode_cc00_zero_page_x = 0b101,
		addrmode_cc00_absolute_x = 0b111
	};

	enum addrmode_cc01 {
		addrmode_cc01_zeropage_x,
		addrmode_cc01_zeropage,
		addrmode_cc01_immediate,
		addrmode_cc01_absolute,
		addrmode_cc01_zeropage_y,
		addrmode_cc01_zreopage_x_,
		addrmode_cc01_absolute_y,
		addrmode_cc01_absolute_x
	};

	enum addrmode_cc10 {
		addrmode_cc10_immediate,
		addrmode_cc10_zero_page,
		addrmode_cc10_accumulator,
		addrmode_cc10_absolute,
		addrmode_cc10_zero_page_x = 0b101,
		addrmode_cc10_absolute_x
	};

public:
	cpu(system *sys);

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

	// cc = 11
	// Used for 65C816 instructions, which the NES uses. 
	// Current not worrying about it.
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
				u8 negative : 1;
				u8 overflow : 1;
				u8 unused : 2;
				u8 decimal : 1;
				u8 interrupt_disable : 1;
				u8 zero : 1;
				u8 carry : 1;
			};
			u8 flags;
		} status;
	} m_registers;

	u8 m_stack[stack_size];
	std::vector<u8> m_code;
	system *m_system;
};

#endif
