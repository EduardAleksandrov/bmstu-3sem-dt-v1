/*
    Task: Коммивояжер - метод полного перебора
    готово
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>

// получение данных
void get_data(std::string, std::vector <std::vector<int>>&);
// печать обычной матрицы
void print_matrix(std::vector <std::vector<int>>&);

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

int main()
{
// --- Ввод матриц из файла
    std::string file[] {"5.2.1.matrix_1.txt"};
    int file_number_one = 0;
    std::vector <std::vector<int>> matrix {};
    get_data(file[file_number_one], matrix);
    print_matrix(matrix);
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

    std::set<int> cities_numbers_set {};
    Stack <int> cities_stack = Stack<int>(10);

    for(int i = 0; i < cities.size(); i++)
    {
        cities_stack.pushStack(cities[i]);
    }

// цикл while
    int upper_element {};
    bool check;
    long int sum_etalon {0};
    std::vector <std::vector <int>> short_ways {};
    int short_way_count {0};
    
    // первая сумма
    std::vector <int> all_s {};
    cities_stack.getAllStack(all_s);
    int ii, jj;
    for(int i = 0; i < all_s.size()-1; i++)
    {
        ii = all_s[i];
        jj = all_s[i+1];
        sum_etalon += matrix[ii-1][jj-1];
    }
    short_ways.push_back(std::vector<int>());
        for(int i = 0; i < all_s.size(); i++)
            short_ways.back().push_back(all_s[i]);

    while(true)
    {
// работа со стеком и множеством
        upper_element = 0;
        check = cities_stack.popStack(upper_element);
        if(check == 1)
        {
            std::cout << "Стек пуст после прохода" << std::endl;
            break;
        }

        cities_numbers_set.insert(upper_element);

        int j {0};
        int diff {*cities_numbers_set.rbegin()};
        int set_index {0};
        int set_element {0};
        for (int n : cities_numbers_set)
        {
            j++;
            if( (n - upper_element > 0) && (n - upper_element < diff) && (n != upper_element))
            {
                diff = n - upper_element;
                set_index = j;
                set_element = n;
            }
        }

        for (int n : cities_numbers_set)
            std::cout << n << " ";
        std::cout << std::endl;

        if(set_index == 0) continue;

        cities_stack.pushStack(set_element);
        cities_numbers_set.erase(set_element);

        for (int n : cities_numbers_set)
        {
            cities_stack.pushStack(n);
        }
        cities_numbers_set.clear();

        std::vector <int> all_stack {};
        cities_stack.getAllStack(all_stack);
        for(int i = 0; i < all_stack.size(); i++)
        {
            std::cout << all_stack[i] << " ";
        }
        std::cout << std::endl;
// --- end работа со стеком и множеством

// расчет минимального пути и суммы
        std::vector <int> all_s {};
        cities_stack.getAllStack(all_s);
        // if(all_s.empty()) break;
        int ii, jj;
        long int sum {0};
        for(int i = 0; i < all_s.size()-1; i++)
        {
            ii = all_s[i];
            jj = all_s[i+1];
            sum += matrix[ii-1][jj-1];
        }

        if(sum <= sum_etalon)
        {
            if(sum == sum_etalon) short_way_count++;
            if(sum < sum_etalon) short_ways = {};
            short_ways.push_back(std::vector<int>());
            for(int i = 0; i < all_s.size(); i++)
                short_ways.back().push_back(all_s[i]);
            sum_etalon = sum;
        }
// --- end расчет минимального пути и суммы
    }

// печать
    std::cout << std::endl;
    std::cout << "Результат:" << std::endl;
    std::cout << "Путь: "<< "\t";
    for(int i = 0; i < short_ways.size(); i++)
    {
        for(int j = 0; j < short_ways.back().size(); j++)
            std::cout << short_ways[i][j] << " ";
        std::cout << std::endl << "\t";
    }
    std::cout << std::endl;
    std::cout << "Сумма: ";
    std::cout << sum_etalon << std::endl;
    std::cout << "Количество путей: ";
    std::cout << short_way_count << std::endl;
// --- end печать

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
void print_matrix(std::vector <std::vector<int>>& matrix)
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