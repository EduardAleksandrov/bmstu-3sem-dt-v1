/*
    Task: разреженные матрицы часть 1. Схема Дженингса для симметричных матриц
    Получение данных из файлов
    Упаковка и распаковка
    Сумма
    Проверка двух типов суммирования
    К показу
    Исправления от преподавателя - работает
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// получение данных из файлов в матрицы
bool get_data_to_matrix(std::string, std::vector <std::vector<int>>&, int&);
//печать матрицы
void print_matrix(std::vector <std::vector<int>>&);
// Расчет обычным сложением
std::vector <std::vector<int>> ordinary_sum(std::vector <std::vector<int>>&, std::vector <std::vector<int>>&);

// упаковка матрицы
void package(std::vector <std::vector<int>>&, std::vector <int>&, std::vector <int>&);
// печать упакованной матрицы
void print_AN_D(std::vector <int>&, std::vector <int>&);

// распаковка матрицы
void unpackage(std::vector <std::vector<int>>&, std::vector <int>&, std::vector <int>&);

// суммирование матриц
void sum_packed_matrix(std::vector <int>&, 
                        std::vector <int>&, 
                        std::vector <int>&, 
                        std::vector <int>&, 
                        std::vector <int>&, 
                        std::vector <int>&);

// cравнение расчетов двумя типами
bool compare_matrix(std::vector <std::vector<int>>&, std::vector <std::vector<int>>&);


int main(void)
{
    // --- получение матриц из файла
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
    // --- получение матриц из файла конец

    // --- Расчет обычным сложением
    std::vector <std::vector<int>> result_ordinary_matrix {} ;
    result_ordinary_matrix = ordinary_sum(matrix_one, matrix_two);
    // --- Расчет обычным сложением конец

    if(one_size != two_size || matrix_one.size() != matrix_two.size() || matrix_one.back().size() != matrix_two.back().size())
    {
        std::cout << "Размеры матриц не совпадают" << std::endl;
        exit(1);
    }

    // --- упаковка матриц
    std::vector <int> AN_one {};
    std::vector <int> D_one {};
    std::vector <int> AN_two {};
    std::vector <int> D_two {};

    package(matrix_one, AN_one, D_one);
    print_AN_D(AN_one, D_one);
    package(matrix_two, AN_two, D_two);
    print_AN_D(AN_two, D_two);
    // --- упаковка матриц конец

    // --- сложение матриц
    std::vector <int> AN_sum {};
    std::vector <int> D_sum {};

    sum_packed_matrix(AN_one, D_one, AN_two, D_two, AN_sum, D_sum);
    print_AN_D(AN_sum, D_sum);
    // --- сложение матриц конец

    // --- распаковка матриц
    std::vector <std::vector<int>> unpacked_matrix {};
    unpackage(unpacked_matrix, AN_sum, D_sum);
    print_matrix(unpacked_matrix);
    // --- распаковка матриц конец

    // --- сравнение выриантов сложения
    bool check_compare_matrix;
    check_compare_matrix = compare_matrix(unpacked_matrix, result_ordinary_matrix);
    if(!check_compare_matrix)
    {
        std::cout << "Матрицы совпадают" << std::endl;
    } else {
        std::cout << "Матрицы не совпадают" << std::endl;
    }
    // --- сравнение выриантов сложения конец


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

std::vector <std::vector<int>> ordinary_sum(std::vector <std::vector<int>>& matrix_one, std::vector <std::vector<int>>& matrix_two)
{
    int n = matrix_one.size();
    int m = matrix_one.back().size();

    std::vector <std::vector<int>> result_matrix (n, std::vector<int>(m, 0));

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            result_matrix[i][j] = matrix_one[i][j] + matrix_two[i][j];
        }
    }

    return result_matrix;
}

void package(std::vector <std::vector<int>>& matrix, std::vector <int>& AN, std::vector <int>& D)
{
    int n = matrix.size();
    int m = matrix.back().size();

    int k {0};
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(i == 0 && j == 0)
            {
                AN.push_back(matrix[i][j]);
                continue;
            }
            for(int jj = 0;jj < m; jj++)
            {
                if(matrix[i][jj] != 0 && jj<i )
                {
                    k = jj;
                    break;
                }
                if(jj == i)
                {
                    k = jj;
                    break;
                }
            }
            if(j>=k && j<=i)
            {
                AN.push_back(matrix[i][j]);
            }

        }
        D.push_back(AN.size());
    }

    
}

void print_AN_D(std::vector <int>& AN, std::vector <int>& D)
{
    for(int i = 0; i< AN.size(); i++)
    {
        std::cout << AN[i] << " ";

    }
    std::cout << std::endl;
    
    for(int i = 0; i< D.size(); i++)
    {
        std::cout << D[i] << " ";

    }
    std::cout << std::endl << std::endl;
}

void unpackage(std::vector <std::vector<int>>& unpacked_matrix, std::vector <int>& AN, std::vector <int>& D)
{
    int n = D.size();

    for(int i = 0; i < n; i++)
    {
        unpacked_matrix.push_back(std::vector<int>());
        for(int j = 0; j < n; j++)
        {
            unpacked_matrix.back().push_back(0);
        }
    } 

    int k {0}; // массив d
    int p {0}; // массив AN
    int s {0}; // нули в массиве
    for(int i = 0; i < n; i++)
    {
        int z = 0, s = 0;
        for(int j = 0; j <= i; j++)
        {
            if(i == 0 && j == 0)
            {
                unpacked_matrix[i][j] = AN[p++];
                continue;
            }

            if((D[k]-D[k-1])<(i+1-s)) // заполняем вначале нулями до числа
            {
                unpacked_matrix[i][j] = 0;
                s++;
                continue;
            }

            while(z<(D[k]-D[k-1]))
            {
                unpacked_matrix[i][j] = AN[p++];
                z++;
                break;
            }
        }
        k++;
    }

    // заполнение симметричностью матрицы
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            unpacked_matrix[i][j] = unpacked_matrix[j][i];
        }
    }
}

void sum_packed_matrix(std::vector <int>& AN_one, 
                        std::vector <int>& D_one, 
                        std::vector <int>& AN_two, 
                        std::vector <int>& D_two, 
                        std::vector <int>& AN_sum, 
                        std::vector <int>& D_sum)
{
    int n = D_one.size();
    int k1 = 0, k2 = 0; // для AN_one, AN_two
    bool check = 0; // для нулей после числа 100 0 0
    for(int i = 0; i < n; i++)
    {
        if(i == 0)
        {
            AN_sum.push_back(AN_one[i] + AN_two[i]);
            D_sum.push_back(AN_sum.size());
            k1++;
            k2++;
            continue;
        }
        int x = D_one[i] - D_one[i-1]; // количество элементов
        int y = D_two[i] - D_two[i-1];
        if(x < y)
        {
            while(x<y)
            {
                AN_sum.push_back(AN_two[k2++]);
                check = 1;
                y--;
            }
        }

        if(x > y)
        {
            while(x>y)
            {
                AN_sum.push_back(AN_one[k1++]);
                check = 1;
                x--;
            }
        }

        if(x==y)
        {
            while(y>0)
            {
                if(x==1 && y==1) 
                {
                    AN_sum.push_back(AN_one[k1]+AN_two[k2]);
                    k1++;
                    k2++;
                    break;
                }
                // 1 0 3 + 2 0 8
                if(AN_one[k1]+AN_two[k2] != 0) 
                {
                    AN_sum.push_back(AN_one[k1]+AN_two[k2]);
                    check = 1;
                }
                if(check == 1 && AN_one[k1]+AN_two[k2] == 0) 
                {
                    AN_sum.push_back(AN_one[k1]+AN_two[k2]);
                }
                k1++;
                k2++;
                y--;
            }

        }
        check = 0;
        D_sum.push_back(AN_sum.size());
    }
}

bool compare_matrix(std::vector <std::vector<int>>& unpacked_matrix, std::vector <std::vector<int>>& result_ordinary_matrix)
{
    int n = unpacked_matrix.size();
    long int count {0};
    std::vector <std::vector<int>> check_m {};
    for(int i = 0; i<n; i++)
    {
        check_m.push_back(std::vector<int>());
        for(int j = 0; j<n; j++)
        {
            if(unpacked_matrix[i][j] - result_ordinary_matrix[i][j] == 0)
            {
                count++;
            }
            check_m.back().push_back(unpacked_matrix[i][j] - result_ordinary_matrix[i][j]);
        }
    }
    print_matrix(check_m);
    if(count == n*n) return 0;
    else return 1;
}



