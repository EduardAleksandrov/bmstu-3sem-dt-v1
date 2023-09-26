// Токенизация вынесена в функцию
// Добавлен ввод данных
// Добавлен стек - работает

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <array>

// проверка ввода
bool failCin();
// 1) перевод введенных данных во входную строку(массив строк-токенов)
bool getTokenStringArray(std::string, std::vector<std::string>&, bool&);
// Стек
template<typename T, typename K>
bool pushStack(T , T*, T**, K);

template<typename T>
bool popStack(T&, T*, T**); 

template<typename T>
void printStack(T*, T*, T*);

template<typename T>
bool upperElement(T&, T*, T*);
// Стек конец

int main(void)
{
// Вводные данные
    std::string inputString {};
    // если в выражении есть x
    double xmin {0};
    double xmax {0};
    double h, hConst {0};
    
    std::vector<std::string> inputStringArray; //массив токенов

    // --- программные данные
    std::string programExpression {"(2^2)*sin(4)"}; //программное выражение
    // {"2^(cot(5)*5/5*x+sin(x)-(-66+22-cos(4))+50-x)"}
    double xxmin {0};
    double xxmax {10};
    double hhConst {1};
    // --- конец программных данных

    bool varX = 0; // флаг, есть ли переменная x в выражении, 1-есть
    bool failEnter = 0; // флаг, ошибка ввода
    int choseInputExpression;
    for(;;)
    {
        std::cout << "1.Ввести выражение" << std::endl;
        std::cout << "2.Использовать программное" << std::endl;
        std::cin >> choseInputExpression;
        failEnter = failCin();
        if(failEnter == 1)
        {
            failEnter = 0;
            continue;
        }
        // break;

        if(choseInputExpression == 1)
        {
            std::cout << "Введите:" << std::endl;
            std::cin >> inputString;
            if(!getTokenStringArray(inputString, inputStringArray, varX))
            {
                if(varX)
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
                        if (hConst <= 0 || hConst > xmax-xmin || hConst < 0.000999)
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
                }
                break;
            } else {
                std::cout << "Проверьте выражение на существование знака" << std::endl;
                continue;
            }
        }
        if(choseInputExpression == 2)
        {
            inputString = programExpression;
            if(!getTokenStringArray(inputString, inputStringArray, varX))
            {
                if(varX)
                {
                    xmin = xxmin;
                    xmax = xxmax;
                    hConst = hhConst;
                }
                break;
            } else {
                std::cout << "Проверьте выражение на существование знака" << std::endl;
                continue;
            }
        }
    }

// --- печать токенизированного массива
    std::cout << "Токенизированная строка: ";
    for(std::string n : inputStringArray)
        std::cout << n << "";
    std::cout << "\n";

    std::cout << "xmin:"<< xmin << " xmax:" << xmax << " h:" << hConst << "\n";
// --- конец печати


// --- Организация стека
    int *stackInteger;
    std::string *stackString;
    
    int stacksizeInteger {100};
    int stacksizeString = inputStringArray.size();

    try
    {
        stackInteger = new int[stacksizeInteger + 1];
        stackString = new std::string[stacksizeString + 1];
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << e.what() << std::endl;
    }

    int *stackBaseInteger = stackInteger;
    int *stackPointerInteger = stackInteger;

    std::string *stackBaseString = stackString;
    std::string *stackPointerString = stackString;

// --- Организация стека конец

// --- варианты использования стека
    // int valueInt = 5;
    // if(pushStack(valueInt, stackBaseInteger, &stackPointerInteger, stacksizeInteger))
    // {
    //     std::cout << "Стек полон" << std::endl;
    // }

    // pushStack(valueInt, stackBaseInteger, &stackPointerInteger, stacksizeInteger);

    // std::string valueStr {"hello"};
    // pushStack(valueStr, stackBaseString, &stackPointerString, stacksizeString);
    // pushStack(valueStr, stackBaseString, &stackPointerString, stacksizeString);

    // int upperElementInt;
    // std::string upperElementString;
    // if(popStack(upperElementInt, stackBaseInteger, &stackPointerInteger))
    // {
    //     std::cout << "Стек пуст" << std::endl;
    // }
    // popStack(upperElementString, stackBaseString, &stackPointerString);

    // printStack(stackInteger, stackBaseInteger, stackPointerInteger);
    // printStack(stackString, stackBaseString, stackPointerString);
// --- варианты использования стека конец








    return 0;
}



// --- Стек
template<typename T, typename K>
bool pushStack(T value, T *stackBase, T **stackPointer, K stacksize)
{
    if(*stackPointer == (stackBase + stacksize))
    {
        return 1;
    }
    **stackPointer = value;
    (*stackPointer)++;
    return 0;
}

