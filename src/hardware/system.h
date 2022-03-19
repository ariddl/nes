#ifndef SYSTEM_H
#define SYSTEM_H

#include "cpu.h"

// This will house the bus, the data stream allowing the
// various components to communicate. We must consider how
// we will emulate the components and synchronize them. We
// could either opt to put each component in its own thread,
// or run everything in a single thread with proper timing.
class system {
public:
    system();

private:
    cpu m_cpu;
};

#endif