#include <iostream>

int main()
{
    
    uint8_t a = 0xFF;
    uint8_t b = 0x0;
    bool carry = (a + b > 0xFF);
    uint8_t c = a + b;
    // std::cout << (int)c << carry << std::endl; 

    uint16_t d = 0x1203;
    uint8_t e = 0xF0;

    uint8_t d1 = d;
    uint8_t d2 = d >> 8;


    uint16_t r = d + e;
    std::cout << r << std::endl;


    carry = (e + d1 > 0xFF);
    uint8_t msb = d2 + carry;
    uint8_t lsb = d1 + e;
    r =  (msb << 8) | lsb;
    std::cout << "cross page: " <<  carry << std::endl;
    std::cout << r << std::endl;

    uint16_t pc = 0x018A;
    int8_t offset = 0x80;
    uint16_t R = pc + offset;
    std::cout << pc << " " << (pc) + offset << " " << R <<  std::endl;







    return 0;
}