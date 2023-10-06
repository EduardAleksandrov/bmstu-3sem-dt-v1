// Task: стек - работает
// добавлены комментарии преподавателя
#include <iostream>
#include <new>


#define STACKSIZE 5

bool pushStack(int, int*, int**);
bool popStack(int&, int*, int**);
void printStack(int*, int*, int*);
void checkFullness(int*, int*);
void checkEmptyness(int*, int*);
bool upperElement(int&, int*, int*);


int main(void)
{
    int *stackBase, *stackPointer, *stack;
    int value, chooseNumber;
    bool check;

    try
    {
        stack = new int[STACKSIZE + 1];
        // int stack[STACKSIZE];
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << e.what() << std::endl;
    }

    stackBase = stack;
    stackPointer = stack;

    for(;;)
    {
        std::cout << "Выберете пункт" << std::endl;
        std::cout << "1.добавить значение в стек" << std::endl;
        std::cout << "2.убрать значение из стека" << std::endl;
        std::cout << "3.печатать стек" << std::endl;
        std::cout << "4.проверить полноту стека" << std::endl;
        std::cout << "5.проверить пустоту стека" << std::endl;
        std::cout << "6.показать верхний элемент стека" << std::endl;
        std::cin >> chooseNumber;
        
        if(chooseNumber == 1)
        {
            std::cout << "Введите значение" << std::endl;
            std::cin >> value;
            check = pushStack(value, stackBase, &stackPointer);
            if(check == 1)
            {
                std::cout << "Стек полон" << std::endl;
                continue;
            }
        }
        if(chooseNumber == 2)
        {
            int upperElement;
            check = popStack(upperElement, stackBase, &stackPointer);
            if(check == 1)
            {
                std::cout << "Стек пуст" << std::endl;
                continue;
            } 
            std::cout << "Верхний элемент получен: " << upperElement << std::endl;
        }
        if(chooseNumber == 3)
        {
            printStack(stack, stackBase, stackPointer);
        }
        if(chooseNumber == 4)
        {
            checkFullness(stackBase, stackPointer);
        }
        if(chooseNumber == 5)
        {
            checkEmptyness(stackBase, stackPointer);
        }
        if(chooseNumber == 6)
        {
            int upperEl;
            check = upperElement(upperEl, stackBase, stackPointer);
            if(check == 1)
            {
                std::cout << "Стек пуст" << std::endl;
                continue;
            }
            std::cout << "Верхний элемент = " << upperEl << std::endl;
        }

    }

    delete [] stack;
    stack = nullptr;

    return 0;
}

bool pushStack(int value, int *stackBase, int **stackPointer)
{
    if(*stackPointer == (stackBase + STACKSIZE))
    {
        return 1;
    }
    **stackPointer = value;
    (*stackPointer)++;
    return 0;
}

bool popStack(int &upperElement, int *stackBase, int **stackPointer) //bool push, pop, проверка верхнего элемента, а значение по переменной по ссылке в stack и очередь
{
    if((*stackPointer) == stackBase)
    {
        return 1;
    }
    (*stackPointer)--;
    upperElement = **stackPointer;
    return 0;
}

void printStack(int *stack, int *stackBase, int *stackPointer)
{
    int stackNum = stackPointer - stackBase;
    if (stackNum == 0)
    {
        std::cout << "Стек пуст" << std::endl;
        return;
    } 
    for(int i = 0; i < stackNum; i++)
        std::cout << stack[i] << " ";
    std::cout << std::endl;
}

void checkFullness(int*stackBase, int*stackPointer)
{
    if(stackPointer == (stackBase + STACKSIZE))
    {
        std::cout << "Стек полон" << std::endl;
    } else {
        std::cout << "Стек не полон" << std::endl;
    }
}

void checkEmptyness(int *stackBase, int *stackPointer)
{
    if(stackPointer == stackBase)
    {
        std::cout << "Стек пуст" << std::endl;
    } else {
        std::cout << "Стек не пуст" << std::endl;
    }
}

bool upperElement(int &upperEl, int *stackBase, int *stackPointer)
{
    if(stackPointer == stackBase)
    {
        return 1;
    }
    upperEl = *(stackPointer-1);
    return 0;
}

