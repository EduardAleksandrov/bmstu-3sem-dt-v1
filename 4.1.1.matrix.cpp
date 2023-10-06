#include <iostream>
#include <fstream>
#include <vector>


int main(void)
{

// получение матрицы из файла
    // матрица 1
    std::ifstream in_one;       // поток для чтения
    in_one.open("4.1.1.matrix1.txt",std::ios::in);

    if (!in_one.is_open())
    {
        std::cout << "Ошибка открытия файла matrix1" << std::endl;
        exit(1);
    }   
        //размер матрицы
    int x_size;
    in_one >> x_size;
    std::cout << x_size << std::endl;

    // std::vector <int> matrix_one {};
    // for(int i = 0; i<x*x; i++)
    // {
    //     int x;
    //     in_one >> x;
    //     matrix_one.push_back(x);
    //     std::cout << matrix_one[i] << "";
    // }
        
        //элементы матрицы
    std::vector <std::vector <int>> matrix_one {};
    for(int i = 0; i < x_size; i++)
    {
        matrix_one.push_back(std::vector<int>());
        for(int j = 0; j < x_size; j++)
        {
            int x_data; 
            in_one >> x_data;
            matrix_one.back().push_back(x_data);
        }
    }
        //печать матрицы
    for(int i = 0; i < x_size; i++)
    {
        for(int j = 0; j < x_size; j++)
        {
            std::cout<<matrix_one[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    in_one.close();

    // матрица 2
    std::ifstream in_two;       // поток для чтения
    in_two.open("4.1.1.matrix2.txt",std::ios::in);

    if (!in_two.is_open())
    {
        std::cout << "Ошибка открытия файла matrix2" << std::endl;
        exit(1);
    }   

    int xx_size;
    in_two >> xx_size;
    std::cout << xx_size << std::endl;

    std::vector <std::vector <int>> matrix_two {};
    for(int i = 0; i < xx_size; i++)
    {
        matrix_two.push_back(std::vector<int>());
        for(int j = 0; j < xx_size; j++)
        {
            int x_data; 
            in_two >> x_data;
            matrix_two.back().push_back(x_data);
        }
    }
    for(int i = 0; i < xx_size; i++)
    {
        for(int j = 0; j < xx_size; j++)
        {
            std::cout<<matrix_two[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    in_two.close();

    return 0;
}