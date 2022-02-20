#include "cpu.h"

cpu::cpu() 
	: m_registers{}
	, m_stack{} {
}

void cpu::reset() {
	m_registers.S = stack_size - 1; // $FF
}