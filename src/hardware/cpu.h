#ifndef CPU_H
#define CPU_H

#include "nes.h"
#include <vector> // temp

class system;
class cpu {
	using instruction_handler = bool (cpu::*)(int addrmode);
	static constexpr size_t stack_size = 256;

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

	// cc == 00
	// null
	bool BIT(int addrmode);
	bool JMP(int addrmode);
	bool JMPABS(int addrmode);
	bool STY(int addrmode);
	bool LDY(int addrmode);
	bool CPY(int addrmode);
	bool CPX(int addrmode);

	// cc == 01
	bool ORA(int addrmode);
	bool AND(int addrmode);
	bool EOR(int addrmode);
	bool ADC(int addrmode);
	bool STA(int addrmode);
	bool LDA(int addrmode);
	bool CMP(int addrmode);
	bool SBC(int addrmode);

	// cc == 10
	bool ASL(int addrmode);
	bool ROL(int addrmode);
	bool LSR(int addrmode);
	bool ROR(int addrmode);
	bool STX(int addrmode);
	bool LDX(int addrmode);
	bool DEC(int addrmode);
	bool INC(int addrmode);

	// cc = 11
	// Used for 65C816 instructions, which the NES uses. 
	// Current not worrying about it.
	static const instruction_handler s_handlers[4][8];

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
