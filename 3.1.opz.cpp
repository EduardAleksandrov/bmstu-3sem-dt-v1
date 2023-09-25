// Токенизация
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <array>

// using namespace std;

// bool cot (double, double*);

bool getTokenStringArray();

int main(void)
{
    // double retValue;
    // bool checkCot = cot(M_PI/2, &retValue);
    // if(checkCot == 0) cout << round(retValue*100)/100 << endl;
    // else cout << "ctg не определен";
    
    // if(isinf(sin(M_PI/2)/round(cos(M_PI/2)*1000)/1000) ==  1) cout << "tan не определен";
    // else cout << tan(M_PI/2) << "  ";

    // cout << sin(M_PI * 3/2) << " " << round(cos(M_PI * 3/2)*100)/100 << " " << round(tan(M_PI/2)*1000)/1000<< endl;

// Вводные данные
    std::string inputString {};
    std::vector<std::string> inputStringArray; 

    std::string programExpression {"55^cot(5)*5/5+sin(9)-(-66+22-cos(6))*x"};

    int choseInputExpression;
    for(;;)
    {
        std::cout << "1.Ввести выражение" << std::endl;
        std::cout << "2.Использовать программное" << std::endl;
        std::cin >> choseInputExpression;

        if(choseInputExpression == 1)
        {
            std::cout << "Введите:" << std::endl;
            std::cin >> inputString;
            break;
        }
        if(choseInputExpression == 2)
        {
            inputString = programExpression;
            break;
        }
        
        

    }


// 1) перевод данных во входную строку
    std::string numbers {"0123456789"};
    std::string binaryOperators {"+-*/^"};
    std::array<std::string, 2>  brackets {"(",")"};
    std::array<std::string, 4> unaryOperators {"sin", "cos", "tan", "cot"};
    std::array<std::string, 1> variableX {"x"};

    std::string promezString {};
    bool signExist, checkUnar;
    for(int i = 0; i < inputString.length(); i++)
    {
        signExist = 0;
        // накапливаем строки
        for(int j = 0; j < numbers.length(); j++)
        {
            if(inputString.substr(i, 1) == numbers.substr(j, 1))
            {
                promezString+=inputString.substr(i, 1);
                signExist = 1;
                checkUnar = 0;
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
            signExist = 1;
            checkUnar = 0;
        }

        // вводим переменную
        if(inputString.substr(i, 1) == variableX[0])
        {
            inputStringArray.push_back(inputString.substr(i, 1));
            signExist = 1;
            if(i == inputString.length()-1) break;
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
            std::cout << "Проверьте выражение на существование знака" << std::endl;
            exit(0);
        }
    }


    for(std::string n : inputStringArray)
        std::cout << n << "";
    std::cout << "\n";







    return 0;
}

// bool cot (double a, double *retValue)
// {
//     if(isinf(cos(a)/sin(a)) == 1) return 1;
//     else *retValue = cos(a)/sin(a);
// 	return 0;
// }