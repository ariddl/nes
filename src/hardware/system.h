#ifndef SYSTEM_H
#define SYSTEM_H

#include "cpu.h"
#include "ppu.h"
#include "apu.h"

// This will house the bus, the data stream allowing the
// various components to communicate. We must consider how
// we will emulate the components and synchronize them. We
// could either opt to put each component in its own thread,
// or run everything in a single thread with proper timing.
class system {
public:
    system();

    cpu *get_cpu() { return &m_cpu; }

private:
    cpu m_cpu; // cpu
    ppu m_ppu; // gfx
    apu m_apu; // audio
};

#endif