#include "system.h"

system::system()
    : m_cpu(this)
    , m_ppu(this)
    , m_apu(this) {
}

void system::init(const u8 *mem, size_t sz) {
    // This will be called each time a new game is started.
    m_mem.init(mem, sz);
    m_cpu.init();
    m_ppu.init();
    m_apu.init();
}