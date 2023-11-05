#include <iostream>
#include <bitset>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>


struct Binary_node
{
    wchar_t binary_node_label;
    std::vector <bool> binary_number;
};

int main()
{




// запись данных в бинарный файл

    std::bitset<8> bits(0);
    // bits.set(7);
    // bits[3] = 1;
    // bits.reset(5);

    std::cout << bits.to_string() << std::endl;


    std::fstream wf("7.2.4.bits.dat", std::ios::out | std::ios::binary);
    if(!wf) {
        std::wcout << "Cannot open file!" << std::endl;
        return 1;
    }
    wf.write(reinterpret_cast<char*>(&bits), 1);
    wf.close();

    std::fstream wff("7.2.4.bits.dat", std::ios::in | std::ios::binary);
    if(!wff) {
        std::wcout << "Cannot open file!" << std::endl;
        return 1;
    }
    std::bitset<8> upper_read(0);
    wff.read((char *) &upper_read, 1);
    // std::cout << upper_read.to_string() << std::endl;
    wff.close();

    std::cout <<upper_read.to_string() << std::endl;
    std::cout <<upper_read[2] << std::endl;
    
    // печать списка битов
    Binary_node tmp;
    for(int i = 7; i >=0 ; i--)
        tmp.binary_number.push_back(upper_read[i]);

    for(int j=0;j < tmp.binary_number.size(); j++)
    {
        std::cout << tmp.binary_number[j];
    }
    std::cout << std::endl;

    return 0;

}