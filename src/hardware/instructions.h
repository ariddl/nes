#pragma once
#include "cpu.h"

class instructions
{
public:
    instructions() = delete;

    static void init_table(cpu::opcode *tab);

private:
    static void BRK(cpu::opcode *tab);
    static void ORA(cpu::opcode *tab);
    static void ASL(cpu::opcode *tab);
    static void PHP(cpu::opcode *tab);
    static void BPL(cpu::opcode *tab);
    static void CLC(cpu::opcode *tab);
    static void JSR(cpu::opcode *tab);
    static void AND(cpu::opcode *tab);
    static void BIT(cpu::opcode *tab);
    static void ROL(cpu::opcode *tab);
    static void PLP(cpu::opcode *tab);
    static void BMI(cpu::opcode *tab);
    static void SEC(cpu::opcode *tab);
    static void RTI(cpu::opcode *tab);
    static void EOR(cpu::opcode *tab);
    static void LSR(cpu::opcode *tab);
    static void PHA(cpu::opcode *tab);
    static void JMP(cpu::opcode *tab);
    static void BVC(cpu::opcode *tab);
    static void CLI(cpu::opcode *tab);
    static void RTS(cpu::opcode *tab);
    static void ADC(cpu::opcode *tab);
    static void ROR(cpu::opcode *tab);
    static void PLA(cpu::opcode *tab);
    static void BVS(cpu::opcode *tab);
    static void SEI(cpu::opcode *tab);
    static void STA(cpu::opcode *tab);
    static void STY(cpu::opcode *tab);
    static void STX(cpu::opcode *tab);
    static void DEY(cpu::opcode *tab);
    static void TXA(cpu::opcode *tab);
    static void BCC(cpu::opcode *tab);
    static void TYA(cpu::opcode *tab);
    static void TXS(cpu::opcode *tab);
    static void LDY(cpu::opcode *tab);
    static void LDA(cpu::opcode *tab);
    static void LDX(cpu::opcode *tab);
    static void TAY(cpu::opcode *tab);
    static void TAX(cpu::opcode *tab);
    static void BCS(cpu::opcode *tab);
    static void CLV(cpu::opcode *tab);
    static void TSX(cpu::opcode *tab);
    static void CPY(cpu::opcode *tab);
    static void CMP(cpu::opcode *tab);
    static void DEC(cpu::opcode *tab);
    static void INY(cpu::opcode *tab);
    static void DEX(cpu::opcode *tab);
    static void BNE(cpu::opcode *tab);
    static void CLD(cpu::opcode *tab);
    static void CPX(cpu::opcode *tab);
    static void SBC(cpu::opcode *tab);
    static void INC(cpu::opcode *tab);
    static void INX(cpu::opcode *tab);
    static void NOP(cpu::opcode *tab);
    static void BEQ(cpu::opcode *tab);
    static void SED(cpu::opcode *tab);
    static void undocumented(cpu::opcode *tab);
};