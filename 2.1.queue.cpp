// циклическая очередь - работает, но с нулем
#include <iostream>
#include <new>

// fpos----lpos--

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
        *(startPos+i) = 0;

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
            if(lpos == endPosition && (startPos == fpos))
            {
                std::cout << "Очередь полна" << std::endl;
            } else if(lpos+1 == fpos)
            {
                std::cout << "Очередь полна" << std::endl;
            } else {
                std::cout << "Очередь не полна" << std::endl;
            }
        }
        if(chooseNumber == 2)
        {
            if(lpos == fpos)
            {
                std::cout << "Очередь пуста" << std::endl;
            } else {
                std::cout << "Очередь не пуста" << std::endl;
            }
        }
        if(chooseNumber == 3)
        {
            int x = fpos - startPos;
            std::cout << "Первый элемент в очереди: " << *fpos << ", индекс=" << x << std::endl;
        }
        if(chooseNumber == 4)
        {
            if(lpos == fpos)
            {
                std::cout << "Очередь пуста" << std::endl;
                continue;
            }
            
            *fpos = 0;

            if(lpos == endPosition && (startPos == fpos))
            {
                lpos = startPos;
            } else if((lpos+1 == fpos) && (*lpos != 0))
            {
                lpos++;
            }

            if(endPosition == fpos)
            {
                fpos = startPos;
            } else {
                fpos++;
            }
        }
        if(chooseNumber == 5)
        {
            
            // if(lpos+1 == fpos)
            // {
            //     std::cout << "Очередь полна" << std::endl;
            //     continue;
            // }
            // if(lpos == endPosition)
            // {
            //     if(startPos == fpos)
            //     {
            //         std::cout << "Очередь полна" << std::endl;
            //         continue;
            //     }
            // }



            std::cin >> value;
            // *lpos = value;
            if(*lpos == 0) *lpos = value;
            if(lpos == endPosition && (startPos != fpos))
            {
                lpos = startPos;
            } else if(lpos == endPosition && (startPos == fpos))
            {
                std::cout << "Очередь полна" << std::endl;
                continue;
            } else if(lpos+1 == fpos)
            {
                std::cout << "Очередь полна" << std::endl;
                continue;
            } else {
                lpos++;
            }
        }
        if(chooseNumber == 6)
        {
            // int x = fpos - startPos;
            // std::cout << x;
            // int y = lpos - startPos;
            // std::cout << y << endPosition-startPos+1;

            // if(y == endPosition-startPos) y++;
            // for(int i = 0; i<endPosition-startPos+1; i++)
            //     {
                    
                    
            //         if(fpos>lpos && i>y &&i<x && y++<x)
            //         {
            //             std::cout << 0 << " ";
            //         } else if(fpos>lpos){
            //             std::cout << *(startPos+i) << " ";
            //         }

            //         if(fpos<lpos && y>i){
            //             std::cout << *(startPos+i) << " ";
            //         // } else if(fpos<lpos)
            //         // {
            //         //     std::cout << *(startPos+i) << " ";
            //         } else if(fpos<lpos){
            //             std::cout << 0 << " ";
            //         }
                    
            //         if(fpos == lpos)
            //         {
            //             std::cout << 0 << " ";
            //         }
            //     }
            // std::cout << std::endl;

            for(int i = 0; i<endPosition-startPos+1; i++)
            {
                std::cout << *(startPos+i) << " ";
            }
            std::cout << std::endl;
            int x = fpos - startPos;
            int y = lpos - startPos;
            std::cout << "fpos=" << *fpos << ", индекс=" << x << std::endl;
            std::cout << "lpos=" << *lpos << ", индекс=" << y << std::endl;
            std::cout << std::endl;
        }
    }


    return 0;
}