#include "cpu.h"
#include "system.h"

void cpu::setup()
{
	opcode_set[0x00] = { "BRK", &cpu::BRK, &cpu::IMP, 7, 1 };
	opcode_set[0x01] = { "ORA", &cpu::ORA, &cpu::IDZPX, 6, 2 };
	opcode_set[0x05] = { "ORA", &cpu::ORA, &cpu::ZP, 3, 2 };
	opcode_set[0x06] = { "ASL", &cpu::ASL, &cpu::ZP, 5, 2 };
	opcode_set[0x08] = { "PHP", &cpu::PHP, &cpu::IMP, 3, 1 };
	opcode_set[0x09] = { "ORA", &cpu::ORA, &cpu::IMM, 2, 2 };
	opcode_set[0x0A] = { "ASL", &cpu::ASL, &cpu::ACC, 2, 1 };
	opcode_set[0x0D] = { "ORA", &cpu::ORA, &cpu::ABS, 4, 3 };
	opcode_set[0x0E] = { "ASL", &cpu::ASL, &cpu::ABS, 6, 3 };
	opcode_set[0x10] = { "BPL", &cpu::BPL, &cpu::REL, 2, 2 };
	opcode_set[0x11] = { "ORA", &cpu::ORA, &cpu::IDZPY, 5, 2 };
	opcode_set[0x15] = { "ORA", &cpu::ORA, &cpu::ZPX, 4, 2 };
	opcode_set[0x16] = { "ASL", &cpu::ASL, &cpu::ZPX, 6, 2 };
	opcode_set[0x18] = { "CLC", &cpu::CLC, &cpu::IMP, 2, 1 };
	opcode_set[0x19] = { "ORA", &cpu::ORA, &cpu::ABY, 4, 3 };
	opcode_set[0x1D] = { "ORA", &cpu::ORA, &cpu::ABX, 4, 3 };
	opcode_set[0x1E] = { "ASL", &cpu::ASL, &cpu::ABX, 7, 3 };
	opcode_set[0x20] = { "JSR", &cpu::JSR, &cpu::ABS, 6, 3 };
	opcode_set[0x21] = { "AND", &cpu::AND, &cpu::IDZPX, 6, 2 };
	opcode_set[0x24] = { "BIT", &cpu::BIT, &cpu::ZP, 3, 2 };
	opcode_set[0x25] = { "AND", &cpu::AND, &cpu::ZP, 3, 2 };
	opcode_set[0x26] = { "ROL", &cpu::ROL, &cpu::ZP, 5, 2 };
	opcode_set[0x28] = { "PLP", &cpu::PLP, &cpu::IMP, 4, 1 };
	opcode_set[0x29] = { "AND", &cpu::AND, &cpu::IMM, 2, 2 };
	opcode_set[0x2A] = { "ROL", &cpu::ROL, &cpu::ACC, 2, 1 };
	opcode_set[0x2C] = { "BIT", &cpu::BIT, &cpu::ABS, 4, 3 };
	opcode_set[0x2D] = { "AND", &cpu::AND, &cpu::ABS, 4, 3 };
	opcode_set[0x2E] = { "ROL", &cpu::ROL, &cpu::ABS, 6, 3 };
	opcode_set[0x30] = { "BMI", &cpu::BMI, &cpu::REL, 2, 2 };
	opcode_set[0x31] = { "AND", &cpu::AND, &cpu::IDZPY, 5, 2 };
	opcode_set[0x35] = { "AND", &cpu::AND, &cpu::ZPX, 4, 2 };
	opcode_set[0x36] = { "ROL", &cpu::ROL, &cpu::ZPX, 6, 2 };
	opcode_set[0x38] = { "SEC", &cpu::SEC, &cpu::IMP, 2, 1 };
	opcode_set[0x39] = { "AND", &cpu::AND, &cpu::ABY, 4, 3 };
	opcode_set[0x3D] = { "AND", &cpu::AND, &cpu::ABX, 4, 3 };
	opcode_set[0x3E] = { "ROL", &cpu::ROL, &cpu::ABX, 7, 3 };
	opcode_set[0x40] = { "RTI", &cpu::RTI, &cpu::IMP, 6, 1 };
	opcode_set[0x41] = { "EOR", &cpu::EOR, &cpu::IDZPX, 6, 2 };
	opcode_set[0x45] = { "EOR", &cpu::EOR, &cpu::ZP, 3, 2 };
	opcode_set[0x46] = { "LSR", &cpu::LSR, &cpu::ZP, 5, 2 };
	opcode_set[0x48] = { "PHA", &cpu::PHA, &cpu::IMP, 3, 1 };
	opcode_set[0x49] = { "EOR", &cpu::EOR, &cpu::IMM, 2, 2 };
	opcode_set[0x4A] = { "LSR", &cpu::LSR, &cpu::ACC, 2, 1 };
	opcode_set[0x4C] = { "JMP", &cpu::JMP, &cpu::ABS, 3, 3 };
	opcode_set[0x4D] = { "EOR", &cpu::EOR, &cpu::ABS, 4, 3 };
	opcode_set[0x4E] = { "LSR", &cpu::LSR, &cpu::ABS, 6, 3 };
	opcode_set[0x50] = { "BVC", &cpu::BVC, &cpu::REL, 2, 2 };
	opcode_set[0x51] = { "EOR", &cpu::EOR, &cpu::IDZPY, 5, 2 };
	opcode_set[0x55] = { "EOR", &cpu::EOR, &cpu::ZPX, 4, 2 };
	opcode_set[0x56] = { "LSR", &cpu::LSR, &cpu::ZPX, 6, 2 };
	opcode_set[0x58] = { "CLI", &cpu::CLI, &cpu::IMP, 2, 1 };
	opcode_set[0x59] = { "EOR", &cpu::EOR, &cpu::ABY, 4, 3 };
	opcode_set[0x5D] = { "EOR", &cpu::EOR, &cpu::ABX, 4, 3 };
	opcode_set[0x5E] = { "LSR", &cpu::LSR, &cpu::ABX, 7, 3 };
	opcode_set[0x60] = { "RTS", &cpu::RTS, &cpu::IMP, 6, 1 };
	opcode_set[0x61] = { "ADC", &cpu::ADC, &cpu::IDZPX, 6, 2 };
	opcode_set[0x65] = { "ADC", &cpu::ADC, &cpu::ZP, 3, 2 };
	opcode_set[0x66] = { "ROR", &cpu::ROR, &cpu::ZP, 5, 2 };
	opcode_set[0x68] = { "PLA", &cpu::PLA, &cpu::IMP, 4, 1 };
	opcode_set[0x69] = { "ADC", &cpu::ADC, &cpu::IMM, 2, 2 };
	opcode_set[0x6A] = { "ROR", &cpu::ROR, &cpu::ACC, 2, 1 };
	opcode_set[0x6C] = { "JMP", &cpu::JMP, &cpu::IDABS, 5, 3 };
	opcode_set[0x6D] = { "ADC", &cpu::ADC, &cpu::ABS, 4, 3 };
	opcode_set[0x6E] = { "ROR", &cpu::ROR, &cpu::ABS, 6, 3 };
	opcode_set[0x70] = { "BVS", &cpu::BVS, &cpu::REL, 2, 2 };
	opcode_set[0x71] = { "ADC", &cpu::ADC, &cpu::IDZPY, 5, 2 };
	opcode_set[0x75] = { "ADC", &cpu::ADC, &cpu::ZPX, 4, 2 };
	opcode_set[0x76] = { "ROR", &cpu::ROR, &cpu::ZPX, 6, 2 };
	opcode_set[0x78] = { "SEI", &cpu::SEI, &cpu::IMP, 2, 1 };
	opcode_set[0x79] = { "ADC", &cpu::ADC, &cpu::ABY, 4, 3 };
	opcode_set[0x7D] = { "ADC", &cpu::ADC, &cpu::ABX, 4, 3 };
	opcode_set[0x7E] = { "ROR", &cpu::ROR, &cpu::ABX, 7, 3 };
	opcode_set[0x81] = { "STA", &cpu::STA, &cpu::IDZPX, 6, 2 };
	opcode_set[0x84] = { "STY", &cpu::STY, &cpu::ZP, 3, 2 };
	opcode_set[0x85] = { "STA", &cpu::STA, &cpu::ZP, 3, 2 };
	opcode_set[0x86] = { "STX", &cpu::STX, &cpu::ZP, 3, 2 };
	opcode_set[0x88] = { "DEY", &cpu::DEY, &cpu::IMP, 2, 1 };
	opcode_set[0x8A] = { "TXA", &cpu::TXA, &cpu::IMP, 2, 1 };
	opcode_set[0x8C] = { "STY", &cpu::STY, &cpu::ABS, 4, 3 };
	opcode_set[0x8D] = { "STA", &cpu::STA, &cpu::ABS, 4, 3 };
	opcode_set[0x8E] = { "STX", &cpu::STX, &cpu::ABS, 4, 3 };
	opcode_set[0x90] = { "BCC", &cpu::BCC, &cpu::REL, 2, 2 };
	opcode_set[0x91] = { "STA", &cpu::STA, &cpu::IDZPY, 6, 2 };
	opcode_set[0x94] = { "STY", &cpu::STY, &cpu::ZPX, 4, 2 };
	opcode_set[0x95] = { "STA", &cpu::STA, &cpu::ZPX, 4, 2 };
	opcode_set[0x96] = { "STX", &cpu::STX, &cpu::ZPY, 4, 2 };
	opcode_set[0x98] = { "TYA", &cpu::TYA, &cpu::IMP, 2, 1 };
	opcode_set[0x99] = { "STA", &cpu::STA, &cpu::ABY, 5, 3 };
	opcode_set[0x9A] = { "TXS", &cpu::TXS, &cpu::IMP, 2, 1 };
	opcode_set[0x9D] = { "STA", &cpu::STA, &cpu::ABX, 5, 3 };
	opcode_set[0xA0] = { "LDY", &cpu::LDY, &cpu::IMM, 2, 2 };
	opcode_set[0xA1] = { "LDA", &cpu::LDA, &cpu::IDZPX, 6, 2 };
	opcode_set[0xA2] = { "LDX", &cpu::LDX, &cpu::IMM, 2, 2 };
	opcode_set[0xA4] = { "LDY", &cpu::LDY, &cpu::ZP, 3, 2 };
	opcode_set[0xA5] = { "LDA", &cpu::LDA, &cpu::ZP, 3, 2 };
	opcode_set[0xA6] = { "LDX", &cpu::LDX, &cpu::ZP, 3, 2 };
	opcode_set[0xA8] = { "TAY", &cpu::TAY, &cpu::IMP, 2, 1 };
	opcode_set[0xA9] = { "LDA", &cpu::LDA, &cpu::IMM, 2, 2 };
	opcode_set[0xAA] = { "TAX", &cpu::TAX, &cpu::IMP, 2, 1 };
	opcode_set[0xAC] = { "LDY", &cpu::LDY, &cpu::ABS, 4, 3 };
	opcode_set[0xAD] = { "LDA", &cpu::LDA, &cpu::ABS, 4, 3 };
	opcode_set[0xAE] = { "LDX", &cpu::LDX, &cpu::ABS, 4, 3 };
	opcode_set[0xB0] = { "BCS", &cpu::BCS, &cpu::REL, 2, 2 };
	opcode_set[0xB1] = { "LDA", &cpu::LDA, &cpu::IDZPY, 5, 2 };
	opcode_set[0xB4] = { "LDY", &cpu::LDY, &cpu::ZPX, 4, 2 };
	opcode_set[0xB5] = { "LDA", &cpu::LDA, &cpu::ZPX, 4, 2 };
	opcode_set[0xB6] = { "LDX", &cpu::LDX, &cpu::ZPY, 4, 2 };
	opcode_set[0xB8] = { "CLV", &cpu::CLV, &cpu::IMP, 2, 1 };
	opcode_set[0xB9] = { "LDA", &cpu::LDA, &cpu::ABY, 4, 3 };
	opcode_set[0xBA] = { "TSX", &cpu::TSX, &cpu::IMP, 2, 1 };
	opcode_set[0xBC] = { "LDY", &cpu::LDY, &cpu::ABX, 4, 3 };
	opcode_set[0xBD] = { "LDA", &cpu::LDA, &cpu::ABX, 4, 3 };
	opcode_set[0xBE] = { "LDX", &cpu::LDX, &cpu::ABY, 4, 3 };
	opcode_set[0xC0] = { "CPY", &cpu::CPY, &cpu::IMM, 2, 2 };
	opcode_set[0xC1] = { "CMP", &cpu::CMP, &cpu::IDZPX, 6, 2 };
	opcode_set[0xC4] = { "CPY", &cpu::CPY, &cpu::ZP, 3, 2 };
	opcode_set[0xC5] = { "CMP", &cpu::CMP, &cpu::ZP, 3, 2 };
	opcode_set[0xC6] = { "DEC", &cpu::DEC, &cpu::ZP, 5, 2 };
	opcode_set[0xC8] = { "INY", &cpu::INY, &cpu::IMP, 2, 1 };
	opcode_set[0xC9] = { "CMP", &cpu::CMP, &cpu::IMM, 2, 2 };
	opcode_set[0xCA] = { "DEX", &cpu::DEX, &cpu::IMP, 2, 1 };
	opcode_set[0xCC] = { "CPY", &cpu::CPY, &cpu::ABS, 4, 3 };
	opcode_set[0xCD] = { "CMP", &cpu::CMP, &cpu::ABS, 4, 3 };
	opcode_set[0xCE] = { "DEC", &cpu::DEC, &cpu::ABS, 6, 3 };
	opcode_set[0xD0] = { "BNE", &cpu::BNE, &cpu::REL, 2, 2 };
	opcode_set[0xD1] = { "CMP", &cpu::CMP, &cpu::IDZPY, 5, 2 };
	opcode_set[0xD5] = { "CMP", &cpu::CMP, &cpu::ZPX, 4, 2 };
	opcode_set[0xD6] = { "DEC", &cpu::DEC, &cpu::ZPX, 6, 2 };
	opcode_set[0xD8] = { "CLD", &cpu::CLD, &cpu::IMP, 2, 1 };
	opcode_set[0xD9] = { "CMP", &cpu::CMP, &cpu::ABY, 4, 3 };
	opcode_set[0xDD] = { "CMP", &cpu::CMP, &cpu::ABX, 4, 3 };
	opcode_set[0xDE] = { "DEC", &cpu::DEC, &cpu::ABX, 7, 3 };
	opcode_set[0xE0] = { "CPX", &cpu::CPX, &cpu::IMM, 2, 2 };
	opcode_set[0xE1] = { "SBC", &cpu::SBC, &cpu::IDZPX, 6, 2 };
	opcode_set[0xE4] = { "CPX", &cpu::CPX, &cpu::ZP, 3, 2 };
	opcode_set[0xE5] = { "SBC", &cpu::SBC, &cpu::ZP, 3, 2 };
	opcode_set[0xE6] = { "INC", &cpu::INC, &cpu::ZP, 5, 2 };
	opcode_set[0xE8] = { "INX", &cpu::INX, &cpu::IMP, 2, 1 };
	opcode_set[0xE9] = { "SBC", &cpu::SBC, &cpu::IMM, 2, 2 };
	opcode_set[0xEA] = { "NOP", &cpu::NOP, &cpu::IMP, 2, 1 };
	opcode_set[0xEC] = { "CPX", &cpu::CPX, &cpu::ABS, 4, 3 };
	opcode_set[0xED] = { "SBC", &cpu::SBC, &cpu::ABS, 4, 3 };
	opcode_set[0xEE] = { "INC", &cpu::INC, &cpu::ABS, 6, 3 };
	opcode_set[0xF0] = { "BEQ", &cpu::BEQ, &cpu::REL, 2, 2 };
	opcode_set[0xF1] = { "SBC", &cpu::SBC, &cpu::IDZPY, 5, 2 };
	opcode_set[0xF5] = { "SBC", &cpu::SBC, &cpu::ZPX, 4, 2 };
	opcode_set[0xF6] = { "INC", &cpu::INC, &cpu::ZPX, 6, 2 };
	opcode_set[0xF8] = { "SED", &cpu::SED, &cpu::IMP, 2, 1 };
	opcode_set[0xF9] = { "SBC", &cpu::SBC, &cpu::ABY, 4, 3 };
	opcode_set[0xFD] = { "SBC", &cpu::SBC, &cpu::ABX, 4, 3 };
	opcode_set[0xFE] = { "INC", &cpu::INC, &cpu::ABX, 7, 3 };
	// opcode_set[0x02] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// opcode_set[0x03] = { "*SLO", &cpu::*SLO, &cpu::IDZPX, 8, 2 };
	// opcode_set[0x04] = { "*NOP", &cpu::*NOP, &cpu::ZP, 3, 2 };
	// opcode_set[0x07] = { "*SLO", &cpu::*SLO, &cpu::ZP, 5, 2 };
	// opcode_set[0x0B] = { "*ANC", &cpu::*ANC, &cpu::IMM, 2, 2 };
	// opcode_set[0x0C] = { "*NOP", &cpu::*NOP, &cpu::ABS, 4, 3 };
	// opcode_set[0x0F] = { "*SLO", &cpu::*SLO, &cpu::ABS, 6, 3 };
	// opcode_set[0x12] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// opcode_set[0x13] = { "*SLO", &cpu::*SLO, &cpu::IDZPY, 8, 2 };
	// opcode_set[0x14] = { "*NOP", &cpu::*NOP, &cpu::ZPX, 4, 2 };
	// opcode_set[0x17] = { "*SLO", &cpu::*SLO, &cpu::ZPX, 6, 2 };
	// opcode_set[0x1A] = { "*NOP", &cpu::*NOP, &cpu::IMP, 2, 1 };
	// opcode_set[0x1B] = { "*SLO", &cpu::*SLO, &cpu::ABY, 7, 3 };
	// opcode_set[0x1C] = { "*NOP", &cpu::*NOP, &cpu::ABX, 4, 3 };
	// opcode_set[0x1F] = { "*SLO", &cpu::*SLO, &cpu::ABX, 7, 3 };
	// opcode_set[0x22] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// opcode_set[0x23] = { "*RLA", &cpu::*RLA, &cpu::IDZPX, 8, 2 };
	// opcode_set[0x27] = { "*RLA", &cpu::*RLA, &cpu::ZP, 5, 2 };
	// opcode_set[0x2B] = { "*ANC", &cpu::*ANC, &cpu::IMM, 2, 2 };
	// opcode_set[0x2F] = { "*RLA", &cpu::*RLA, &cpu::ABS, 6, 3 };
	// opcode_set[0x32] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// opcode_set[0x33] = { "*RLA", &cpu::*RLA, &cpu::IDZPY, 8, 2 };
	// opcode_set[0x34] = { "*NOP", &cpu::*NOP, &cpu::ZPX, 4, 2 };
	// opcode_set[0x37] = { "*RLA", &cpu::*RLA, &cpu::ZPX, 6, 2 };
	// opcode_set[0x3A] = { "*NOP", &cpu::*NOP, &cpu::IMP, 2, 1 };
	// opcode_set[0x3B] = { "*RLA", &cpu::*RLA, &cpu::ABY, 7, 3 };
	// opcode_set[0x3C] = { "*NOP", &cpu::*NOP, &cpu::ABX, 4, 3 };
	// opcode_set[0x3F] = { "*RLA", &cpu::*RLA, &cpu::ABX, 7, 3 };
	// opcode_set[0x42] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// opcode_set[0x43] = { "*SRE", &cpu::*SRE, &cpu::IDZPX, 8, 2 };
	// opcode_set[0x44] = { "*NOP", &cpu::*NOP, &cpu::ZP, 3, 2 };
	// opcode_set[0x47] = { "*SRE", &cpu::*SRE, &cpu::ZP, 5, 2 };
	// opcode_set[0x4B] = { "*ASR", &cpu::*ASR, &cpu::IMM, 2, 2 };
	// opcode_set[0x4F] = { "*SRE", &cpu::*SRE, &cpu::ABS, 6, 3 };
	// opcode_set[0x52] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// opcode_set[0x53] = { "*SRE", &cpu::*SRE, &cpu::IDZPY, 8, 2 };
	// opcode_set[0x54] = { "*NOP", &cpu::*NOP, &cpu::ZPX, 4, 2 };
	// opcode_set[0x57] = { "*SRE", &cpu::*SRE, &cpu::ZPX, 6, 2 };
	// opcode_set[0x5A] = { "*NOP", &cpu::*NOP, &cpu::IMP, 2, 1 };
	// opcode_set[0x5B] = { "*SRE", &cpu::*SRE, &cpu::ABY, 7, 3 };
	// opcode_set[0x5C] = { "*NOP", &cpu::*NOP, &cpu::ABX, 4, 3 };
	// opcode_set[0x5F] = { "*SRE", &cpu::*SRE, &cpu::ABX, 7, 3 };
	// opcode_set[0x62] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// opcode_set[0x63] = { "*RRA", &cpu::*RRA, &cpu::IDZPX, 8, 2 };
	// opcode_set[0x64] = { "*NOP", &cpu::*NOP, &cpu::ZP, 3, 2 };
	// opcode_set[0x67] = { "*RRA", &cpu::*RRA, &cpu::ZP, 5, 2 };
	// opcode_set[0x6B] = { "*ARR", &cpu::*ARR, &cpu::IMM, 2, 2 };
	// opcode_set[0x6F] = { "*RRA", &cpu::*RRA, &cpu::ABS, 6, 3 };
	// opcode_set[0x72] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// opcode_set[0x73] = { "*RRA", &cpu::*RRA, &cpu::IDZPY, 8, 2 };
	// opcode_set[0x74] = { "*NOP", &cpu::*NOP, &cpu::ZPX, 4, 2 };
	// opcode_set[0x77] = { "*RRA", &cpu::*RRA, &cpu::ZPX, 6, 2 };
	// opcode_set[0x7A] = { "*NOP", &cpu::*NOP, &cpu::IMP, 2, 1 };
	// opcode_set[0x7B] = { "*RRA", &cpu::*RRA, &cpu::ABY, 7, 3 };
	// opcode_set[0x7C] = { "*NOP", &cpu::*NOP, &cpu::ABX, 4, 3 };
	// opcode_set[0x7F] = { "*RRA", &cpu::*RRA, &cpu::ABX, 7, 3 };
	// opcode_set[0x80] = { "*NOP", &cpu::*NOP, &cpu::IMM, 2, 2 };
	// opcode_set[0x82] = { "*NOP", &cpu::*NOP, &cpu::IMM, 2, 2 };
	// opcode_set[0x83] = { "*SAX", &cpu::*SAX, &cpu::IDZPX, 6, 2 };
	// opcode_set[0x87] = { "*SAX", &cpu::*SAX, &cpu::ZP, 3, 2 };
	// opcode_set[0x89] = { "*NOP", &cpu::*NOP, &cpu::IMM, 2, 2 };
	// opcode_set[0x8B] = { "*XAA", &cpu::*XAA, &cpu::IMM, 2, 2 };
	// opcode_set[0x8F] = { "*SAX", &cpu::*SAX, &cpu::ABS, 4, 3 };
	// opcode_set[0x92] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// opcode_set[0x93] = { "*SHA", &cpu::*SHA, &cpu::IDZPY, 6, 2 };
	// opcode_set[0x97] = { "*SAX", &cpu::*SAX, &cpu::ZPY, 4, 2 };
	// opcode_set[0x9B] = { "*SHS", &cpu::*SHS, &cpu::ABY, 5, 3 };
	// opcode_set[0x9C] = { "*SHY", &cpu::*SHY, &cpu::ABX, 5, 3 };
	// opcode_set[0x9E] = { "*SHX", &cpu::*SHX, &cpu::ABY, 5, 3 };
	// opcode_set[0x9F] = { "*SHA", &cpu::*SHA, &cpu::ABY, 5, 3 };
	// opcode_set[0xA3] = { "*LAX", &cpu::*LAX, &cpu::IDZPX, 6, 2 };
	// opcode_set[0xA7] = { "*LAX", &cpu::*LAX, &cpu::ZP, 3, 2 };
	// opcode_set[0xAB] = { "*LAX", &cpu::*LAX, &cpu::IMM, 2, 2 };
	// opcode_set[0xAF] = { "*LAX", &cpu::*LAX, &cpu::ABS, 4, 3 };
	// opcode_set[0xB2] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// opcode_set[0xB3] = { "*LAX", &cpu::*LAX, &cpu::IDZPY, 5, 2 };
	// opcode_set[0xB7] = { "*LAX", &cpu::*LAX, &cpu::ZPY, 4, 2 };
	// opcode_set[0xBB] = { "*LAS", &cpu::*LAS, &cpu::ABY, 4, 3 };
	// opcode_set[0xBF] = { "*LAX", &cpu::*LAX, &cpu::ABY, 4, 3 };
	// opcode_set[0xC2] = { "*NOP", &cpu::*NOP, &cpu::IMM, 2, 2 };
	// opcode_set[0xC3] = { "*DCP", &cpu::*DCP, &cpu::IDZPX, 8, 2 };
	// opcode_set[0xC7] = { "*DCP", &cpu::*DCP, &cpu::ZP, 5, 2 };
	// opcode_set[0xCB] = { "*SBX", &cpu::*SBX, &cpu::IMM, 2, 2 };
	// opcode_set[0xCF] = { "*DCP", &cpu::*DCP, &cpu::ABS, 6, 3 };
	// opcode_set[0xD2] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// opcode_set[0xD3] = { "*DCP", &cpu::*DCP, &cpu::IDZPY, 8, 2 };
	// opcode_set[0xD4] = { "*NOP", &cpu::*NOP, &cpu::ZPX, 4, 2 };
	// opcode_set[0xD7] = { "*DCP", &cpu::*DCP, &cpu::ZPX, 6, 2 };
	// opcode_set[0xDA] = { "*NOP", &cpu::*NOP, &cpu::IMP, 2, 1 };
	// opcode_set[0xDB] = { "*DCP", &cpu::*DCP, &cpu::ABY, 7, 3 };
	// opcode_set[0xDC] = { "*NOP", &cpu::*NOP, &cpu::ABX, 4, 3 };
	// opcode_set[0xDF] = { "*DCP", &cpu::*DCP, &cpu::ABX, 7, 3 };
	// opcode_set[0xE2] = { "*NOP", &cpu::*NOP, &cpu::IMM, 2, 2 };
	// opcode_set[0xE3] = { "*ISC", &cpu::*ISC, &cpu::IDZPX, 8, 2 };
	// opcode_set[0xE7] = { "*ISC", &cpu::*ISC, &cpu::ZP, 5, 2 };
	// opcode_set[0xEB] = { "*SBC", &cpu::*SBC, &cpu::IMM, 2, 2 };
	// opcode_set[0xEF] = { "*ISC", &cpu::*ISC, &cpu::ABS, 6, 3 };
	// opcode_set[0xF2] = { "*JAM", &cpu::*JAM, &cpu::IMP, -1, 1 };
	// opcode_set[0xF3] = { "*ISC", &cpu::*ISC, &cpu::IDZPY, 8, 2 };
	// opcode_set[0xF4] = { "*NOP", &cpu::*NOP, &cpu::ZPX, 4, 2 };
	// opcode_set[0xF7] = { "*ISC", &cpu::*ISC, &cpu::ZPX, 6, 2 };
	// opcode_set[0xFA] = { "*NOP", &cpu::*NOP, &cpu::IMP, 2, 1 };
	// opcode_set[0xFB] = { "*ISC", &cpu::*ISC, &cpu::ABY, 7, 3 };
	// opcode_set[0xFC] = { "*NOP", &cpu::*NOP, &cpu::ABX, 4, 3 };
	// opcode_set[0xFF] = { "*ISC", &cpu::*ISC, &cpu::ABX, 7, 3 };
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
	u8 opcode_byte = memory[m_registers.PC];
	if (0xffff - m_registers.PC <= opcode_set[opcode_byte].bytes)
		return false;
	
	const opcode &o = opcode_set[opcode_byte];
	cross_page = false; branch = false;
	(this->*o.addr_handler)();
	(this->*o.instr_handler)();
	total_cycles += opcode_set[opcode_byte].cycles + cross_page + branch;
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
	u8 immediate = get_byte();
	instr_arg = immediate;
}

