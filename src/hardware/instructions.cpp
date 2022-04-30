#include "instructions.h"

void instructions::init_table(cpu::opcode *tab) {
    // Fill the table with each type of instruction with all addressing modes:
    BRK(tab); ORA(tab); ASL(tab); PHP(tab); BPL(tab); CLC(tab);
    JSR(tab); AND(tab); BIT(tab); ROL(tab); PLP(tab); BMI(tab);
    SEC(tab); RTI(tab); EOR(tab); LSR(tab); PHA(tab); JMP(tab);
    BVC(tab); CLI(tab); RTS(tab); ADC(tab); ROR(tab); PLA(tab);
    BVS(tab); SEI(tab); STA(tab); STY(tab); STX(tab); DEY(tab);
    TXA(tab); BCC(tab); TYA(tab); TXS(tab); LDY(tab); LDA(tab);
    LDX(tab); TAY(tab); TAX(tab); BCS(tab); CLV(tab); TSX(tab);
    CPY(tab); CMP(tab); DEC(tab); INY(tab); DEX(tab); BNE(tab);
    CLD(tab); CPX(tab); SBC(tab); INC(tab); INX(tab); NOP(tab);
    BEQ(tab); SED(tab);
}

void instructions::BRK(cpu::opcode *tab) {
    tab[0x00] = { "BRK", &cpu::BRK, &cpu::IMP, 7, 1 };
}

void instructions::ORA(cpu::opcode *tab) {
    tab[0x01] = { "ORA", &cpu::ORA, &cpu::IDZPX, 6, 2 };
    tab[0x05] = { "ORA", &cpu::ORA, &cpu::ZP, 3, 2 };
    tab[0x09] = { "ORA", &cpu::ORA, &cpu::IMM, 2, 2 };
    tab[0x0D] = { "ORA", &cpu::ORA, &cpu::ABS, 4, 3 };
    tab[0x11] = { "ORA", &cpu::ORA, &cpu::IDZPY, 5, 2 };
    tab[0x15] = { "ORA", &cpu::ORA, &cpu::ZPX, 4, 2 };
    tab[0x19] = { "ORA", &cpu::ORA, &cpu::ABY, 4, 3 };
    tab[0x1D] = { "ORA", &cpu::ORA, &cpu::ABX, 4, 3 };
}

void instructions::ASL(cpu::opcode *tab) {
    tab[0x06] = { "ASL", &cpu::ASL, &cpu::ZP, 5, 2 };
    tab[0x0A] = { "ASL", &cpu::ASL, &cpu::ACC, 2, 1 };
    tab[0x0E] = { "ASL", &cpu::ASL, &cpu::ABS, 6, 3 };
    tab[0x16] = { "ASL", &cpu::ASL, &cpu::ZPX, 6, 2 };
    tab[0x1E] = { "ASL", &cpu::ASL, &cpu::ABX, 7, 3 };
}

void instructions::PHP(cpu::opcode *tab) {
    tab[0x08] = { "PHP", &cpu::PHP, &cpu::IMP, 3, 1 };
}

void instructions::BPL(cpu::opcode *tab) {
    tab[0x10] = { "BPL", &cpu::BPL, &cpu::REL, 2, 2 };
}

void instructions::CLC(cpu::opcode *tab) {
    tab[0x18] = { "CLC", &cpu::CLC, &cpu::IMP, 2, 1 };
}

void instructions::JSR(cpu::opcode *tab) {
    tab[0x20] = { "JSR", &cpu::JSR, &cpu::ABS, 6, 3 };
}

