#include <iostream>
#include <cmath>

int main(void)
{
    double x = 1;
    for(int i = 0; i < 12 ; i++)
    {
        x-=0.1;
        x = round(x*10)/10;
        std::cout << x << " " << "\n";
    }
        
    
    return 0;
}