void cpu::ZP() {
	u8 address = get_byte();
	instr_addr = (u8)(address);
	instr_arg = get_byte((u8)address);
}

void cpu::ABS() {
	// For JMP the PC is set to address: u16 address = (byte2 << 8) | byte1; 
	u8 byte1 = get_byte();
	u8 byte2 = get_byte();
	instr_addr = (byte2 << 8) | byte1;
	instr_arg = get_byte(instr_addr);
}

void cpu::ZPX() {
	u8 contents = m_registers.X;
	u8 byte = get_byte(m_registers.PC + 1);
	u8 address = byte + contents;
	instr_addr = address;
	instr_arg = get_byte(address);
}

void cpu::ABX() {
	u8 contents = m_registers.X;
	u8 byte1 = get_byte();
	u8 byte2 = get_byte();
	bool carry = (byte1 + contents > 0xFF);
	m_registers.status.C = carry; // might not be needed.
	cross_page = carry;
	u8 address_byte1 = byte1 + contents;
	u8 address_byte2 = byte2 + carry;
	instr_addr = (address_byte2 << 8) | address_byte1;
	instr_arg = get_byte(instr_addr);
}

void cpu::ABY() {
	u8 contents = m_registers.Y;
	u8 byte1 = get_byte();
	u8 byte2 = get_byte();
	bool carry = (byte1 + contents > 0xFF);
	m_registers.status.C = carry; // might not be needed.
	cross_page = carry;
	u8 address_byte1 = byte1 + contents;
	u8 address_byte2 = byte2 + carry;
	instr_addr = (address_byte2 << 8) | address_byte1;
	instr_arg = get_byte(instr_addr);
}

