#ifndef PPU_H
#define PPU_H

class system;
class ppu {
public:
    ppu(system *sys);

private:
    system *m_system;
};

#endif