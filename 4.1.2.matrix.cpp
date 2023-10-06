/*
    Task: разреженные матрицы
    Получение данных из файлов - работает
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// получение данных из файлов в матрицы
void get_data_to_matrix(std::string, std::vector <std::vector<int>>&, int&);
//печать матрицы
void print_matrix(std::vector <std::vector<int>>&);

int main(void)
{
    
    int one_size {0};
    int two_size {0};
    std::vector <std::vector<int>> matrix_one {};
    std::vector <std::vector<int>> matrix_two {};

    get_data_to_matrix("4.1.1.matrix1.txt", matrix_one, one_size);
    get_data_to_matrix("4.1.1.matrix2.txt", matrix_two, two_size);

    print_matrix(matrix_one);
    print_matrix(matrix_two);



    

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

// получение данных из файлов в матрицы
void get_data_to_matrix(std::string file_name, std::vector <std::vector<int>>& matrix, int& x_size)
{
    // поток для чтения
    std::ifstream in;
    in.open(file_name,std::ios::in);

    if (!in.is_open())
    {
        std::cout << "Ошибка открытия файла matrix1" << std::endl;
        exit(1);
    }   
    //размер матрицы (первый элемент в файле)
    in >> x_size;

    //элементы матрицы
    for(int i = 0; i < x_size; i++)
    {
        matrix.push_back(std::vector<int>());
        for(int j = 0; j < x_size; j++)
        {
            int x_data; 
            in >> x_data;
            matrix.back().push_back(x_data);
        }
    } 

    in.close();
}