void cpu::ZPY() {
	u8 contents = m_registers.Y;
	u8 byte = get_byte();
	u8 address = byte + contents; // must be u8 because 00xx
	instr_addr = address;
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
	instr_addr = (address_byte2 << 8) | address_byte1;
	instr_arg = get_byte(instr_addr);
}

void cpu::IDZPY() {
	u8 contents1 = m_registers.Y;
	u8 byte = get_byte();
	u8 contents2 = get_byte(byte);
	bool carry = (contents1 + contents2 > 0xFF);
	m_registers.status.C = carry; // might not be needed.
	cross_page = carry;
	u8 address_byte1 = contents1 + contents2;
	u8 address_byte2 = get_byte(byte + 1) + carry;
	instr_addr = (address_byte2 << 8) | address_byte1;
	instr_arg = get_byte(instr_addr);
}

void cpu::REL() {
	s8 offset = get_byte();
	u8 low_byte = (u8)m_registers.PC;
	if(low_byte + offset < 0 || low_byte + offset > 0xFF) cross_page = true;
	u16 new_address = m_registers.PC + offset;
	instr_addr = new_address;
	instr_arg = new_address;
}

void cpu::IMP() {
	// Nothing should be here.
}

void cpu::IDABS() {
	u8 byte1 = get_byte();
	u8 byte2 = get_byte();
	u16 address = (byte2 << 8) | byte1;
	u8 address_byte1 = get_byte(address);
	u8 address_byte2 = get_byte(address + 1);
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
	// stub
}