void instructions::AND(cpu::opcode *tab) {
    tab[0x21] = { "AND", &cpu::AND, &cpu::IDZPX, 6, 2 };
    tab[0x25] = { "AND", &cpu::AND, &cpu::ZP, 3, 2 };
    tab[0x29] = { "AND", &cpu::AND, &cpu::IMM, 2, 2 };
    tab[0x2D] = { "AND", &cpu::AND, &cpu::ABS, 4, 3 };
    tab[0x31] = { "AND", &cpu::AND, &cpu::IDZPY, 5, 2 };
    tab[0x35] = { "AND", &cpu::AND, &cpu::ZPX, 4, 2 };
    tab[0x39] = { "AND", &cpu::AND, &cpu::ABY, 4, 3 };
    tab[0x3D] = { "AND", &cpu::AND, &cpu::ABX, 4, 3 };
}

void instructions::BIT(cpu::opcode *tab) {
    tab[0x24] = { "BIT", &cpu::BIT, &cpu::ZP, 3, 2 };
    tab[0x2C] = { "BIT", &cpu::BIT, &cpu::ABS, 4, 3 };
}

void instructions::ROL(cpu::opcode *tab) {
    tab[0x26] = { "ROL", &cpu::ROL, &cpu::ZP, 5, 2 };
    tab[0x2A] = { "ROL", &cpu::ROL, &cpu::ACC, 2, 1 };
    tab[0x2E] = { "ROL", &cpu::ROL, &cpu::ABS, 6, 3 };
    tab[0x36] = { "ROL", &cpu::ROL, &cpu::ZPX, 6, 2 };
    tab[0x3E] = { "ROL", &cpu::ROL, &cpu::ABX, 7, 3 };
}

void instructions::PLP(cpu::opcode *tab) {
    tab[0x28] = { "PLP", &cpu::PLP, &cpu::IMP, 4, 1 };
}

void instructions::BMI(cpu::opcode *tab) {
    tab[0x30] = { "BMI", &cpu::BMI, &cpu::REL, 2, 2 };
}

void instructions::SEC(cpu::opcode *tab) {
    tab[0x38] = { "SEC", &cpu::SEC, &cpu::IMP, 2, 1 };
}

void instructions::RTI(cpu::opcode *tab) {
    tab[0x40] = { "RTI", &cpu::RTI, &cpu::IMP, 6, 1 };
}

void instructions::EOR(cpu::opcode *tab) {
    tab[0x41] = { "EOR", &cpu::EOR, &cpu::IDZPX, 6, 2 };
    tab[0x45] = { "EOR", &cpu::EOR, &cpu::ZP, 3, 2 };
    tab[0x49] = { "EOR", &cpu::EOR, &cpu::IMM, 2, 2 };
    tab[0x4D] = { "EOR", &cpu::EOR, &cpu::ABS, 4, 3 };
    tab[0x51] = { "EOR", &cpu::EOR, &cpu::IDZPY, 5, 2 };
    tab[0x55] = { "EOR", &cpu::EOR, &cpu::ZPX, 4, 2 };
    tab[0x59] = { "EOR", &cpu::EOR, &cpu::ABY, 4, 3 };
    tab[0x5D] = { "EOR", &cpu::EOR, &cpu::ABX, 4, 3 };
}

void instructions::LSR(cpu::opcode *tab) {
    tab[0x46] = { "LSR", &cpu::LSR, &cpu::ZP, 5, 2 };
    tab[0x4A] = { "LSR", &cpu::LSR, &cpu::ACC, 2, 1 };
    tab[0x4E] = { "LSR", &cpu::LSR, &cpu::ABS, 6, 3 };
    tab[0x56] = { "LSR", &cpu::LSR, &cpu::ZPX, 6, 2 };
    tab[0x5E] = { "LSR", &cpu::LSR, &cpu::ABX, 7, 3 };
}

void instructions::PHA(cpu::opcode *tab) {
    tab[0x48] = { "PHA", &cpu::PHA, &cpu::IMP, 3, 1 };
}

void instructions::JMP(cpu::opcode *tab) {
    tab[0x4C] = { "JMP", &cpu::JMP, &cpu::ABS, 3, 3 };
    tab[0x6C] = { "JMP", &cpu::JMP, &cpu::IDABS, 5, 3 };
}

