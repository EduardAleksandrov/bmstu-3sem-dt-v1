/*
    Task: Коммивояжер - метод муравьиного алгоритма
    расчет вероятности перехода
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

// стек
template <typename T>
class Stack
{
private:
    T *stack;
    T *stackBase, *stackPointer;
    int stack_size;
public:
    Stack(int s_size): stack_size{s_size}
    {
        try
        {
            stack = new T [stack_size + 1];
        }
        catch(const std::bad_alloc& e)
        {
            std::cerr << e.what() << std::endl;
            exit(1);
        }
        stackBase = stack;
        stackPointer = stack;
    }
    ~Stack()
    {
        delete [] stack;
        stack = nullptr;
    }
    
    bool pushStack(T value)
    {
        if(stackPointer == (stackBase + stack_size))
        {
            // std::cout << "Стек полон" << std::endl;
            return 1;
        }
        *stackPointer = value;
        stackPointer++;
        return 0;
    }
    
    void printStack()
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

    bool popStack(T &upperElement) 
    {
        if(stackPointer == stackBase)
        {
            return 1;
        }
        stackPointer--;
        upperElement = *stackPointer;
        return 0;
    }

    void getAllStack(std::vector<T>& all_stack)
    {
        int stackNum = stackPointer - stackBase;
        for(int i = 0; i < stackNum; i++)
            all_stack.push_back(stack[i]);
    }

};

double compute_func(double a, 
                    double g, 
                    int tmax, 
                    std::vector <std::vector<int>>& matrix,
                    std::vector <int>&);

int main()
{
// --- Ввод матриц из файла
    std::string file[] {"5.2.1.matrix_1.txt"};
    int file_number_one = 0;
    std::vector <std::vector<int>> matrix {};
    get_data(file[file_number_one], matrix);
    print_matrix<int>(matrix);
    if(matrix.size() != matrix.back().size())
    {
        std::cout << "Количество строк и столбцов не совпадает" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector <int> cities {};
    for(int i = 0; i < matrix.size(); i++)
    {
        cities.push_back(i+1);
    }
// --- end

    // a - alpha
    double a {0.1};
    double g {0.1};
    int tmax {100};
    double Lbest {0};
    std::vector <int> way {};
    Lbest = compute_func(a, g, tmax, matrix, way);










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
*/
double compute_func(double a, 
                    double g, 
                    int tmax, 
                    std::vector <std::vector<int>>& matrix,
                    std::vector <int>& way)
{
    srand(time(NULL));

    std::vector <int> cities {};
    for(int i = 0; i < matrix.size(); i++)
    {
        cities.push_back(i+1);
    }

    // b - betta
    double b = 1-a;

    // начальное значение феромона
    std::vector <std::vector<double>> feromon_m {};
    for(int i = 0; i < matrix.size(); i++)
    {
        feromon_m.push_back(std::vector<double>());
        for(int j = 0; j < matrix.back().size(); j++)
            feromon_m.back().push_back(g);
    }
    print_matrix<double>(feromon_m);

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
    std::cout << Lbest << "\n";

    // цикл по суткам
    std::vector <int> cities_k_ant{};
    double Lk {0};
    std::vector <double> ver_perehoda{}; //вероятность перехода
    for(int i = 1; i <= tmax; i++) // цикл по суткам
    {
        for(int k = 1; k <= cities.size(); k++) // цикл по муравьям
        {
            cities_k_ant.clear();
            Lk = 0;
            cities_k_ant.push_back(k);
            // cities_k_ant.push_back(2);
            // cities_k_ant.push_back(3);
            
            int counter {0};
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
                    // std::cout<<matrix[cities_k_ant[cities_k_ant.size()-1]][j-1] << " ";
                    double one{0}, two{0};
                    if(cities_k_ant[cities_k_ant.size()-1] != j)
                    {
                        one = pow(1.0/matrix[cities_k_ant[cities_k_ant.size()-1]-1][j-1],a); // последний посещенный город i- текущий город j
                        two = pow(feromon_m[cities_k_ant[cities_k_ant.size()-1]-1][j-1],b);
                        std::cout << 2 <<"\n";
                    }
                    double sumq {0};
                    for(int q = 1; q<=cities.size(); q++)
                    {
                        if(cities_k_ant[cities_k_ant.size()-1] != q)
                        {
                            for(int n = 0; n < cities_k_ant.size(); n++)
                            {
                                if(cities_k_ant[n] != q )
                                {
                                    sumq+= pow(1.0/matrix[cities_k_ant[cities_k_ant.size()-1]-1][q-1],a) * pow(feromon_m[cities_k_ant[cities_k_ant.size()-1]-1][q-1],b);
                                    // std::cout << 1;
                                }
                            }
                        }
                        
                    }
                    // std::cout << "\n";
                    // std::cout << one << " "<< two << " " <<sumq << "\n";
                    ver_perehoda.push_back(one*two/sumq);
                
                }
                // получить случайное число
                double rand_value;
                int precision {6};
                double min {0.00001};
                double max {0.99999};
                rand_value = rand() % (int)pow(10, precision); // получить случайное число как целое число с порядком precision
                rand_value = min + (rand_value / pow(10, precision)) * (max - min); // получить вещественное число
                std::cout<< rand_value <<"\n";
                // ---

                double sum_veroyt {0};
                int next_point {0};
                for(int i = 0; i<ver_perehoda.size(); i++)
                {
                    sum_veroyt+=ver_perehoda[i];
                    if(sum_veroyt <= rand_value && ver_perehoda[i] != 0)
                    {
                        next_point = i+1;
                    }
                }
                if(next_point == 0) next_point = 1;
                cities_k_ant.push_back(next_point);



                for(int i = 0; i<ver_perehoda.size();i++)
                        std::cout<<ver_perehoda[i] << " ";
                    std::cout << std::endl;
                double summ {0};
                for(int i = 0; i<ver_perehoda.size();i++)
                    summ += ver_perehoda[i];
                std::cout << "сумма вероятностей " << summ <<std::endl;
                // if(counter++ == 2) exit(1);
            }
            
        }
    }

    return Lbest;

}

