#include <vector>
#include <fstream> 
#include <iostream>

typedef union
{
  struct
  {
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4 : 1;
    unsigned char bit5 : 1;
    unsigned char bit6 : 1;
    unsigned char bit7 : 1;
    unsigned char bit8 : 1;
  }u;
  unsigned char BYTE;
} BYTE;




int main(int argc, char* argv[])
{

const char* filename = *(argv + 1);

  std::ifstream is (filename, std::ifstream::binary);
  if (is) {
    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);

    char * buffer = new char [length];

    std::cout << "Reading " << length << " characters... ";
    // read data as a block:
    is.read (buffer,length);

    if (is)
      std::cout << "all characters read successfully.";
    else
      std::cout << "error: only " << is.gcount() << " could be read";
    is.close();

    // ...buffer contains the entire file...
    std::cout << length  << std::endl;
    std::cout << std::hex << (int)buffer[0] << std::endl;
    delete[] buffer;
  }




    return 0;
}

