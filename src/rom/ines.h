#ifndef INES_H
#define INES_H

#include <string>
#include <memory>
#include "nes.h"

class ines {
public:
	static std::unique_ptr<u8[]>  load(const std::string &file, std::size_t &size);
};

#endif