#include <iostream>
#include <new>

#define QUEUESIZE 5

int main(void)
{
    int *fpos, *lpos, *startPos, *endPosition;
    int value, chooseNumber;

    try
    {
        startPos = new int[QUEUESIZE];
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << e.what() << std::endl;
    }

    endPosition = startPos + QUEUESIZE - 1;
    fpos = startPos;
    lpos = startPos;

    for(int i = 0; i< endPosition-startPos+1; i++)
        *(startPos+i) = 1;

    for(;;)
    {
        std::cout << "Выберете пункт" << std::endl;
        std::cout << "1.Проверка полноты очереди" << std::endl;
        std::cout << "2.Проверка пустоты очереди" << std::endl;
        std::cout << "3.Просмотр первого элемента в очереди" << std::endl;
        std::cout << "4.Извлечение из очереди первого элемента" << std::endl;
        std::cout << "5.Добавление элемента в очередь" << std::endl;
        std::cout << "6.Печать очереди" << std::endl;
        std::cout << "0.Завершение работы" << std::endl;
        
        std::cin >> chooseNumber;
        if(chooseNumber == 0)
        {
            exit(0);
        }
        if(chooseNumber == 1)
        {

        }
        if(chooseNumber == 2)
        {

        }
        if(chooseNumber == 3)
        {
            
        }
        if(chooseNumber == 4)
        {
            fpos = endPosition;
            *fpos = 6;
        }
        if(chooseNumber == 5)
        {
            std::cin >> value;
            *lpos = value;
            lpos++;
            
        }
        if(chooseNumber == 6)
        {
            int x = fpos - startPos;
            std::cout << x;
            int y = lpos - startPos;
            std::cout << y;


            for(int i = 0; i<endPosition-startPos+1; i++)
                {
                    
                    
                    if(fpos>lpos && i>y &&i<x && y++<x)
                    {
                        std::cout << 0 << " ";
                    } else if(fpos>lpos){
                        std::cout << *(startPos+i) << " ";
                    }

                    if(fpos<lpos && y>i){
                        std::cout << *(startPos+i) << " ";
                    } else if(fpos<lpos){
                        std::cout << 0 << " ";
                    }
                    
                    if(fpos == lpos)
                    {
                        std::cout << 0 << " ";
                    }
                }
            std::cout << std::endl;
        }
    }


    return 0;
}