/*
    Task: Коммивояжер - метод муравьиного алгоритма
    расчет вероятности перехода равен единице - работает
    сохранение путей и вычисление минимального - работает
    матрица феромона - работает
    построение таблицы не полной  - готово
    таблица полная - работает
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <cmath>

// получение данных
void get_data(std::string, std::vector <std::vector<int>>&);
// печать обычной матрицы
template <typename T>
void print_matrix(std::vector <std::vector<T>>&);
// вычисление (муравьиный алгоритм)
double compute_func(double a, 
                    double g, 
                    int tmax, 
                    std::vector <std::vector<int>>& matrix,
                    std::vector <int>&);

int main()
{
// --- Ввод матриц из файла
    // std::string file[] {"5.2.1.matrix_1.txt"};
    // int file_number_one = 0;
    // std::vector <std::vector<int>> matrix {};
    // get_data(file[file_number_one], matrix);
    // print_matrix<int>(matrix);
    // if(matrix.size() != matrix.back().size())
    // {
    //     std::cout << "Количество строк и столбцов не совпадает" << std::endl;
    //     exit(EXIT_FAILURE);
    // }
    // std::vector <int> cities {};
    // for(int i = 0; i < matrix.size(); i++)
    // {
    //     cities.push_back(i+1);
    // }
// --- end

    // a - alpha
    // double a {0.1};
    // double g {0.1};
    // int tmax {100};
    // double Lbest {0};
    // std::vector <int> way {};
    // Lbest = compute_func(a, g, tmax, matrix, way);

// --- Ввод матриц из файла
    std::string file[] {"5.2.1.matrix_2.txt", "5.2.1.matrix_3.txt", "5.2.1.matrix_4.txt"};
    int file_number_one = 0;
    int file_number_two = 1;
    int file_number_three = 2;
    std::vector <std::vector<int>> matrix_1 {}; // Lэ = 14
    std::vector <std::vector<int>> matrix_2 {}; // Lэ = 14
    std::vector <std::vector<int>> matrix_3 {}; // Lэ = 16
    get_data(file[file_number_one], matrix_1);
    if(matrix_1.size() != matrix_1.back().size())
    {
        std::cout << "Количество строк и столбцов не совпадает" << std::endl;
        exit(EXIT_FAILURE);
    }
    get_data(file[file_number_two], matrix_2);
    if(matrix_2.size() != matrix_2.back().size())
    {
        std::cout << "Количество строк и столбцов не совпадает" << std::endl;
        exit(EXIT_FAILURE);
    }
    get_data(file[file_number_three], matrix_3);
    if(matrix_3.size() != matrix_3.back().size())
    {
        std::cout << "Количество строк и столбцов не совпадает" << std::endl;
        exit(EXIT_FAILURE);
    }

// --- end

    std::vector <int> tmax = {50, 100, 200, 500, 1000};
    std::vector <double> a = {0.1, 0.25, 0.5, 0.75, 0.9};
    std::vector <double> g = {0.1, 0.25, 0.5, 0.75, 0.9};
    // a - alpha
    double Lbest_one {0};
    double Lbest_two {0};
    double Lbest_three {0};
    std::vector <int> way_one {};
    std::vector <int> way_two {};
    std::vector <int> way_three {};
    int diff_one {0};
    int diff_two {0};
    int diff_three {0};
    int maxf {0};
    int maxp {0};

    std::cout << "a" <<"\t"<< "q" << "\t" << "tmax" << "\t" << "Lb_1" << "\t" << "Lb_2"<<"\t" << "Lb_3"<< "\t"<<"Lb1-Lэ1" << "\t" << "Lb2-Lэ2" << "\t" << "Lb3-Lэ3"<< "\t" << "maxp" << "\t\t" << "ways_L1" << "\t\t" << "ways_L2" << "\t\t" << "ways_L3"<< std::endl;

    for(int i = 0; i < tmax.size(); i++)
    {
        for(int j = 0; j < a.size(); j++)
        {
            for(int n = 0; n < g.size(); n++)
            {
                Lbest_one = compute_func(a[j], g[n], tmax[i], matrix_1, way_one);
                Lbest_two = compute_func(a[j], g[n], tmax[i], matrix_2, way_two);
                Lbest_three = compute_func(a[j], g[n], tmax[i], matrix_3, way_three);

                diff_one = Lbest_one-14;
                diff_two = Lbest_two-14;
                diff_three = Lbest_three-16;

                maxf = std::max(diff_one, diff_two);
                maxp = std::max(maxf, diff_three);

                std::cout << a[j] <<"\t"<< g[n] << "\t" << tmax[i] << "\t" << Lbest_one << "\t" << Lbest_two << "\t" << Lbest_three << "\t" << diff_one << "\t" << diff_two << "\t" << diff_three << "\t" << maxp <<"\t\t";
                
                for(int t = 0; t< way_one.size(); t++)
                    std::cout << way_one[t] << "";
                std::cout << "\t";
                for(int t = 0; t< way_two.size(); t++)
                    std::cout << way_two[t] << "";
                std::cout << "\t";
                for(int t = 0; t< way_three.size(); t++)
                    std::cout << way_three[t] << "";
                std::cout << "\t";

                std::cout << std::endl;
            }
        }
    }

    std::cout << std::endl;


    return 0;
}

/*
 in: file
 out: matrix
*/
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
    if(r < 1)
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

