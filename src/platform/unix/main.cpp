#include "system.h"
#include "ines.h"
#include <iostream>
#include <iomanip>
#include <string>

void dump_cpu(cpu *cpu, mem *m, u32 cols, u32 start, u32 end) {
    const auto r = cpu->get_registers();
    std::stringstream ss;
    ss << std::hex << "Registers: A=" << (s32)r.A << " X=" << (s32)r.X << " Y=" << (s32)r.Y
        << " PC=" << (s32)r.PC << " S=" << (s32)r.S << ' ';
    ss << "Status(Flags=" << (s32)r.status.flags << "): N=" << (s32)r.status.N << " V=" << (s32)r.status.V
        << " D=" << (s32)r.status.D << " I=" << (s32)r.status.I << " Z=" << (s32)r.status.Z 
        << " C=" << (s32)r.status.C;
    std::string reg;

    const u8 *memory = m->get_mem();
    std::cout << std::hex;
    for (u32 i = start; i < end; ++i) {
        if (i % cols == 0) {
            if (i > 0)
                std::cout << (std::getline(ss, reg, ' ') ? (std::string(4, ' ') + reg) : "") << std::endl;
            std::cout << std::setfill('0') << std::setw(4) << i << "  ";
        }
        std::cout << std::setfill('0') << std::setw(2) << s32(memory[i]) << ' ';
    }
    std::cout << std::endl << std::dec;
}

int main(int argc, const char **argv) {
    if (argc < 2)
        return 1;

    // Load sample rom.
    size_t sz;
    auto rom = ines::load(argv[1], sz);

    // Setup test system.
    nes_system s;
    s.init(rom.get(), sz);
    cpu *c = s.get_cpu();
    mem *m = s.get_mem();

    // For testing:
    // Execute instructions until we get to an empty instruction
    while (c->execute_next());

    // Dump CPU stats now that instructions have executed:
    dump_cpu(c, m, 16, 0x0, 0x100);

    return 0;
}