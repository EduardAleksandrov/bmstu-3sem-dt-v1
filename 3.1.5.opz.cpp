// Токенизация вынесена в функцию
// Добавлен ввод данных
// Добавлен стек - работает
// Добавлена ОПЗ кроме минуса - работает
// Добавлен унарный минус - работает

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <array>
#include <map>

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
// 2) ОПЗ - постфиксная запись
bool opz(std::string *stackString, 
        std::string *stackBaseString, 
        std::string *stackPointerString, 
        int stacksizeString, 
        std::vector<std::string>,
        std::vector<std::string>&);
// ОПЗ - постфиксная запись - конец

int main(void)
{
// Вводные данные
    std::string inputString {};
    // если в выражении есть x
    double xmin {0};
    double xmax {0};
    double h, hConst {0};
    
    std::vector<std::string> inputStringArray; //массив токенов, входная строка

    // --- программные данные
    std::string programExpression {"2^(cot(5)*5/5*x+sin(x)-(-66+22-cos(4))+50-x)"}; //программное выражение
    // {"2^(cot(5)*5/5*x+sin(x)-(-66+22-cos(4))+50-x)"}
    // "(2^2)*sin(4)"
    // 10+18*(1+7-8*2/(1/3)+1)+10
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
    std::cout << std::endl;

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

// --- Выходная строка ОПЗ
    std::vector<std::string> outputStringArray; 
    /*
        Перевод в ОПЗ
        in - stack
        in - inputStringArray
        out - outputStringArray
    */
    bool result = 0;
    result = opz(stackString, stackBaseString, stackPointerString, stacksizeString, inputStringArray, outputStringArray);
    if(result) exit(1);
    
    // печать ОПЗ
    std::cout << "OPZ строка: ";
    for(std::string n : outputStringArray)
        std::cout << n << " ";
    std::cout << std::endl;
    // конец печати
// --- Выходная строка ОПЗ конец








    return 0;
}

