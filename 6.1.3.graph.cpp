/*
    Task: обход графа в виде дерева через матрицу смежности (поиск в глубину)
    шаблон класса
    проверка перед добавлением элемента в очереди/стеке и списке посещенных вершин
    готово
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

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

// получение данных
void get_data(std::string, std::vector <std::vector<int>>&);
// печать обычной матрицы
void print_matrix(std::vector <std::vector<int>>&);

int main()
{
    std::string file[] {"6.1.1.matrix_1.txt"};
    int file_number_one = 0;
    std::vector <std::vector<int>> matrix {};
    get_data(file[file_number_one], matrix);
    // print_matrix(matrix);

    std::string simbols {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    std::vector <std::string> row_s {};
    std::vector <std::string> column_s {};

    for(int i = 0; i< matrix.size(); i++)
        row_s.push_back(simbols.substr(i, 1));
    for(int i = 0; i< matrix.back().size(); i++)
        column_s.push_back(simbols.substr(i, 1));
    
    // for(int i = 0; i< row_s.size(); i++)
    //     std::cout << row_s[i] << " ";
    // std::cout << std::endl;
    // for(int i = 0; i< column_s.size(); i++)
    //     std::cout << column_s[i] << " ";
    // std::cout << std::endl;
    
    Stack <std::string> stack_vertex {50};
    std::vector <std::string> visited_vertex {};
    std::string input_vertex {};
    
    for(;;)
    {
        int br {0};
        std::cout << "Введите заглавную букву с какой читаем" <<std::endl;
        std::cin >> input_vertex;
        for(int i = 0; i < row_s.size(); i++)
        {
            if(row_s[i] == input_vertex)
            {
                br = 1;
                break;
            }
        }
        if(br == 1) 
        {
            std::cout << std::endl;
            break;
        }
        
    }
    stack_vertex.pushStack(input_vertex);

    std::string upperElement {};
    bool check {0};
    int r {0};
    int col {0};
    while(true)
    {
        upperElement = {};
        check = stack_vertex.popStack(upperElement);
        if(check == 1)
        {
            std::cout << "Стек пуст" << std::endl;
            break;
        }

        // расчет
        r = 0;
        for(int i = 0; i < row_s.size(); i++)
        {
            if(row_s[i] == upperElement) r = i;
        }

        col = 0;
        bool check_element {0};
        for(int j = matrix.back().size(); j >=r; j--)
        {
            if(matrix[r][j] == 1)
            {
                col = j;

                // проверка элемента в списке посещенных
                for(int i = 0; i< visited_vertex.size(); i++)
                {
                    if(visited_vertex[i] == row_s[col])
                    {
                        check_element = 1;
                        break;
                    }
                }
                if(check_element == 1) break;
                // проверка элемента в стеке
                std::vector<std::string> all_stack {};
                stack_vertex.getAllStack(all_stack);
                for(int i = 0; i< all_stack.size(); i++)
                {
                    if(all_stack[i] == row_s[col])
                    {
                        check_element = 1;
                        break;
                    }
                }
                if(check_element == 1) break;

                bool check_stack;
                check_stack = stack_vertex.pushStack(row_s[col]);
                if(check_stack == 1)
                {
                    std::cout << "Стек полон" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            
        }
        // if(check_element == 1) continue;

        visited_vertex.push_back(upperElement);
        
        // печать вытянутого элемента
        std::cout << "Элемент: " << upperElement << std::endl;

        // печать списка посещенных вершин
        std::cout << "Посещенные вершины: " ;
        for(int i = 0; i< visited_vertex.size(); i++)
        {
            std::cout <<  visited_vertex[i] << " ";
        }
        std::cout << std::endl;

        // печать стека на каждом шаге
        std::vector<std::string> all_stack {};
        stack_vertex.getAllStack(all_stack);
        std::cout << "Стек: " ;
        for(int i = 0; i< all_stack.size(); i++)
        {
            std::cout << all_stack[i] << " ";
        }
        std::cout << std::endl << std::endl;
    }

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