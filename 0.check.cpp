#include <iostream>
#include <cmath>
void print();
void printfun();

int main(void)
{
    double x = 1;
    for(int i = 0; i < 12 ; i++)
    {
        x-=0.1;
        x = round(x*10)/10;
        std::cout << x << " " << "\n";
    }
    printfun();
    std::cout << std::stod("0.5") << "\n";
    
    return 0;
}
void printfun()
{
    print();
}

void print()
{
    std::cout << "hello"<<"\n";
}