// 2) Обратная Польская Запись
bool opz(std::string *stackString, 
        std::string *stackBaseString, 
        std::string *stackPointerString, 
        int stacksizeString, 
        std::vector<std::string> inputStringArray,
        std::vector<std::string> &outputStringArray)
{
    // Приоритеты операций
    std::map<std::string, int> priorityOperations;
    // установка значений
    priorityOperations["+"] = 1;
    priorityOperations["-"] = 1;
    priorityOperations["*"] = 2;
    priorityOperations["/"] = 2;
    priorityOperations["^"] = 3;
    priorityOperations["sin"] = 4;
    priorityOperations["cos"] = 4;
    priorityOperations["tan"] = 4;
    priorityOperations["cot"] = 4;
    priorityOperations["("] = 5;

    std::string numbers {"0123456789"};
    std::string binaryOperators {"+-*/^"};
    std::array<std::string, 2>  brackets {"(",")"};
    std::array<std::string, 4> unaryOperators {"sin", "cos", "tan", "cot"};
    std::array<std::string, 1> variableX {"x"};
    std::array<std::string, 10> allOperators {"+","-","*","/","^","sin", "cos", "tan", "cot", "%"};
    std::string minusSign {"%"};

    outputStringArray = {};
    stackPointerString = stackBaseString;

    bool checkStack = 0;
    bool continueThree = 0;
    // 1
    for(int i = 0; i < inputStringArray.size(); i++)
    {
        // 2
        for(int j = 0; j < numbers.length(); j++)
        {
            if(inputStringArray[i].substr(0, 1) == numbers.substr(j, 1))
            {
                outputStringArray.push_back(inputStringArray[i]);
                break;
            }
        }
        // 2
        if(inputStringArray[i] == variableX[0])
        {
            outputStringArray.push_back(inputStringArray[i]);
            continue;
        }
        // 3
        for(;;)
        {
            // 3.0
            if(inputStringArray[i] == brackets[0])
            {
                checkStack = pushStack(inputStringArray[i], stackBaseString, &stackPointerString, stacksizeString);
                if(checkStack == 1) std::cout << "Стек полон" << std::endl;
                break;
            }
            // 3.a
            if(inputStringArray[i] == brackets[1])
            {
                for(;;)
                {
                    std::string upperEl {};
                    checkStack = upperElement(upperEl, stackBaseString, stackPointerString);
                    if(upperEl != brackets[0])
                    {
                        std::string outputStack {};
                        checkStack = popStack(outputStack, stackBaseString, &stackPointerString);
                        if(checkStack == 1) 
                        {
                            std::cout << "Стек пуст, ошибка разбора" << std::endl;
                            return 1;
                        }
                        outputStringArray.push_back(outputStack);
                    } else {
                        std::string outputStack {};
                        checkStack = popStack(outputStack, stackBaseString, &stackPointerString);
                        if(checkStack == 1) std::cout << "Стек пуст" << std::endl;
                        break;
                    }
                }
            }
            // 3.1
            for(int j = 0; j < 10; j++)
            {
                if(inputStringArray[i] == allOperators[j])
                {
                    // 3.1.0.- Отрицательное число скобки при его написании обязательны 5-(-6)
                    // std::string upperEl {};
                    // checkStack = upperElement(upperEl, stackBaseString, stackPointerString);
                    // if(checkStack == 1) std::cout << "Стек пуст" << std::endl;
                    // std::string minus {"-"};
                    // if(inputStringArray[i] == minus)
                    // {
                    //     if(upperEl == brackets[0])
                    //     {
                    //         outputStringArray.push_back("0");
                    //         checkStack = pushStack(minus, stackBaseString, &stackPointerString, stacksizeString);
                    //         if(checkStack == 1) std::cout << "Стек полон" << std::endl;
                    //         continueThree = 0;
                    //         break;
                    //     }
                    // }
                    
                    // !3.1.0.- Отрицательное число скобки при его написании обязательны 5-(-6)
                    if(inputStringArray[i] == minusSign)
                    {
                        outputStringArray.push_back(numbers.substr(0, 1));
                        checkStack = pushStack(binaryOperators.substr(1, 1), stackBaseString, &stackPointerString, stacksizeString);
                        if(checkStack == 1) std::cout << "Стек полон" << std::endl;
                        continueThree = 0;
                        break;
                    }
                    
                    // 3.1.a
                    if(stackBaseString == stackPointerString)
                    {
                        checkStack = pushStack(inputStringArray[i], stackBaseString, &stackPointerString, stacksizeString);
                        if(checkStack == 1) std::cout << "Стек полон" << std::endl;
                        continueThree = 0;
                        break;
                    // 3.1.b
                    } else {
                        // 3.1.b.a
                        std::string upperEl {};
                        checkStack = upperElement(upperEl, stackBaseString, stackPointerString);
                        if(checkStack == 1) std::cout << "Стек пуст" << std::endl;
                        if(upperEl == brackets[0])
                        {
                            checkStack = pushStack(inputStringArray[i], stackBaseString, &stackPointerString, stacksizeString);
                            if(checkStack == 1) std::cout << "Стек полон" << std::endl; 
                            continueThree = 0;
                            break;
                        }
                        // 3.1.b.b
                        int priorityStack = 0;
                        int priorityInput = 0;
                        for (const auto& element : priorityOperations)
                        {
                            if(element.first == upperEl) priorityStack = element.second;
                            if(element.first == inputStringArray[i]) priorityInput = element.second;
                        }
                        if(priorityStack < priorityInput)
                        {
                            checkStack = pushStack(inputStringArray[i], stackBaseString, &stackPointerString, stacksizeString);
                            if(checkStack == 1) std::cout << "Стек полон" << std::endl;
                            continueThree = 0;
                            break;
                        }
                        // 3.1.b.в.
                        std::string outputStack {};
                        checkStack = popStack(outputStack, stackBaseString, &stackPointerString);
                        if(checkStack == 1) std::cout << "Стек пуст" << std::endl;
                        outputStringArray.push_back(outputStack);
                        continueThree = 1;
                        break;
                    }
                }
            }
            if(continueThree == 1) continue;
            break;
        }
    }

    for(int i = 0; i < stackPointerString-stackBaseString+1; i++)
    {
        std::string outputStack {};
        checkStack = popStack(outputStack, stackBaseString, &stackPointerString);
        if(checkStack == 1) std::cout << "Стек пуст" << std::endl;
        outputStringArray.push_back(outputStack);
    }

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

        //! поиск унарного оператора минуса (скобки обязательны)
        if(i > 0 && inputString.substr(i, 1) == binaryOperators.substr(1, 1) && inputString.substr(i-1, 1) == brackets[0])
        {
            std::string minusSign {"%"};
            inputStringArray.push_back(minusSign);
            signExist = 1;
            checkUnar = 0;
            continue;
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




