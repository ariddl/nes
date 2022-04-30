#ifndef SYSTEM_H
#define SYSTEM_H

#include "cpu.h"
#include "ppu.h"
#include "apu.h"
#include "mem.h"

// This will house the bus, the data stream allowing the
// various components to communicate. We must consider how
// we will emulate the components and synchronize them. We
// could either opt to put each component in its own thread,
// or run everything in a single thread with proper timing.
class system {
public:
    system();

    void init(const u8 *mem, size_t sz);

    cpu *get_cpu() { return &m_cpu; }
    mem *get_mem() { return &m_mem; }

private:
    mem m_mem; // memory
    cpu m_cpu; // cpu
    ppu m_ppu; // gfx
    apu m_apu; // audio
};

// TODO: rename this class, it's conflicting with a standard function!
using nes_system = system;

#endif