void instructions::BVC(cpu::opcode *tab) {
    tab[0x50] = { "BVC", &cpu::BVC, &cpu::REL, 2, 2 };
}

void instructions::CLI(cpu::opcode *tab) {
    tab[0x58] = { "CLI", &cpu::CLI, &cpu::IMP, 2, 1 };
}

void instructions::RTS(cpu::opcode *tab) {
    tab[0x60] = { "RTS", &cpu::RTS, &cpu::IMP, 6, 1 };
}

void instructions::ADC(cpu::opcode *tab) {
    tab[0x61] = { "ADC", &cpu::ADC, &cpu::IDZPX, 6, 2 };
    tab[0x65] = { "ADC", &cpu::ADC, &cpu::ZP, 3, 2 };
    tab[0x69] = { "ADC", &cpu::ADC, &cpu::IMM, 2, 2 };
    tab[0x6D] = { "ADC", &cpu::ADC, &cpu::ABS, 4, 3 };
    tab[0x71] = { "ADC", &cpu::ADC, &cpu::IDZPY, 5, 2 };
    tab[0x75] = { "ADC", &cpu::ADC, &cpu::ZPX, 4, 2 };
    tab[0x79] = { "ADC", &cpu::ADC, &cpu::ABY, 4, 3 };
    tab[0x7D] = { "ADC", &cpu::ADC, &cpu::ABX, 4, 3 };
}

void instructions::ROR(cpu::opcode *tab) {
    tab[0x66] = { "ROR", &cpu::ROR, &cpu::ZP, 5, 2 };
    tab[0x6A] = { "ROR", &cpu::ROR, &cpu::ACC, 2, 1 };
    tab[0x6E] = { "ROR", &cpu::ROR, &cpu::ABS, 6, 3 };
    tab[0x76] = { "ROR", &cpu::ROR, &cpu::ZPX, 6, 2 };
    tab[0x7E] = { "ROR", &cpu::ROR, &cpu::ABX, 7, 3 };
}

void instructions::PLA(cpu::opcode *tab) {
    tab[0x68] = { "PLA", &cpu::PLA, &cpu::IMP, 4, 1 };
}

void instructions::BVS(cpu::opcode *tab) {
    tab[0x70] = { "BVS", &cpu::BVS, &cpu::REL, 2, 2 };
}

void instructions::SEI(cpu::opcode *tab) {
    tab[0x78] = { "SEI", &cpu::SEI, &cpu::IMP, 2, 1 };
}

void instructions::STA(cpu::opcode *tab) {
    tab[0x81] = { "STA", &cpu::STA, &cpu::IDZPX, 6, 2 };
    tab[0x85] = { "STA", &cpu::STA, &cpu::ZP, 3, 2 };
    tab[0x8D] = { "STA", &cpu::STA, &cpu::ABS, 4, 3 };
    tab[0x91] = { "STA", &cpu::STA, &cpu::IDZPY, 6, 2 };
    tab[0x95] = { "STA", &cpu::STA, &cpu::ZPX, 4, 2 };
    tab[0x99] = { "STA", &cpu::STA, &cpu::ABY, 5, 3 };
    tab[0x9D] = { "STA", &cpu::STA, &cpu::ABX, 5, 3 };
}

void instructions::STY(cpu::opcode *tab) {
    tab[0x84] = { "STY", &cpu::STY, &cpu::ZP, 3, 2 };
    tab[0x8C] = { "STY", &cpu::STY, &cpu::ABS, 4, 3 };
    tab[0x94] = { "STY", &cpu::STY, &cpu::ZPX, 4, 2 };
}

void instructions::STX(cpu::opcode *tab) {
    tab[0x86] = { "STX", &cpu::STX, &cpu::ZP, 3, 2 };
    tab[0x8E] = { "STX", &cpu::STX, &cpu::ABS, 4, 3 };
    tab[0x96] = { "STX", &cpu::STX, &cpu::ZPY, 4, 2 };
}

