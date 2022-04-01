#include "ines.h"
#include <fstream>
#include <memory>

/*
	iNES Header (0x10 bytes):
	bytes 0-3: signature
	byte 4: num PRG ROM pages
	byte 5: num CHR ROM pages
	byte 6: flags: mapper, mirroring, battery, trainer
	byte 7: flags: mapper, VS/Playchoice, NES 2.0
	byte 8: flags: PRG-RAM size (some roms have different page sizes, but rarely)
	byte 9: flags: tv system
	bytes 10-15: padding, typically zero bytes

	Immediately following the header is the PRG pages, and then CHR pages.
*/

bool ines::load(const std::string &file) {
	std::ifstream fi(file, std::ios::binary | std::ios::ate);
	if (!fi)
		return false;
	
	size_t size = fi.tellg();
	fi.seekg(std::ios::beg);

	std::unique_ptr<u8[]> data = std::make_unique<u8[]>(size);
	fi.read(reinterpret_cast<char *>(data.get()), size);
	return false;
}