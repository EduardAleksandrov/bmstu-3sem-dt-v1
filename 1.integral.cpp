#include <iostream>
#include <math.h>

bool failCin();
float functionY(float);

int main(void)
{
    double xmin;
    double xmax;
    double h, hConst;
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
            if (xmax<=xmin)
            {
                std::cout << "Неверное значение, повторите" << std::endl; 
                continue;
            }
            break;
        }
        for(;;) 
        {
            std::cout << "Введите шаг h: ";
            std::cin >> hConst;
            if (hConst <= 0 || hConst > xmax-xmin)
            {
                std::cout << "Неверное значение, повторите" << std::endl; 
                continue;
            }
            failEnter = failCin();
            if(failEnter == 1)
            {
                failEnter = 0;
                continue;
            }
            break;
        }
        std::cout << "xmin: " << xmin << ", xmax: " << xmax << ", step h:" << hConst << std::endl;

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
                double xnew = xmin;
                h = hConst;
                while(xnew<xmax)
                {
                    x = xnew;
                    try
                    {
                        // if(x < 0.00001 && x > -0.00001) x = 0;
                        f = functionY(x);
                        std::cout << f << ", для x = " << x << std::endl;
                    }
                    catch(...)
                    {
                        std::cout << "---, деление на ноль для x = " << x << std::endl;
                    }
                    xnew+= h;
                }
                if(xnew>=xmax)
                {
                    x = xmax;
                    try
                    {
                        // if(x < 0.00001 && x > -0.00001) x = 0;
                        f = functionY(x);
                        std::cout << f << ", для x = " << x << std::endl;
                    }
                    catch(...)
                    {
                        std::cout << "---, деление на ноль для x = "<< x << std::endl;
                    }
                }
                
            }

            if(choise == 2)
            {
                float x, f1, f2, f3;
                f1 = 0;
                f2 = 0;
                f3 = 0;
                double xnew = xmin;
                h = hConst;
                while(xnew<xmax)
                {
                    x = xnew;
                    if (xmax - xmin == h || xnew + h >= xmax)
                    {
                        xnew+= h;
                        break;
                    }
                    
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
                float eps;            //min 0 max 3 step 0.3 0.2 0.1 eps 0.1 0.01
                for(;;)
                {
                    std::cout << "Введите eps(точность) от 0 до 1" << std::endl;
                    std::cin >> eps;
                    if(std::cin.fail())
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка cin от всего лишнего
                        std::cout << "Неверный ввод, повторите."<< std::endl;
                        continue;
                    }
                    if(eps>0 && eps<=1)
                    {
                        break;
                    } else {
                        continue;
                    }
                }
                int method;
                for(;;)
                {
                    std::cout << "Выберете метод расчета" << std::endl;
                    std::cout << "1.(Метод левых прямоугольников): "<< std::endl;
                    std::cout << "2.(Метод правых прямоугольников): "<<  std::endl;
                    std::cout << "3.(Метод трапеций): "<<  std::endl;
                    std::cin >> method;
                    if(std::cin.fail())
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка cin от всего лишнего
                        std::cout << "Неверный ввод, повторите."<< std::endl;
                        continue;
                    }
                    if(method>=1 && method<=3)
                    {
                        break;
                    } else {
                        continue;
                    }
                }
                
                int nmax = 0;
                h = hConst; 

                while(true)
                {
                    nmax += 1;
                    if(counter == 0 || nmax > 500 || h<=0) break;
                    f = 0;
                    double xnew = xmin;
                    
                    // if(h > 0)
                    // {
                        while(xnew<xmax)
                        {
                            x = xnew;
                            if (xmax - xmin == h || xnew + h >= xmax)
                            {
                                xnew+= h;
                                break;
                            }
                            if(method == 1) f += ((x + h) - x)*functionY(x);
                            if(method == 2) f += ((x + h) - x)*functionY(x + h);
                            if(method == 3) f += (functionY(x) + functionY(x + h))/2*((x + h) - x);

                            xnew += h;
                        }
                        if(xnew>=xmax)
                        {
                            if(method == 1) f += (xmax - x)*functionY(x);
                            if(method == 2) f += (xmax - x)*functionY(xmax);
                            if(method == 3) f += (functionY(x) + functionY(xmax))/2*(xmax - x);
                        }
                    // } else {
                    //     break;
                    // }

                    float dif = fabs(f - fprev);
                    if(dif >= eps) 
                    {
                        counter = 1;
                        h-= 0.01;
                    } else {
                        counter = 0;
                    }

                    if(h <= 0) std::cout << "Величина шага обнулилась" << std::endl;
                    std::cout << "Шаг: "<< nmax << " f=" << f << " fprev=" << fprev << " fdif=" << dif << std::endl;
                    fprev = f;
                }
                std::cout << "Площадь равна: "<< f << std::endl << std::endl;
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