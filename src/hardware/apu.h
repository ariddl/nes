#ifndef APU_H
#define APU_H

class system;
class apu {
public:
    apu(system *sys);

    void init();

private:
    system *m_system;
};

#endif