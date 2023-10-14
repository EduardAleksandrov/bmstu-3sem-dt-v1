/*
    Task: разреженные матрицы часть 2. Кольцевая схема Рейндболта - Местеньи (КРМ)
    Получение данных из файла
    Упаковка матрицы кольцевая - работает
*/


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

    
void get_data(std::string, std::vector <std::vector<int>>&);

void print_matrix(std::vector <std::vector<int>>&);

bool package(std::vector <std::vector<int>>&, 
            std::vector <int>&, 
            std::vector <int>&, 
            std::vector <int>&, 
            std::vector <int>&, 
            std::vector <int>&);

void print_packed_matrix(std::vector <int>&, 
                        std::vector <int>&, 
                        std::vector <int>&, 
                        std::vector <int>&, 
                        std::vector <int>&);

int main()
{
    std::string file[] {"4.2.1.matrix_1.txt", "4.2.1.matrix_2.txt", "4.2.1.matrix_0.txt", "4.2.1.matrix_test2.txt"};
    // int file_size = sizeof(file)/sizeof(file[0]);
    // int file_index_one;
    // int file_index_two;
    // for(;;)
    // {
    //     std::cout << "Введите какой файл использовать №1:" << std::endl;
    //     std::cout << "0. Выход" << std::endl;
    //     std::cout << "1. 4.2.1.matrix_1.txt" << std::endl;
    //     std::cout << "2. 4.2.1.matrix_2.txt" << std::endl;
    //     std::cout << "3. 4.2.1.matrix_0.txt" << std::endl;
    //     std::cout << "4. 4.2.1.matrix_test2.txt" << std::endl;
    //     for(;;)
    //     {
    //         std::cin >> file_index_one;
    //         if(file_index_one == 0) exit(0);
    //         if(file_index_one>0 && file_index_one<file_size+1) break;
    //     }
    //     std::cout << "Введите какой файл использовать №2:" << std::endl;
    //     for(;;)
    //     {
    //         std::cin >> file_index_two;
    //         if(file_index_two == 0) exit(0);
    //         if(file_index_two>0 && file_index_two<file_size+1) break;
    //     }
    //     if(file_index_one>0 && file_index_one<5 && file_index_two>0 && file_index_two<5) break;
    // }
// --- Ввод матриц из файла
    std::vector <std::vector<int>> matrix_one {};
    // get_data(file[file_index_one-1], matrix_one);
    get_data(file[2], matrix_one);
    print_matrix(matrix_one);

    // std::vector <std::vector<int>> matrix_two {};
    // get_data(file[1], matrix_two);
    // print_matrix(matrix_two);
// --- Ввод матриц из файла конец

// --- упаковка матриц
    std::vector <int> A_AN {};
    std::vector <int> A_NR {};
    std::vector <int> A_NC {};
    std::vector <int> A_JR {};
    std::vector <int> A_JC {};

    bool check_matrix_one; // если нулевая матрица
    check_matrix_one = package(matrix_one, A_AN, A_NR, A_NC, A_JR, A_JC);
    print_packed_matrix(A_AN, A_NR, A_NC, A_JR, A_JC);
// --- упаковка матриц конец






    return 0;
}

void get_data(std::string file, std::vector <std::vector<int>>& matrix)
{
    std::ifstream in;
    in.open(file,std::ios::in);

    if (!in.is_open())
    {
        std::cout << "Ошибка открытия файла matrix: " << file[0] << std::endl;
        exit(1);
    }

    //  убираем множественные пробелы из файла и считаем количество строк
    std::string s; // получаем строку с данными из файла, без лишних пробелов
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
    if(r < 2)
    {
        std::cout << "Проверьте строки в файле " << file << std::endl;
        exit(1);
    }
    in.clear();
    in.seekg(0);

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
        }
        columns.push_back(number_of_columns);
        number_of_columns = 0;
    }
    for(int i = 0; i < columns.size(); i++)
    {
        for(int j = i; j < columns.size(); j++)
        {
            if(columns[i] != columns[j])
            {
                std::cout << "Количество столбцов не совпадает, проверьте файл " << file << std::endl;
                exit(1);
            }
        }
    }

    //разбираем строки на токены и записываем в матрицу
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
        }
    }

    in.close(); 
}