void instructions::DEY(cpu::opcode *tab) {
    tab[0x88] = { "DEY", &cpu::DEY, &cpu::IMP, 2, 1 };
}

void instructions::TXA(cpu::opcode *tab) {
    tab[0x8A] = { "TXA", &cpu::TXA, &cpu::IMP, 2, 1 };
}

void instructions::BCC(cpu::opcode *tab) {
    tab[0x90] = { "BCC", &cpu::BCC, &cpu::REL, 2, 2 };
}

void instructions::TYA(cpu::opcode *tab) {
    tab[0x98] = { "TYA", &cpu::TYA, &cpu::IMP, 2, 1 };
}

void instructions::TXS(cpu::opcode *tab) {
    tab[0x9A] = { "TXS", &cpu::TXS, &cpu::IMP, 2, 1 };
}

void instructions::LDY(cpu::opcode *tab) {
    tab[0xA0] = { "LDY", &cpu::LDY, &cpu::IMM, 2, 2 };
    tab[0xA4] = { "LDY", &cpu::LDY, &cpu::ZP, 3, 2 };
    tab[0xAC] = { "LDY", &cpu::LDY, &cpu::ABS, 4, 3 };
    tab[0xB4] = { "LDY", &cpu::LDY, &cpu::ZPX, 4, 2 };
    tab[0xBC] = { "LDY", &cpu::LDY, &cpu::ABX, 4, 3 };
}

void instructions::LDA(cpu::opcode *tab) {
    tab[0xA1] = { "LDA", &cpu::LDA, &cpu::IDZPX, 6, 2 };
    tab[0xA5] = { "LDA", &cpu::LDA, &cpu::ZP, 3, 2 };
    tab[0xA9] = { "LDA", &cpu::LDA, &cpu::IMM, 2, 2 };
    tab[0xAD] = { "LDA", &cpu::LDA, &cpu::ABS, 4, 3 };
    tab[0xB1] = { "LDA", &cpu::LDA, &cpu::IDZPY, 5, 2 };
    tab[0xB5] = { "LDA", &cpu::LDA, &cpu::ZPX, 4, 2 };
    tab[0xB9] = { "LDA", &cpu::LDA, &cpu::ABY, 4, 3 };
    tab[0xBD] = { "LDA", &cpu::LDA, &cpu::ABX, 4, 3 };
}

void instructions::LDX(cpu::opcode *tab) {
    tab[0xA2] = { "LDX", &cpu::LDX, &cpu::IMM, 2, 2 };
    tab[0xA6] = { "LDX", &cpu::LDX, &cpu::ZP, 3, 2 };
    tab[0xAE] = { "LDX", &cpu::LDX, &cpu::ABS, 4, 3 };
    tab[0xB6] = { "LDX", &cpu::LDX, &cpu::ZPY, 4, 2 };
    tab[0xBE] = { "LDX", &cpu::LDX, &cpu::ABY, 4, 3 };
}

void instructions::TAY(cpu::opcode *tab) {
    tab[0xA8] = { "TAY", &cpu::TAY, &cpu::IMP, 2, 1 };
}

void instructions::TAX(cpu::opcode *tab) {
    tab[0xAA] = { "TAX", &cpu::TAX, &cpu::IMP, 2, 1 };
}

void instructions::BCS(cpu::opcode *tab) {
    tab[0xB0] = { "BCS", &cpu::BCS, &cpu::REL, 2, 2 };
}

void instructions::CLV(cpu::opcode *tab) {
    tab[0xB8] = { "CLV", &cpu::CLV, &cpu::IMP, 2, 1 };
}

void instructions::TSX(cpu::opcode *tab) {
    tab[0xBA] = { "TSX", &cpu::TSX, &cpu::IMP, 2, 1 };
}