void cpu::STY() {
	// Flags: none
	u8 contents = m_registers.Y; 
	store_byte(instr_addr, contents);
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
	store_byte(instr_addr, contents);
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
	// stub
}

void cpu::ROL() {
	// stub
}

void cpu::LSR() {
	// stub
}

void cpu::ROR() {
	// stub
}

void cpu::STX() {
	// Flags: none
	u8 contents = m_registers.X; 
	store_byte(instr_addr, contents);
}

void cpu::LDX() {
	// Flags: N, Z
	u8 contents = instr_arg;
	m_registers.status.N = contents < 0 ? 1 : 0;
	m_registers.status.Z = contents == 0 ? 1 : 0;
	m_registers.X = contents;
}

void cpu::DEC() {
	// stub
}

void cpu::INC() {
	// stub
}

void cpu::BPL() {
	// stub
}

void cpu::BMI() {
	// stub
}

void cpu::BVC() {
	// stub
}

void cpu::BVS() {
	// stub
}

void cpu::BCC() {
	// stub
}

void cpu::BCS() {
	// stub
}

void cpu::BNE() {
	// stub
}

void cpu::BEQ() {
	// stub
}

void cpu::BRK() {
	// stub
}

void cpu::JSR() {
	// stub
}

void cpu::RTI() {
	// stub
}

void cpu::RTS() {
	// stub
}

void cpu::PHP() {
	// stub
}

void cpu::CLC() {
	// Flags: C
	m_registers.status.C = 0;
}

void cpu::PLP() {
	// stub
}

void cpu::SEC() {
	// Flags: C
	m_registers.status.C = 1;
}

void cpu::PHA() {
	// stub
}

void cpu::CLI() {
	// Flags: I
	m_registers.status.I = 0;
}

void cpu::PLA() {
	// stub
}

void cpu::SEI() {
	// Flags: I
	m_registers.status.I = 1;
}

void cpu::DEY() {
	// stub
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
	// stub
}

void cpu::CLD() {
	// Flags: D
	m_registers.status.D = 0;
}

void cpu::INX() {
	// stub
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
} 

void cpu::NOP() {
	// Flags: None
} 



void cpu::store_byte(u16 address, u8 byte) {
	memory[address] = byte;
}

u8 cpu::get_byte(u16 address) const {
	// TODO: Instead of having bounds checking here, let's add a
	// new field to our instruction table with minimum number of bytes
	return memory[address];
}