void print_matrix(std::vector <std::vector<int>>& matrix)
{
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix.back().size(); j++)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool package(std::vector <std::vector<int>>& matrix, 
            std::vector <int>& AN, 
            std::vector <int>& NR, 
            std::vector <int>& NC, 
            std::vector <int>& JR, 
            std::vector <int>& JC)
{
    // инициализировали JR JC
    for(int i = 0; i < matrix.size(); i++)
        JR.push_back(-1);
    for(int i = 0; i < matrix.back().size(); i++)
        JC.push_back(-1);
    // посчитали AN, JR, JC
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix.back().size(); j++)
        {
            if(matrix[i][j] != 0)
            {
                AN.push_back(matrix[i][j]);
                if(JR[i] == -1) JR[i] = AN.size();
                if(JC[j] == -1) JC[j] = AN.size();
            }
        }
    }
    // если нулевая матрица
    if(AN.size() == 0) return 1; 
    // инициализировали NR NC
    for(int i = 0; i < AN.size(); i++)
    {
        NR.push_back(-1);
        NC.push_back(-1);
    }

    // расчет NR NC
    int k {0}; //счетчик номеров элементов
    bool flag_row {0}; // флаг последнего элемента в строке

    int t {0}; // счетчик для NC
    int count {0}; // расчет номера элемента
    bool flag_column {0}; // флаг последнего элемента в столбце
    bool check_count_element {0}; // выход из цикла при совпадении номеров элементов
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix.back().size(); j++)
        {
            if(matrix[i][j] != 0)
            {
                // для строк
                for(int n = j; n < matrix.back().size(); n++)
                {
                    flag_row = 0;
                    if(matrix[i][n] != 0 && n>j)
                    {
                        NR[k] = k+2;
                        // std::cout << NR[k] << " ";
                        k++;
                        flag_row = 1;
                        
                        break;
                    } 
                }
                // если последний или единственный элемент в строке
                if(flag_row == 0)
                {
                    NR[k] = JR[i];
                    // std::cout << NR[k] << " ";
                    k++;
                }
                // для столбцов
                for(int m = i; m < matrix.size(); m++)
                {
                    flag_column = 0;
                    if(matrix[m][j] != 0 && m>i)
                    {
                        // счетчик элементов
                        count = 0;
                        check_count_element = 0;
                        for(int ii = 0; ii < matrix.size(); ii++)
                        {
                            for(int jj = 0; jj < matrix.back().size(); jj++)
                            {
                                if(matrix[ii][jj] != 0)
                                {
                                    count++;
                                }
                                if(m == ii && j == jj)
                                {
                                    check_count_element = 1;
                                    break;
                                } 
                            }
                            if (check_count_element == 1) break;
                        }
                        
                        if(NC[t] == -1) NC[t] = count;
                        t++;
                        flag_column = 1;
                        break; // заполняется только нижележащий столбец
                    }
                }
                // если последний или единственный элемент в столбце
                if(flag_column == 0)
                {
                    if(NC[t] == -1) NC[t] = JC[j];
                    t++;
                }
            }
        }
    }
    return 0;
}

void print_packed_matrix(std::vector <int>& AN, 
                        std::vector <int>& NR, 
                        std::vector <int>& NC, 
                        std::vector <int>& JR, 
                        std::vector <int>& JC)
{
    std::cout << "AN: ";
    for(int i = 0; i < AN.size(); i++)
        std::cout << AN[i] << " ";
    std::cout << std::endl;
    std::cout << "JR: ";
    for(int i = 0; i < JR.size(); i++)
        std::cout << JR[i] << " ";
    std::cout << std::endl;
    std::cout << "JC: ";
    for(int i = 0; i < JC.size(); i++)
        std::cout << JC[i] << " ";
    std::cout << std::endl;
    std::cout << "NR: ";
    for(int i = 0; i < NR.size(); i++)
        std::cout << NR[i] << " ";
    std::cout << std::endl;
    std::cout << "NC: ";
    for(int i = 0; i < NC.size(); i++)
        std::cout << NC[i] << " ";
    std::cout << std::endl << std::endl;;
}




