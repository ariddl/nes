#include "ines.h"
#include <fstream>
#include <memory>

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