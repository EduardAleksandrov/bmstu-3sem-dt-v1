/*
    Подготовка
*/
#include <iostream>
#include <bitset>
#include <string>
#include <fstream>
#include <iterator>
#include <locale>

// #include <io.h>                      // для функции _setmode
// #include <fcntl.h>                   // для константы _O_U16TEXT

struct Student
{
    std::string name;
    std::string age;
};
    
int main()
{
    setlocale(LC_ALL, "");
    wchar_t lower = {L'м'};
    std::bitset<8> upper(lower);
    // std::wcout << upper.to_string() << std::endl;
    std::cout << sizeof(lower)<< " " << std::endl;
    // std::cout << lower << std::endl;

    upper.reset(5);
    // std::wcout << (wchar_t)upper.to_ulong() << std::endl;
    std::cout << upper.to_string() << std::endl;

    Student one;
    one.name = "allana";
    std::cout << sizeof(Student) << "\n";

    std::fstream wf("7.1.1.one.dat", std::ios::app | std::ios::binary);
    if(!wf) {
        std::cout << "Cannot open file!" << std::endl;
        return 1;
    }
    wf.write(reinterpret_cast<char*>(&upper), 1);
    wf.close();

    std::fstream wff("7.1.1.one.dat", std::ios::in | std::ios::binary);
    if(!wff) {
        std::cout << "Cannot open file!" << std::endl;
        return 1;
    }
    std::bitset<8> upper_read(0);
    wff.read((char *) &upper_read, 1);
    std::cout << upper_read.to_string() << std::endl;
    wff.seekp(0);
    std::bitset<16> upper_read2(0);
    wff.read((char *) &upper_read2, 2);
    std::cout << upper_read2.to_string() << std::endl;

    wff.close();
    
    std::wfstream wfff("7.1.1.text.txt", std::wios::out);
    if(!wfff) {
        std::cout << "Cannot open file!" << std::endl;
        return 1;
    }
    wchar_t five =L'м';
    wfff.imbue(std::locale(""));
    wfff.write(&five, 1);
    // wfff << five;
    wfff.close();




    return 0;
}
    