void instructions::CPY(cpu::opcode *tab) {
    tab[0xC0] = { "CPY", &cpu::CPY, &cpu::IMM, 2, 2 };
    tab[0xC4] = { "CPY", &cpu::CPY, &cpu::ZP, 3, 2 };
    tab[0xCC] = { "CPY", &cpu::CPY, &cpu::ABS, 4, 3 };
}

void instructions::CMP(cpu::opcode *tab) {
    tab[0xC1] = { "CMP", &cpu::CMP, &cpu::IDZPX, 6, 2 };
    tab[0xC5] = { "CMP", &cpu::CMP, &cpu::ZP, 3, 2 };
    tab[0xC9] = { "CMP", &cpu::CMP, &cpu::IMM, 2, 2 };
    tab[0xCD] = { "CMP", &cpu::CMP, &cpu::ABS, 4, 3 };
    tab[0xD1] = { "CMP", &cpu::CMP, &cpu::IDZPY, 5, 2 };
    tab[0xD5] = { "CMP", &cpu::CMP, &cpu::ZPX, 4, 2 };
    tab[0xD9] = { "CMP", &cpu::CMP, &cpu::ABY, 4, 3 };
    tab[0xDD] = { "CMP", &cpu::CMP, &cpu::ABX, 4, 3 };
}

void instructions::DEC(cpu::opcode *tab) {
    tab[0xC6] = { "DEC", &cpu::DEC, &cpu::ZP, 5, 2 };
    tab[0xCE] = { "DEC", &cpu::DEC, &cpu::ABS, 6, 3 };
    tab[0xD6] = { "DEC", &cpu::DEC, &cpu::ZPX, 6, 2 };
    tab[0xDE] = { "DEC", &cpu::DEC, &cpu::ABX, 7, 3 };
}

void instructions::INY(cpu::opcode *tab) {
    tab[0xC8] = { "INY", &cpu::INY, &cpu::IMP, 2, 1 };
}

void instructions::DEX(cpu::opcode *tab) {
    tab[0xCA] = { "DEX", &cpu::DEX, &cpu::IMP, 2, 1 };
}

void instructions::BNE(cpu::opcode *tab) {
    tab[0xD0] = { "BNE", &cpu::BNE, &cpu::REL, 2, 2 };
}

void instructions::CLD(cpu::opcode *tab) {
    tab[0xD8] = { "CLD", &cpu::CLD, &cpu::IMP, 2, 1 };
}

void instructions::CPX(cpu::opcode *tab) {
    tab[0xE0] = { "CPX", &cpu::CPX, &cpu::IMM, 2, 2 };
    tab[0xE4] = { "CPX", &cpu::CPX, &cpu::ZP, 3, 2 };
    tab[0xEC] = { "CPX", &cpu::CPX, &cpu::ABS, 4, 3 };
}

void instructions::SBC(cpu::opcode *tab) {
    tab[0xE1] = { "SBC", &cpu::SBC, &cpu::IDZPX, 6, 2 };
    tab[0xE5] = { "SBC", &cpu::SBC, &cpu::ZP, 3, 2 };
    tab[0xE9] = { "SBC", &cpu::SBC, &cpu::IMM, 2, 2 };
    tab[0xED] = { "SBC", &cpu::SBC, &cpu::ABS, 4, 3 };
    tab[0xF1] = { "SBC", &cpu::SBC, &cpu::IDZPY, 5, 2 };
    tab[0xF5] = { "SBC", &cpu::SBC, &cpu::ZPX, 4, 2 };
    tab[0xF9] = { "SBC", &cpu::SBC, &cpu::ABY, 4, 3 };
    tab[0xFD] = { "SBC", &cpu::SBC, &cpu::ABX, 4, 3 };
}

void instructions::INC(cpu::opcode *tab) {
    tab[0xE6] = { "INC", &cpu::INC, &cpu::ZP, 5, 2 };
    tab[0xEE] = { "INC", &cpu::INC, &cpu::ABS, 6, 3 };
    tab[0xF6] = { "INC", &cpu::INC, &cpu::ZPX, 6, 2 };
    tab[0xFE] = { "INC", &cpu::INC, &cpu::ABX, 7, 3 };
}

