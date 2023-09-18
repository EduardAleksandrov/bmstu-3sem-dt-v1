#include <iostream>
#include <new>


#define STACKSIZE 5

int pushStack(int, int*, int**);
int popStack(int&, int*, int**);
void printStack(int*, int*, int*);


int main(void)
{
    int *stackBase, *stackPointer, *stack;
    int value, chooseNumber, check;

    try
    {
        stack = new int[STACKSIZE];
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
        std::cin >> chooseNumber;
        
        if(chooseNumber == 1)
        {
            std::cout << "Введите значение" << std::endl;
            std::cin >> value;
            check = pushStack(value, stackBase, &stackPointer);
            if(check == 1) continue;
        }
        if(chooseNumber == 2)
        {
            int upperElement;
            upperElement = popStack(check, stackBase, &stackPointer);
            if(check == 1) continue;
            std::cout << "Верхний элемент получен: " << upperElement << std::endl;
        }
        if(chooseNumber == 3)
        {
            printStack(stack, stackBase, stackPointer);
        }
    }
    return 0;
}

int pushStack(int value, int *stackBase, int **stackPointer)
{
    if(*stackPointer == (stackBase + STACKSIZE))
    {
        std::cout << "Стек полон" << std::endl;
        return 1;
    }
    **stackPointer = value;
    (*stackPointer)++;
    return 0;
}

int popStack(int &check, int *stackBase, int **stackPointer)
{
    if((*stackPointer) == stackBase)
    {
        std::cout << "Стек пуст" << std::endl;
        check = 1;
        return 1;
    }
    check = 0;
    (*stackPointer)--;
    return **stackPointer;
}

void printStack(int *stack, int *stackBase, int *stackPointer)
{
    int stackNum = stackPointer - stackBase;
    // std::cout << stackNum << std::endl;
    if (stackNum == 0)
    {
        std::cout << "Стек пуст" << std::endl;
        return;
    } 
    for(int i = 0; i < stackNum; i++)
        std::cout << stack[i] << " ";
    std::cout << std::endl;
}


