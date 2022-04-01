#ifndef INES_H
#define INES_H

#include <string>
#include "nes.h"

class ines {
public:
	bool load(const std::string &file);
};

#endif