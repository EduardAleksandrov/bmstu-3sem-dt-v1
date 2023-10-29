/*
    Task: обход графа в виде дерева с указателями (поиск в ширину)
    добавлена очередь

*/
#include <iostream>
#include <string>
#include <vector>

class Queue 
{
private:
    int *fpos, *lpos, *startPos, *endPosition;
    int queue_size;
    int addLastElement; //проверка, менялся ли последний элемент, 1-менялся, 0-не менялся
    int exclude; //заменять последнее значения только один раз когда очередь не полна
public:
    Queue(int q_size): queue_size{q_size}
    {
        if(q_size <= 0)
        {
            std::cout << "Очередь не может быть меньше нуля" << std::endl;
            exit(EXIT_FAILURE);
        }

        try
        {
            startPos = new int[queue_size];
        }
        catch(const std::bad_alloc& e)
        {
            std::cerr << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }

        endPosition = startPos + queue_size - 1;
        fpos = startPos;
        lpos = startPos;

        for(int i = 0; i < endPosition-startPos+1; i++)
            *(startPos+i) = 0;
        
        addLastElement = exclude = 0;
    }
    ~Queue()
    {
        delete [] startPos;
        startPos = nullptr;
    }
    bool addElementToQueue(int value)
    {

        if((lpos != endPosition) && (startPos != fpos)) exclude = 0;
        if(lpos+1 != fpos) addLastElement = 0;

        if((lpos == endPosition) && (startPos != fpos))
        {
            lpos = startPos;
            *endPosition = value;
        } else if((lpos == endPosition) && (startPos == fpos))
        {
            if(exclude == 0) 
            {
                *lpos = value;
                exclude = 1;
            }
                
            // std::cout << "Очередь полна" << std::endl;
            return 1;
        } else if(lpos+1 == fpos)
        {
            if(addLastElement == 0)
            {
                *lpos = value;
                addLastElement = 1;
            }
            // std::cout << "Очередь полна" << std::endl;
            return 1;
        } else {
            lpos++;
            *(lpos - 1) = value;
        }
        return 0;
    }
    void printQueue()
    {
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
    bool deleteElementFromQueue(int& dropedValue)
    {
        if(lpos == fpos)
        {
            // std::cout << "Очередь пуста" << std::endl;
            return 1;
        }
        int dropedElement = *fpos;
        *fpos = 0;

        if(lpos+1 != fpos) addLastElement = 0;

        if((lpos == endPosition) && (startPos == fpos))
        {
            lpos = startPos;
        } else if((lpos+1 == fpos)) 
        {
            if(addLastElement == 1) // указатель не проедет дальше при следующем удалении, останется на месте
            {
                lpos++;
                addLastElement = 0;
            }
            
        }

        if(endPosition == fpos)
        {
            fpos = startPos;
        } else {
            fpos++;
        }
        dropedValue = dropedElement;
        return 0;
    }
    void getAllQueue(std::vector<int>& all_queue)
    {
        if(fpos<lpos)
        {
            if(fpos == startPos && lpos == endPosition)
            {
                for(int i = 0; i<lpos-fpos+1; i++)
                {
                    all_queue.push_back(*(fpos+i));
                }
            } else {
                for(int i = 0; i<lpos-fpos; i++)
                {
                    all_queue.push_back(*(fpos+i));
                }
            }
            
        }
        if(fpos>lpos)
        {
            if(lpos+1 == fpos)
            {
                for(int i = 0; i<endPosition-fpos+1; i++)
                    all_queue.push_back(*(fpos+i));
                if(addLastElement == 1)
                {
                    for(int i = 0; i<lpos - startPos+1; i++)
                        all_queue.push_back(*(startPos+i));
                } else {
                    for(int i = 0; i<lpos - startPos; i++)
                        all_queue.push_back(*(startPos+i));
                }
                
            } else {
                for(int i = 0; i<endPosition-fpos+1; i++)
                    all_queue.push_back(*(fpos+i));
                for(int i = 0; i<lpos - startPos; i++)
                    all_queue.push_back(*(startPos+i));
            }
            
        }
    }

};

int main()
{
    int value, chooseNumber, dropedValue;
    bool check;

    Queue one {5};
    for(;;)
    {
        std::cout << "Выберете пункт" << std::endl;
        std::cout << "1.Получение всех элементов очереди" << std::endl;
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
            std::vector<int> all_queue{};
            one.getAllQueue(all_queue);
            for(int i = 0; i < all_queue.size(); i++)
                std::cout<< all_queue[i] << " ";
            std::cout << std::endl;
        }
        if(chooseNumber == 2)
        {
            // emptynessQueue(fpos, lpos);
        }
        if(chooseNumber == 3)
        {
            // int firstElementInQueue;
            // check = firstElementQueue(fpos, lpos, firstElementInQueue);
            // if(check == 1)
            // {
            //     std::cout << "Очередь пуста" << std::endl;
            //     continue;
            // }
            // int x = fpos - startPos;
            // std::cout << "Первый элемент в очереди= " << firstElementInQueue << ", индекс= " << x << std::endl;


        }
        if(chooseNumber == 4)
        {

            check = one.deleteElementFromQueue(dropedValue);
            if(check == 1)
            {
                std::cout << "Очередь пуста" << std::endl;
                continue;
            }
            std::cout << dropedValue << std::endl;
        }
        if(chooseNumber == 5)
        {
            std::cout << "Введите: " << std::endl;
            std::cin >> value;
            check = one.addElementToQueue(value);
            if(check == 1)
            {
                std::cout << "Очередь полна" << std::endl;
                continue;
            } 
        }
        if(chooseNumber == 6)
        {
            one.printQueue();
        }
    }
    return 0;
}