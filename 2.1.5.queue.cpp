
// Task: циклическая очередь с функциями - полностью работает
// добавлены комментарии преподавателя
// Исправленная версия
// addElementToQueue добавлен return 0 - работает

#include <iostream>
#include <new>

// fpos----lpos--

#define QUEUESIZE 6

void fullnessQueue(int*, int*, int*, int*);
void emptynessQueue(int*, int*);
bool firstElementQueue(int*, int*, int&);
void printQueue(int*, int*, int*, int*);
bool addElementToQueue(int*, int**, int*, int*, int);
bool deleteElementFromQueue(int**, int**, int*, int*, int&);


int addLastElement = 0; //проверка, менялся ли последний элемент, 1-менялся, 0-не менялся
int exclude = 0; //заменять последнее значения только один раз когда очередь не полна


int main(void)
{
    int *fpos, *lpos, *startPos, *endPosition;
    int value, chooseNumber, dropedValue;
    bool check;

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
            fullnessQueue(fpos, lpos, startPos, endPosition);
        }
        if(chooseNumber == 2)
        {
            emptynessQueue(fpos, lpos);
        }
        if(chooseNumber == 3)
        {
            int firstElementInQueue;
            check = firstElementQueue(fpos, lpos, firstElementInQueue);
            if(check == 1)
            {
                std::cout << "Очередь пуста" << std::endl;
                continue;
            }
            int x = fpos - startPos;
            std::cout << "Первый элемент в очереди= " << firstElementInQueue << ", индекс= " << x << std::endl;


        }
        if(chooseNumber == 4)
        {

            check = deleteElementFromQueue(&fpos, &lpos, startPos, endPosition, dropedValue);
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
            check = addElementToQueue(fpos, &lpos, startPos, endPosition, value);
            if(check == 1)
            {
                std::cout << "Очередь полна" << std::endl;
                continue;
            } 
        }
        if(chooseNumber == 6)
        {
            printQueue(fpos, lpos, startPos, endPosition);
        }
    }

    delete [] startPos;
    startPos = nullptr;

    return 0;
}

void fullnessQueue(int *fpos, int *lpos, int *startPos, int *endPosition)
{
    if((lpos == endPosition) && (startPos == fpos) && exclude == 1)
    {
        std::cout << "Очередь полна" << std::endl;
    } else if(lpos+1 == fpos && addLastElement == 1)
    {
        std::cout << "Очередь полна" << std::endl;
    } else {
        std::cout << "Очередь не полна" << std::endl;
    }
}

void emptynessQueue(int *fpos, int *lpos)
{
    if(lpos == fpos)
    {
        std::cout << "Очередь пуста" << std::endl;
    } else {
        std::cout << "Очередь не пуста" << std::endl;
    }
}

bool firstElementQueue(int *fpos, int *lpos, int &firstElementInQueue)
{
    if(*lpos == *fpos)
    {
        return 1;
    }
    firstElementInQueue = *fpos;
    return 0;
}

void printQueue(int *fpos, int *lpos, int *startPos, int *endPosition)
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

bool addElementToQueue(int *fpos, int **lpos, int *startPos, int *endPosition, int value)
{

    // if((*lpos != endPosition) && (startPos != fpos)) exclude = 0;
    // if(*lpos+1 != fpos) addLastElement = 0;

    if((*lpos == endPosition) && (startPos != fpos))
    {
        *lpos = startPos;
        if(addLastElement == 0)
        {
            *endPosition = value;
        }
        addLastElement = 0;
    } else if((*lpos == endPosition) && (startPos == fpos))
    {
        if(addLastElement == 0) 
        {
            **lpos = value;
            addLastElement = 1;
            return 0;
        }
            
        // std::cout << "Очередь полна" << std::endl;
        return 1;
    } else if(*lpos+1 == fpos)
    {
        if(addLastElement == 0)
        {
            **lpos = value;
            addLastElement = 1;
            return 0;
        }
        // std::cout << "Очередь полна" << std::endl;
        return 1;
    } else {
        (*lpos)++;
        *(*lpos - 1) = value;
    }
    return 0;
}

bool deleteElementFromQueue(int **fpos, int **lpos, int *startPos, int *endPosition, int &dropedValue)
{
    if(*lpos == *fpos)
    {
        // std::cout << "Очередь пуста" << std::endl;
        return 1;
    }
    int dropedElement = **fpos;
    **fpos = 0;

    // if(*lpos+1 != *fpos) addLastElement = 0;

    if((*lpos == endPosition) && (startPos == *fpos) && (addLastElement == 1))
    {
        *lpos = startPos;
        addLastElement = 0;
    } else if((*lpos+1 == *fpos)) 
    {
        if(addLastElement == 1) // указатель не проедет дальше при следующем удалении, останется на месте
        {
            (*lpos)++;
            addLastElement = 0;
        }
        
    }

    if(endPosition == *fpos)
    {
        *fpos = startPos;
    } else {
        (*fpos)++;
    }
    dropedValue = dropedElement;
    return 0;
}



