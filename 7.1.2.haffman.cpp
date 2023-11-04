/*
    Подготовка
    если начали использовать wcout, то его и используем иначе будет ошибка

*/
#include <iostream>
#include <bitset>
#include <string>
#include <fstream>

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
    
    std::wfstream wx("7.1.1.text.txt", std::wios::in);
    if(!wx) {
        std::cout << "Cannot open file!" << std::endl;
        return 1;
    }

    wchar_t six;
    wx.imbue(std::locale(""));
    wx.read(&six, 1);
    // wx >> six;
    std::wcout<<six<<sizeof(six)<<std::endl;
    
    wx.close();

    wchar_t st[3] {L'н', L'ß', L'G'};
    for(int i = 0; i<3; i++)
        std::wcout << st[i] << " " << std::endl;


    // std::wstring str = L"путопатв";
    std::wstring str;
    // std::wcin>>str;
    std::getline(std::wcin, str);
    std::wcout << str << "\n";

    int32_t w_int = 5;
    std::wcout << w_int << "\n";

    return 0;
}
    
