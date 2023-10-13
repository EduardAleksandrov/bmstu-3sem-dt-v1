/*
    Task: разреженные матрицы часть 2. Кольцевая схема Рейндболта - Местеньи (КРМ)
    Получение данных из файла - работает

*/


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>



int main()
{
    std::string file[] {"4.2.1.matrix_1.txt"};
    std::ifstream in;
    in.open(file[0],std::ios::in);

    if (!in.is_open())
    {
        std::cout << "Ошибка открытия файла matrix: " << file[0] << std::endl;
        exit(1);
    }
    // считаем количество строк
    // int k {0};
    // char c {};
    // while(in)
    // {
    //     if((c = in.get()) == '\n') k++; // считаем количество строк
    // }
    // in.clear();
    // in.seekg(0);

    //  убираем множественные пробелы из файла и считаем количество строк
    std::string s;
    bool flag {0}; //если найден первый пробел, то остальные пропускаем
    int r {0}; // считаем количество строк
    char c;
    while(in)
    {
        c = in.get();
        if(in.eof()) break;
        if(c == '\n')
        {
            r++;
        }
        if(c != ' ')
        {
            s+=c;
            flag = 0;
            continue;
        } 
        if(c == ' ' && flag == 0) 
        {
            s+=c;
            flag = 1;
        }
        
    }
    // std::cout << s << "\n" << k;
    in.clear();
    in.seekg(0);

    // std::string line, l;
    // char delimeter = ' ';
    // while(std::getline(in, line))
    // {
    //     std::stringstream stream(line);
    //     while(std::getline(stream, l, delimeter))
    //     {
    //         std::cout << l << " ";
    //     }
    // }
    

    // считаем количество столбцов
    std::string line, l;
    char delimeter = ' ';
    
    std::stringstream stream(s);
    int number_of_columns {0};
    std::vector <int> columns {};
    while(std::getline(stream, line))
    {
        std::stringstream stream_two(line);
        while(std::getline(stream_two, l, delimeter))
        {
            number_of_columns++;
            // std::cout << l << " ";
        }
        columns.push_back(number_of_columns);
        number_of_columns = 0;
    }
    for(int i = 0; i<columns.size(); i++)
    {
        for(int j = i; j<columns.size(); j++)
        {
            if(columns[i] != columns[j])
            {
                std::cout << "Количество столбцов не совпадает" << std::endl;
                exit(1);
            }
        }
    }
        
    //разбираем строки на токены и записываем в матрицу
    std::vector <std::vector<int>> matrix {};
    std::stringstream stream_one(s);
    line = {};
    l = {};
    while(std::getline(stream_one, line))
    {
        matrix.push_back(std::vector<int>());
        std::stringstream stream_two(line);
        while(std::getline(stream_two, l, delimeter))
        {
            matrix.back().push_back(std::stoi(l));
            // std::cout << l << " ";
        }
    }

    for(int i = 0; i < r; i++)
        for(int j = 0; j < matrix.back().size(); j++)
            std::cout << matrix[i][j] << " ";
    
    in.close(); 


    return 0;
}