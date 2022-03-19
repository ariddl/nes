#ifndef APU_H
#define APU_H

class system;
class apu {
public:
    apu(system *sys);

private:
    system *m_system;
};

#endif