template<typename T>
bool popStack(T &upperElement, T *stackBase, T **stackPointer) 
{
    if((*stackPointer) == stackBase)
    {
        return 1;
    }
    (*stackPointer)--;
    upperElement = **stackPointer;
    return 0;
}

template<typename T>
void printStack(T *stack, T *stackBase, T *stackPointer)
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

template<typename T>
bool upperElement(T &upperEl, T *stackBase, T *stackPointer)
{
    if(stackPointer == stackBase)
    {
        return 1;
    }
    upperEl = *(stackPointer-1);
    return 0;
}
// --- Стек конец

// проверка ввода
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

// 1) перевод введенных данных во входную строку(массив строк-токенов)
bool getTokenStringArray(std::string inputString, std::vector<std::string> &inputStringArray, bool &varX)
{
    std::string numbers {"0123456789"};
    std::string binaryOperators {"+-*/^"};
    std::array<std::string, 2>  brackets {"(",")"};
    std::array<std::string, 4> unaryOperators {"sin", "cos", "tan", "cot"};
    std::array<std::string, 1> variableX {"x"};
    // varX = 0;

    int openBrackets {0}, closeBrackets {0}; //подсчет кавычек

    std::string promezString {};
    bool signExist, checkUnar; // checkUnar - проверка sin, cos...; signExist - проверка символа на существование
    for(int i = 0; i < inputString.length(); i++)
    {
        signExist = 0;

        if(inputString.substr(i, 1) == " ") continue;
        // накапливаем строки
        for(int j = 0; j < numbers.length(); j++)
        {
            if(inputString.substr(i, 1) == numbers.substr(j, 1))
            {
                promezString += inputString.substr(i, 1);
                signExist = 1;
                checkUnar = 0;
                continue;
            }
        }

        // вводим бинарный оператор и накопленную строку
        for(int j = 0; j < binaryOperators.length(); j++)
        {
            if(inputString.substr(i, 1) == binaryOperators.substr(j, 1))
            {
                if(promezString != "")
                {
                    inputStringArray.push_back(promezString);
                    promezString = {};  
                }
                inputStringArray.push_back(binaryOperators.substr(j, 1));
                signExist = 1;
                checkUnar = 0;
                continue;
            }
        }

        // вводим унарный оператор 
        if((inputString.substr(i, 3) == unaryOperators[0]) || 
            (inputString.substr(i, 3) == unaryOperators[1]) || 
            (inputString.substr(i, 3) == unaryOperators[2]) || 
            (inputString.substr(i, 3) == unaryOperators[3]))
        {
            inputStringArray.push_back(inputString.substr(i, 3));
            promezString = {};
            signExist = 1;
            checkUnar = 1;
            continue;
        }

        // вводим кавычки
        if((inputString.substr(i, 1) == brackets[0]) || 
            (inputString.substr(i, 1) == brackets[1]))
        {
            if((promezString != "") && (inputString.substr(i, 1) == brackets[1]))
                {
                    inputStringArray.push_back(promezString);
                    promezString = {};  
                }
            inputStringArray.push_back(inputString.substr(i, 1));

            //считаем кавычки
            if(inputString.substr(i, 1) == brackets[0]) openBrackets++;
            if(inputString.substr(i, 1) == brackets[1]) closeBrackets++;

            signExist = 1;
            checkUnar = 0;
            continue;
        }

        // вводим переменную
        if(inputString.substr(i, 1) == variableX[0])
        {
            inputStringArray.push_back(inputString.substr(i, 1));
            varX = 1;
            signExist = 1;
            checkUnar = 0;
            promezString = {};
            // проверка x предшествует числу
            bool checkNextElement = 0;
            for(int j = 0; j < binaryOperators.length(); j++)
            {
                if(inputString.substr(i+1, 1) == binaryOperators.substr(j, 1)) checkNextElement = 1;
            }
            if(inputString.substr(i+1, 1) == brackets[1]) checkNextElement = 1;
            if(i == inputString.length()-1) checkNextElement = 1;
            
            if(checkNextElement != 1) return 1;

            // x последний
            if(i == inputString.length()-1) break;

            continue;
        }

        // если последний элемент число то вводим его
        if(i == inputString.length()-1 && promezString != "")
        {
            inputStringArray.push_back(promezString);
            promezString = {};
            break;
        }
        
        // проверка выражение на существование знака 
        if(signExist == 0 && checkUnar == 0)
        {
            return 1;
        }
    }
    if(openBrackets != closeBrackets) return 1;
return 0;
}