void instructions::INX(cpu::opcode *tab) {
    tab[0xE8] = { "INX", &cpu::INX, &cpu::IMP, 2, 1 };
}

void instructions::NOP(cpu::opcode *tab) {
    tab[0xEA] = { "NOP", &cpu::NOP, &cpu::IMP, 2, 1 };
}

void instructions::BEQ(cpu::opcode *tab) {
    tab[0xF0] = { "BEQ", &cpu::BEQ, &cpu::REL, 2, 2 };
}

void instructions::SED(cpu::opcode *tab) {
    tab[0xF8] = { "SED", &cpu::SED, &cpu::IMP, 2, 1 };
}

void instructions::undocumented(cpu::opcode *tab) {
    // I'm not sure we will need these...

    // tab[0x02] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// tab[0x03] = { "*SLO", &cpu::*SLO, &cpu::IDZPX, 8, 2 };
	// tab[0x04] = { "*NOP", &cpu::*NOP, &cpu::ZP, 3, 2 };
	// tab[0x07] = { "*SLO", &cpu::*SLO, &cpu::ZP, 5, 2 };
	// tab[0x0B] = { "*ANC", &cpu::*ANC, &cpu::IMM, 2, 2 };
	// tab[0x0C] = { "*NOP", &cpu::*NOP, &cpu::ABS, 4, 3 };
	// tab[0x0F] = { "*SLO", &cpu::*SLO, &cpu::ABS, 6, 3 };
	// tab[0x12] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// tab[0x13] = { "*SLO", &cpu::*SLO, &cpu::IDZPY, 8, 2 };
	// tab[0x14] = { "*NOP", &cpu::*NOP, &cpu::ZPX, 4, 2 };
	// tab[0x17] = { "*SLO", &cpu::*SLO, &cpu::ZPX, 6, 2 };
	// tab[0x1A] = { "*NOP", &cpu::*NOP, &cpu::IMP, 2, 1 };
	// tab[0x1B] = { "*SLO", &cpu::*SLO, &cpu::ABY, 7, 3 };
	// tab[0x1C] = { "*NOP", &cpu::*NOP, &cpu::ABX, 4, 3 };
	// tab[0x1F] = { "*SLO", &cpu::*SLO, &cpu::ABX, 7, 3 };
	// tab[0x22] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// tab[0x23] = { "*RLA", &cpu::*RLA, &cpu::IDZPX, 8, 2 };
	// tab[0x27] = { "*RLA", &cpu::*RLA, &cpu::ZP, 5, 2 };
	// tab[0x2B] = { "*ANC", &cpu::*ANC, &cpu::IMM, 2, 2 };
	// tab[0x2F] = { "*RLA", &cpu::*RLA, &cpu::ABS, 6, 3 };
	// tab[0x32] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// tab[0x33] = { "*RLA", &cpu::*RLA, &cpu::IDZPY, 8, 2 };
	// tab[0x34] = { "*NOP", &cpu::*NOP, &cpu::ZPX, 4, 2 };
	// tab[0x37] = { "*RLA", &cpu::*RLA, &cpu::ZPX, 6, 2 };
	// tab[0x3A] = { "*NOP", &cpu::*NOP, &cpu::IMP, 2, 1 };
	// tab[0x3B] = { "*RLA", &cpu::*RLA, &cpu::ABY, 7, 3 };
	// tab[0x3C] = { "*NOP", &cpu::*NOP, &cpu::ABX, 4, 3 };
	// tab[0x3F] = { "*RLA", &cpu::*RLA, &cpu::ABX, 7, 3 };
	// tab[0x42] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// tab[0x43] = { "*SRE", &cpu::*SRE, &cpu::IDZPX, 8, 2 };
	// tab[0x44] = { "*NOP", &cpu::*NOP, &cpu::ZP, 3, 2 };
	// tab[0x47] = { "*SRE", &cpu::*SRE, &cpu::ZP, 5, 2 };
	// tab[0x4B] = { "*ASR", &cpu::*ASR, &cpu::IMM, 2, 2 };
	// tab[0x4F] = { "*SRE", &cpu::*SRE, &cpu::ABS, 6, 3 };
	// tab[0x52] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// tab[0x53] = { "*SRE", &cpu::*SRE, &cpu::IDZPY, 8, 2 };
	// tab[0x54] = { "*NOP", &cpu::*NOP, &cpu::ZPX, 4, 2 };
	// tab[0x57] = { "*SRE", &cpu::*SRE, &cpu::ZPX, 6, 2 };
	// tab[0x5A] = { "*NOP", &cpu::*NOP, &cpu::IMP, 2, 1 };
	// tab[0x5B] = { "*SRE", &cpu::*SRE, &cpu::ABY, 7, 3 };
	// tab[0x5C] = { "*NOP", &cpu::*NOP, &cpu::ABX, 4, 3 };
	// tab[0x5F] = { "*SRE", &cpu::*SRE, &cpu::ABX, 7, 3 };
	// tab[0x62] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// tab[0x63] = { "*RRA", &cpu::*RRA, &cpu::IDZPX, 8, 2 };
	// tab[0x64] = { "*NOP", &cpu::*NOP, &cpu::ZP, 3, 2 };
	// tab[0x67] = { "*RRA", &cpu::*RRA, &cpu::ZP, 5, 2 };
	// tab[0x6B] = { "*ARR", &cpu::*ARR, &cpu::IMM, 2, 2 };
	// tab[0x6F] = { "*RRA", &cpu::*RRA, &cpu::ABS, 6, 3 };
	// tab[0x72] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// tab[0x73] = { "*RRA", &cpu::*RRA, &cpu::IDZPY, 8, 2 };
	// tab[0x74] = { "*NOP", &cpu::*NOP, &cpu::ZPX, 4, 2 };
	// tab[0x77] = { "*RRA", &cpu::*RRA, &cpu::ZPX, 6, 2 };
	// tab[0x7A] = { "*NOP", &cpu::*NOP, &cpu::IMP, 2, 1 };
	// tab[0x7B] = { "*RRA", &cpu::*RRA, &cpu::ABY, 7, 3 };
	// tab[0x7C] = { "*NOP", &cpu::*NOP, &cpu::ABX, 4, 3 };
	// tab[0x7F] = { "*RRA", &cpu::*RRA, &cpu::ABX, 7, 3 };
	// tab[0x80] = { "*NOP", &cpu::*NOP, &cpu::IMM, 2, 2 };
	// tab[0x82] = { "*NOP", &cpu::*NOP, &cpu::IMM, 2, 2 };
	// tab[0x83] = { "*SAX", &cpu::*SAX, &cpu::IDZPX, 6, 2 };
	// tab[0x87] = { "*SAX", &cpu::*SAX, &cpu::ZP, 3, 2 };
	// tab[0x89] = { "*NOP", &cpu::*NOP, &cpu::IMM, 2, 2 };
	// tab[0x8B] = { "*XAA", &cpu::*XAA, &cpu::IMM, 2, 2 };
	// tab[0x8F] = { "*SAX", &cpu::*SAX, &cpu::ABS, 4, 3 };
	// tab[0x92] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// tab[0x93] = { "*SHA", &cpu::*SHA, &cpu::IDZPY, 6, 2 };
	// tab[0x97] = { "*SAX", &cpu::*SAX, &cpu::ZPY, 4, 2 };
	// tab[0x9B] = { "*SHS", &cpu::*SHS, &cpu::ABY, 5, 3 };
	// tab[0x9C] = { "*SHY", &cpu::*SHY, &cpu::ABX, 5, 3 };
	// tab[0x9E] = { "*SHX", &cpu::*SHX, &cpu::ABY, 5, 3 };
	// tab[0x9F] = { "*SHA", &cpu::*SHA, &cpu::ABY, 5, 3 };
	// tab[0xA3] = { "*LAX", &cpu::*LAX, &cpu::IDZPX, 6, 2 };
	// tab[0xA7] = { "*LAX", &cpu::*LAX, &cpu::ZP, 3, 2 };
	// tab[0xAB] = { "*LAX", &cpu::*LAX, &cpu::IMM, 2, 2 };
	// tab[0xAF] = { "*LAX", &cpu::*LAX, &cpu::ABS, 4, 3 };
	// tab[0xB2] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// tab[0xB3] = { "*LAX", &cpu::*LAX, &cpu::IDZPY, 5, 2 };
	// tab[0xB7] = { "*LAX", &cpu::*LAX, &cpu::ZPY, 4, 2 };
	// tab[0xBB] = { "*LAS", &cpu::*LAS, &cpu::ABY, 4, 3 };
	// tab[0xBF] = { "*LAX", &cpu::*LAX, &cpu::ABY, 4, 3 };
	// tab[0xC2] = { "*NOP", &cpu::*NOP, &cpu::IMM, 2, 2 };
	// tab[0xC3] = { "*DCP", &cpu::*DCP, &cpu::IDZPX, 8, 2 };
	// tab[0xC7] = { "*DCP", &cpu::*DCP, &cpu::ZP, 5, 2 };
	// tab[0xCB] = { "*SBX", &cpu::*SBX, &cpu::IMM, 2, 2 };
	// tab[0xCF] = { "*DCP", &cpu::*DCP, &cpu::ABS, 6, 3 };
	// tab[0xD2] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// tab[0xD3] = { "*DCP", &cpu::*DCP, &cpu::IDZPY, 8, 2 };
	// tab[0xD4] = { "*NOP", &cpu::*NOP, &cpu::ZPX, 4, 2 };
	// tab[0xD7] = { "*DCP", &cpu::*DCP, &cpu::ZPX, 6, 2 };
	// tab[0xDA] = { "*NOP", &cpu::*NOP, &cpu::IMP, 2, 1 };
	// tab[0xDB] = { "*DCP", &cpu::*DCP, &cpu::ABY, 7, 3 };
	// tab[0xDC] = { "*NOP", &cpu::*NOP, &cpu::ABX, 4, 3 };
	// tab[0xDF] = { "*DCP", &cpu::*DCP, &cpu::ABX, 7, 3 };
	// tab[0xE2] = { "*NOP", &cpu::*NOP, &cpu::IMM, 2, 2 };
	// tab[0xE3] = { "*ISC", &cpu::*ISC, &cpu::IDZPX, 8, 2 };
	// tab[0xE7] = { "*ISC", &cpu::*ISC, &cpu::ZP, 5, 2 };
	// tab[0xEB] = { "*SBC", &cpu::*SBC, &cpu::IMM, 2, 2 };
	// tab[0xEF] = { "*ISC", &cpu::*ISC, &cpu::ABS, 6, 3 };
	// tab[0xF2] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// tab[0xF3] = { "*ISC", &cpu::*ISC, &cpu::IDZPY, 8, 2 };
	// tab[0xF4] = { "*NOP", &cpu::*NOP, &cpu::ZPX, 4, 2 };
	// tab[0xF7] = { "*ISC", &cpu::*ISC, &cpu::ZPX, 6, 2 };
	// tab[0xFA] = { "*NOP", &cpu::*NOP, &cpu::IMP, 2, 1 };
	// tab[0xFB] = { "*ISC", &cpu::*ISC, &cpu::ABY, 7, 3 };
	// tab[0xFC] = { "*NOP", &cpu::*NOP, &cpu::ABX, 4, 3 };
	// tab[0xFF] = { "*ISC", &cpu::*ISC, &cpu::ABX, 7, 3 };
}