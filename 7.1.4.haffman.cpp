#include <iostream>
#include <bitset>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>




int main()
{

    std::bitset<8> bits(0);
    bits.set(5);
        std::cout << bits.to_string() << std::endl;


    std::ofstream wf("7.1.4.ate.txt",  std::ios::in | std::ios::ate );  //! ОТКРЫТИЕ ФАЙЛА ДЛЯ ДОЗАПИСИ В ПРОИЗВОЛЬНОЕ МЕСТО ofstream, in, ate
    if(!wf) {
        std::wcout << "Cannot open file!" << std::endl;
        return 1;
    }

    char s = 'x';
    wf.write(&s, 1);
    wf.seekp(0,std::ios::beg);
    char ss = 'f';
    wf.write(&ss, 1);

    wf.close();


    return 0;

}