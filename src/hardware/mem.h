#ifndef MEM_H
#define MEM_H

#include "nes.h"
#include <cstring>

class mem
{
public:
	mem();
    ~mem();

    void init(const u8 *mem, size_t sz);
    
    void write(u8 lo, u8 hi, u8 byte);
    void write(u16 address, u8 byte);
    u8 read(u16 address) const;
    u8 read(u8 lo, u8 hi) const;
	
	const u8 *get_mem() const { return m_memory; }

private:
	/*
		0000-07FF is RAM, 0800-1FFF are mirrors of RAM (you AND the address with
		07FF to get the effective address)

		2000-2007 is how the CPU writes to the PPU, 2008-3FFF are mirrors of
		that address range.

		4000-401F is for IO ports and sound

		4020-4FFF is rarely used, but can be used by some cartridges

		5000-5FFF is rarely used, but can be used by some cartridges, often as
		bank switching registers, not actual memory, but some cartridges put RAM
		there

		6000-7FFF is often cartridge WRAM. Since emulators usually emulate this
		whether it actually exists in the cartridge or not, there's a little bit
		of controversy about NES headers not adequately representing a
		cartridge.

		8000-FFFF is the main area the cartridge ROM is mapped to in memory.
		Sometimes it can be bank switched, usually in 32k, 16k, or 8k sized
		banks.
	*/
	u8 *m_memory;
	u8 *m_map[256];
};

#endif