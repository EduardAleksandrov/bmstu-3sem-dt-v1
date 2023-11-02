#include <iostream>
#include <bitset>
    
    
    
int main()
{
    setlocale(LC_ALL, "");
    wchar_t lower = L'м';
    std::bitset<8> upper(lower);
    std::cout << upper.to_string() << std::endl;

    upper.reset(5);
    std::wcout << (wchar_t)upper.to_ulong() << std::endl;
    std::cout << upper.to_string() << std::endl;

    return 0;
}
    
