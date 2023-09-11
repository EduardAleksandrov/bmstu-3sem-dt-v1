#include <iostream>
#include <math.h>

bool failCin();
float functionY(float);

int main(void)
{
    float xmin;
    float xmax;
    float h;
    bool failEnter = 0;
    for(;;)
    {
        for(;;)
        {
            std::cout << "Введите x min: ";
            std::cin >> xmin;
            failEnter = failCin();
            if(failEnter == 1)
            {
                failEnter = 0;
                continue;
            }
            break;
        }
            
        for(;;)
        {
            std::cout << "Введите x max: ";
            std::cin >> xmax;
            failEnter = failCin();
            if(failEnter == 1)
            {
                failEnter = 0;
                continue;
            }
            break;
        }
        for(;;) 
        {
            std::cout << "Введите шаг h: ";
            std::cin >> h;
            failEnter = failCin();
            if(failEnter == 1)
            {
                failEnter = 0;
                continue;
            }
            break;
        }
        std::cout << "xmin: " << xmin << ", xmax: " << xmax << ", step h:" << h << std::endl;

        short int choise;
        for(;;)
        {
            std::cout << "Введите 1. Таблица значений функции" << std::endl;
            std::cout << "Введите 2. Значение интеграла 3 способами" << std::endl;
            std::cout << "Введите 3. Значение интеграла с точность" << std::endl;
            std::cout << "Введите 0. Для ввода nmin, nmax, h" << std::endl;
            std::cin >> choise;
            if(std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка cin от всего лишнего
                std::cout << "Неверный ввод, повторите."<< std::endl;
                continue;
            }
            if(choise == 0) break;

            if(choise == 1)
            {
                float x, f; //определили функцию
                f = 0;
                float xnew = xmin;
                while(xnew<xmax)
                {
                    x = xnew;
                    try
                    {
                        f = functionY(x);
                        std::cout << f << ", для x = " << x << std::endl;
                    }
                    catch(...)
                    {
                        std::cout << "---, деление на ноль" << std::endl;
                    }
                    xnew+= h;
                }
                if(xnew>=xmax)
                {
                    x = xmax;
                    try
                    {
                        f = functionY(x);
                        std::cout << f << ", для x = " << x << std::endl;
                    }
                    catch(...)
                    {
                        std::cout << "---, деление на ноль" << std::endl;
                    }
                }
                
            }

            if(choise == 2)
            {
                // float eps;
                // for(;;)
                // {
                //     std::cout << "Введите точность eps" << std::endl;
                //     std::cin >> eps;
                //     if(std::cin.fail())
                //     {
                //         std::cin.clear();
                //         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка cin от всего лишнего
                //         std::cout << "Неверный ввод, повторите."<< std::endl;
                //         continue;
                //     }
                //     break;
                // }
                    

                float x, f1, f2, f3;
                f1 = 0;
                f2 = 0;
                f3 = 0;
                float xnew = xmin;
                while(xnew<xmax)
                {
                    x = xnew;
                    f1+=((x + h) - x)*functionY(x);
                    f2+=((x + h) - x)*functionY(x + h);
                    f3+=(functionY(x) + functionY(x + h))/2*((x + h) - x);
                    xnew+= h;
                }
                if(xnew>=xmax)
                {
                    f1+=(xmax - x)*functionY(x);
                    f2+=(xmax - x)*functionY(xmax);
                    f3+=(functionY(x) + functionY(xmax))/2*(xmax - x);
                    std::cout << "(Метод левых прямоугольников): Площадь равна: "<< f1 << std::endl;
                    std::cout << "(Метод правых прямоугольников): Площадь равна: "<< f2 << std::endl;
                    std::cout << "(Метод трапеций): Площадь равна: "<< f3 << std::endl;
                }
            }

            if(choise == 3)
            {
                float x, f, fprev;
                f = 0;
                fprev = 0;
                bool counter = 1;
                float eps = 0.01;            //min 0 max 3 step 0.3 0.2 0.1 eps 0.1 0.01
                int nmax = 0;

                while(true)
                {
                    nmax += 1;
                    if(counter == 0 || nmax > 50) break;
                    
                    f = 0;
                    float xnew = xmin;
                    if(h > 0)
                    {
                        while(xnew<xmax)
                        {
                            x = xnew;
                            f += ((x + h) - x)*functionY(x);
                            xnew += h;
                        }
                        if(xnew>=xmax)
                        {
                            f += (xmax - x)*functionY(x);
                        }
                    } else {
                        break;
                    }
                    
                    if(fabs(f - fprev) >= eps && h > 0) 
                    {
                        counter = 1;
                        h-= 0.01;
                    } else {
                        counter = 0;
                    }

                    float dif = fabs(f - fprev);
                    std::cout << "Шаг: "<< nmax << " f=" << f << " fprev=" << fprev << " fdif=" << dif << std::endl;
                    fprev = f;
                }
                std::cout << "Площадь равна: "<< f << std::endl;
            }
        }
    }
    return 0;
}

bool failCin()
{
    if(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка cin от всего лишнего
        std::cout << "Неверный ввод, повторите."<< std::endl;
        return 1;
    }
    return 0;
}

float functionY(float x)
{
    float y;
    y = 0;
    // if(x)
        return y = x*x;
    throw "division by zero";
}