/*
 in: matrix
*/
template <typename T>
void print_matrix(std::vector <std::vector<T>>& matrix)
{
    if(matrix.size() == 0) return;
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix.back().size(); j++)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/*
 out: Lbest
      way best
*/
double compute_func(double a, 
                    double g, 
                    int tmax, 
                    std::vector <std::vector<int>>& matrix,
                    std::vector <int>& way)
{
    srand(time(NULL));
    way.clear();

    std::vector <int> cities {};
    for(int i = 0; i < matrix.size(); i++)
    {
        cities.push_back(i+1);
    }

    // b - betta
    double b = 1-a;

    // начальное значение феромона g - gmin
    std::vector <std::vector<double>> feromon_m {};
    for(int i = 0; i < matrix.size(); i++)
    {
        feromon_m.push_back(std::vector<double>());
        for(int j = 0; j < matrix.back().size(); j++)
            feromon_m.back().push_back(g);
    }
    // print_matrix<double>(feromon_m);

    //Q
    double sum {0};
    double kol {0};
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix.back().size(); j++)
            if(i!=j)
            {
                sum+=matrix[i][j];
                kol++;
            }
    }
    double Q = (sum/kol)/2;
    // std::cout << sum << " "<< kol << " " <<Q << "\n";

    // Lfirstbest
    std::vector <int> ways{};
    for(int i = 0; i<cities.size(); i++)
        ways.push_back(cities[i]);
    double Lbest {0};
    int ii, jj;
    for(int i = 0; i < ways.size()-1; i++)
    {
        ii = ways[i];
        jj = ways[i+1];
        Lbest += matrix[ii-1][jj-1];
    }
    // std::cout << Lbest << "\n";

    // цикл по суткам
    std::vector <int> cities_k_ant{};
    double Lk {0};
    std::vector <double> ver_perehoda{}; //вероятность перехода
    std::vector <std::vector<int>> ant_ways_day {}; // матрица путей за k день
    for(int i = 1; i <= tmax; i++) // цикл по суткам
    {
        ant_ways_day.clear();
        int counter {0};
        for(int k = 1; k <= cities.size(); k++) // цикл по муравьям
        {
            cities_k_ant.clear();
            Lk = 0;
            cities_k_ant.push_back(k);
            
            // int counter {0};
            while(cities_k_ant.size() != cities.size()) // проход пути одним муравьем
            {
                ver_perehoda.clear();
                for(int j = 1; j <=cities.size(); j++) // вероятность перехода в след город
                {
                    bool check_cities {0};
                    for(int n = 0; n < cities_k_ant.size(); n++)
                    {
                        if(cities_k_ant[n] == j)
                        {
                            ver_perehoda.push_back(0);
                            check_cities = 1;
                            break;
                        }
                    }
                    if(check_cities == 1) continue;
                    
                    double one{0}, two{0};
                    if(cities_k_ant[cities_k_ant.size()-1] != j)
                    {
                        one = pow(1.0/matrix[cities_k_ant[cities_k_ant.size()-1]-1][j-1],a); // последний посещенный город i- текущий город j
                        two = pow(feromon_m[cities_k_ant[cities_k_ant.size()-1]-1][j-1],b);
                        // std::cout << 2 <<"\n";
                    }
                    double sumq {0};
                    std::vector <bool> visited_city{};
                    for(int j = 0; j<cities.size(); j++)
                    {
                        visited_city.push_back(0);
                    }
                    for(int i = 0; i < cities_k_ant.size(); i++)
                    {
                        visited_city[cities_k_ant[i]-1] = 1;
                    }
                    for(int i = 0; i<visited_city.size(); i++)
                    {
                        if(visited_city[i] == 1) visited_city[i]=0;
                        else visited_city[i]=1;
                    }
                    // for(int i = 0; i<visited_city.size(); i++)
                    //     std::cout << visited_city[i] << " ";

                    for(int q = 0; q<cities.size(); q++)
                    {
                        if(visited_city[q] == 0) continue;
                        else {
                            sumq+= pow(1.0/matrix[cities_k_ant[cities_k_ant.size()-1]-1][q],a) * pow(feromon_m[cities_k_ant[cities_k_ant.size()-1]-1][q],b);
                            // std::cout<< "sum" << sumq<<"\n";
                        }
                    }
                    
                    ver_perehoda.push_back(one*two/sumq);
                }
                // std::cout << std::endl;

                // получить случайное число
                double rand_value;
                int precision {6};
                double min {0.00001};
                double max {0.99999};
                rand_value = rand() % (int)pow(10, precision); // получить случайное число как целое число с порядком precision
                rand_value = min + (rand_value / pow(10, precision)) * (max - min); // получить вещественное число
                // std::cout<< "Случайное число: "<<rand_value <<"\n";
                // ---
                // расчет следующего города через вероятность перехода и случайное число
                double sum_veroyt {0};
                int next_point {0};
                for(int i = 0; i<ver_perehoda.size(); i++)
                {
                    sum_veroyt+=ver_perehoda[i];
                    if(sum_veroyt >= rand_value && ver_perehoda[i] != 0)
                    {
                        next_point = i+1;
                        break;
                    }
                }
                if(next_point == 0) 
                {
                    for(int i = 0; i< ver_perehoda.size(); i++)
                        if(ver_perehoda[i] != 0) next_point = i+1;
                }
                
                cities_k_ant.push_back(next_point);
                //---
                
                //печать
                // for(int i = 0; i<ver_perehoda.size();i++)
                //         std::cout<<ver_perehoda[i] << " ";
                //     std::cout << std::endl;
                // double summ {0};
                // for(int i = 0; i<ver_perehoda.size();i++)
                //     summ += ver_perehoda[i];
                // std::cout << "сумма вероятностей " << summ <<std::endl;
                // std::cout << "k_ant_size " << cities_k_ant.size() <<std::endl;
                // if(counter++ == 2) exit(1);
            }
            
            ant_ways_day.push_back(std::vector<int>());
            for(int i = 0; i < cities_k_ant.size(); i++)
            {
                ant_ways_day.back().push_back(cities_k_ant[i]);
            }



        }
        // печать
        // for(int i = 0; i < ant_ways_day.size(); i++)
        // {
        //     for(int j = 0; j < ant_ways_day.back().size(); j++)
        //         std::cout << ant_ways_day[i][j] <<" ";
        //     std::cout << std::endl;
        // }
        //вычисление минимального пути на основе полученных путей
        double L {0};
        int ii, jj;
        for(int j = 0; j<ant_ways_day.size();j++)
        {
            L = 0;
            for(int i = 0; i < ant_ways_day.back().size()-1; i++)
            {
                ii = ant_ways_day[j][i];
                jj = ant_ways_day[j][i+1];
                L += matrix[ii-1][jj-1];
            }
            if(L<Lbest)
            {
                Lbest = L;
                way.clear();
                for(int n = 0; n<ant_ways_day.back().size(); n++)
                    way.push_back(ant_ways_day[j][n]);
            }
        // std::cout << L << "\n";
        }


        // печать
        // for(int n = 0; n<way.size(); n++)
        //     std::cout<<way[n] << " ";
        // std::cout << "\n";
        // std::cout << Lbest << "\n";

    //расчет феромона
        // испарение
        for(int i = 0; i<feromon_m.size(); i++)
        {
            for(int j = 0; j < feromon_m.back().size(); j++)
            {
                feromon_m[i][j] = feromon_m[i][j]*g;
                // std::cout << feromon_m[i][j] << " ";
            }
            // std::cout<<std::endl;
        }
        // по муравьям
        for(int k = 1; k <= cities.size(); k++) // цикл по муравьям
        {
            double Lk = 0;
            int ii, jj;
            for(int i = 0; i < ant_ways_day.back().size()-1; i++)
            {
                ii = ant_ways_day[k-1][i];
                jj = ant_ways_day[k-1][i+1];
                Lk += matrix[ii-1][jj-1];
            }
            ii = 0;
            jj = 0;
            for(int i = 0; i < ant_ways_day.back().size()-1; i++)
            {
                ii = ant_ways_day[k-1][i];
                jj = ant_ways_day[k-1][i+1];
                feromon_m[ii-1][jj-1] = feromon_m[ii-1][jj-1]+Q/Lk;
                feromon_m[jj-1][ii-1] = feromon_m[jj-1][ii-1]+Q/Lk;
            }

        }
        // Пост проверка матрицы феромона
        for(int i = 0; i<feromon_m.size(); i++)
        {
            for(int j = 0; j < feromon_m.back().size(); j++)
            {
                if(feromon_m[i][j] < 0.1) // qmin = 0.1
                {
                    feromon_m[i][j] = 0.1;
                }
            }
        }
        //печать матрицы феромона
        // for(int i = 0; i<feromon_m.size(); i++)
        // {
        //     for(int j = 0; j < feromon_m.back().size(); j++)
        //     {
        //         std::cout << feromon_m[i][j] << " ";
        //     }
        //     std::cout<<std::endl;
        // }
    //--- end расчет феромона


        // if(counter++ == 0) exit(1);


    }

    return Lbest;

}

