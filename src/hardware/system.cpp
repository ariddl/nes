#include "system.h"

system::system()
    : m_cpu(this)
    , m_ppu(this)
    , m_apu(this) {
}