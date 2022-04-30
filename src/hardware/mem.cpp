#include "mem.h"

mem::mem()
    : m_memory(nullptr)
    , m_map{} {}

mem::~mem() {
    delete[] m_memory;
}

void mem::init(const u8 *mem, size_t sz) {
    delete[] m_memory;
    m_memory = new u8[0xffff];
	memcpy(m_memory + 0x2000, mem, sz);

    // TODO: m_map[...]
    // As it turns out, the byte ranges do not seem to perfectly align on
    // 256 byte boundaries, so we need some other method of mapping (TODO).
}

void mem::write(u8 lo, u8 hi, u8 byte) {
    //m_map[lo][hi] = byte;
    m_memory[static_cast<u16>(lo) | static_cast<u16>(hi) << 8] = byte;
}

void mem::write(u16 address, u8 byte) {
    m_memory[address] = byte;
	//m_map[address & 0xff][address >> 8] = byte;
}

u8 mem::read(u8 lo, u8 hi) const {
    return m_memory[static_cast<u16>(lo) | static_cast<u16>(hi) << 8];
    //return m_map[lo][hi];
}

u8 mem::read(u16 address) const {
	return m_memory[address];
    //return m_map[address & 0xff][address >> 8];
}