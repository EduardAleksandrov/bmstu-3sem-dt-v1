/*
    Task: разреженные матрицы
    Получение данных из файлов - работает
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// получение данных из файлов в матрицы
bool get_data_to_matrix(std::string, std::vector <std::vector<int>>&, int&);
//печать матрицы
void print_matrix(std::vector <std::vector<int>>&);

int main(void)
{
    
    int one_size {0};
    int two_size {0};
    std::vector <std::vector<int>> matrix_one {};
    std::vector <std::vector<int>> matrix_two {};
    bool check;
    
    check = get_data_to_matrix("4.1.1.matrix1.txt", matrix_one, one_size);
    if(check == 1)
    {
        std::cout << "Не хватает данных в файле 1" << std::endl;
        exit(1);
    }
    check = get_data_to_matrix("4.1.1.matrix2.txt", matrix_two, two_size);
    if(check == 1)
    {
        std::cout << "Не хватает данных в файле 2" << std::endl;
        exit(1);
    }

    print_matrix(matrix_one);
    print_matrix(matrix_two);



    

    return 0;
}


// получение данных из файлов в матрицы
bool get_data_to_matrix(std::string file_name, std::vector <std::vector<int>>& matrix, int& x_size)
{
    // поток для чтения
    std::ifstream in;
    in.open(file_name,std::ios::in);

    if (!in.is_open())
    {
        std::cout << "Ошибка открытия файла matrix: " << file_name << std::endl;
        exit(1);
    }   
    //размер матрицы (первый элемент в файле)
    in >> x_size;

    //элементы матрицы
    int x_data;
    for(int i = 0; i < x_size; i++)
    {
        matrix.push_back(std::vector<int>());
        for(int j = 0; j < x_size; j++)
        {
            in >> x_data;
            if(!in)
            {   
                in.close();
                return 1;
            }
            matrix.back().push_back(x_data);
        }
    } 

    in.close();
    return 0;
}

//печать матрицы
void print_matrix(std::vector <std::vector<int>>& matrix)
{
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix.back().size(); j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
