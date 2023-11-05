/*
    Task: алгоритм сжатия текста по Хаффману
*/
#include <iostream>
#include <bitset>
#include <string>
#include <fstream>

// #include <locale>

int main()
{
    setlocale(LC_ALL, "");
    
    wchar_t ch;
    std::wfstream fr("7.2.1.string.txt", std::wios::in);
    if(!fr) {
        std::wcout << "Cannot open file!" << std::endl;
        return 1;
    }
    fr.imbue(std::locale(""));
    while(fr)
    {
        ch = fr.get();
        std::wcout << ch << " ";



    }
    std::wcout << std::endl;


    

    fr.close();

    return 0;
}