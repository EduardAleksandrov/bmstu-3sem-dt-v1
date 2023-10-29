/*
    Task: обход графа в виде дерева с указателями (поиск в ширину)
    добавлена очередь
    готово
    fix queue
*/
#include <iostream>
#include <string>
#include <vector>

struct Vertex
{
    std::string element;
    Vertex* left;
    Vertex* right;
};
template <typename T>
class Queue
{
private:
    T *fpos, *lpos, *startPos, *endPosition;
    int queue_size;
    bool addLastElement; //проверка, менялся ли последний элемент, 1-менялся, 0-не менялся
    bool exclude; //заменять последнее значения только один раз когда очередь не полна
public:
    Queue(int q_size): queue_size{q_size}
    {
        if(q_size <= 0)
        {
            std::cout << "Очередь не может быть меньше нуля" << std::endl;
            exit(EXIT_FAILURE);
        }

        try
        {
            startPos = new T[queue_size];
        }
        catch(const std::bad_alloc& e)
        {
            std::cerr << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }

        endPosition = startPos + queue_size - 1;
        fpos = startPos;
        lpos = startPos;

        // for(int i = 0; i < endPosition-startPos+1; i++)
        //     *(startPos+i) = 0;
        
        addLastElement = exclude = 0;
    }
    ~Queue()
    {
        delete [] startPos;
        startPos = nullptr;
    }
    bool addElementToQueue(T value)
    {

        // if((lpos != endPosition) && (startPos != fpos)) exclude = 0;
        // if(lpos+1 != fpos) addLastElement = 0;

        if((lpos == endPosition) && (startPos != fpos))
        {
            lpos = startPos;
            if(addLastElement == 0)
            {
                *endPosition = value;
            }
            addLastElement = 0;
        } else if((lpos == endPosition) && (startPos == fpos))
        {
            if(addLastElement == 0) 
            {
                *lpos = value;
                addLastElement = 1;
            }
                
            // std::cout << "Очередь полна" << std::endl;
            return 1;
        } else if(lpos+1 == fpos)
        {
            if(addLastElement == 0)
            {
                *lpos = value;
                addLastElement = 1;
            }
            // std::cout << "Очередь полна" << std::endl;
            return 1;
        } else {
            lpos++;
            *(lpos - 1) = value;
        }
        return 0;
    }
    void printQueue()
    {
        for(int i = 0; i<endPosition-startPos+1; i++)
        {
            std::cout << *(startPos+i) << " ";
        }
        std::cout << std::endl;
        int x = fpos - startPos;
        int y = lpos - startPos;
        std::cout << "fpos=" << *fpos << ", индекс=" << x << std::endl;
        std::cout << "lpos=" << *lpos << ", индекс=" << y << std::endl;
        std::cout << std::endl;
    }
    bool deleteElementFromQueue(T& dropedValue)
    {
        if(lpos == fpos)
        {
            // std::cout << "Очередь пуста" << std::endl;
            return 1;
        }
        T dropedElement = *fpos;
        // *fpos = 0;

        // if(lpos+1 != fpos) addLastElement = 0;

        if((lpos == endPosition) && (startPos == fpos) && (addLastElement == 1))
        {
            lpos = startPos;
            addLastElement = 0;
        } else if((lpos+1 == fpos)) 
        {
            if(addLastElement == 1) // указатель не проедет дальше при следующем удалении, останется на месте
            {
                lpos++;
                addLastElement = 0;
            }
            
        }

        if(endPosition == fpos)
        {
            fpos = startPos;
        } else {
            fpos++;
        }
        dropedValue = dropedElement;
        return 0;
    }
    void getAllQueue(std::vector<T>& all_queue)
    {
        if(fpos<lpos)
        {
            if(fpos == startPos && lpos == endPosition)
            {
                if(addLastElement == 1)
                {
                    for(int i = 0; i<lpos-fpos+1; i++)
                    {
                        all_queue.push_back(*(fpos+i));
                    }
                } else {
                    for(int i = 0; i<lpos-fpos; i++)
                    {
                        all_queue.push_back(*(fpos+i));
                    }
                }
            } else {
                for(int i = 0; i<lpos-fpos; i++)
                {
                    all_queue.push_back(*(fpos+i));
                }
            }
            
        }
        if(fpos>lpos)
        {
            if(lpos+1 == fpos)
            {
                for(int i = 0; i<endPosition-fpos+1; i++)
                    all_queue.push_back(*(fpos+i));
                if(addLastElement == 1)
                {
                    for(int i = 0; i<lpos - startPos+1; i++)
                        all_queue.push_back(*(startPos+i));
                } else {
                    for(int i = 0; i<lpos - startPos; i++)
                        all_queue.push_back(*(startPos+i));
                }
                
            } else {
                for(int i = 0; i<endPosition-fpos+1; i++)
                    all_queue.push_back(*(fpos+i));
                for(int i = 0; i<lpos - startPos; i++)
                    all_queue.push_back(*(startPos+i));
            }
            
        }
    }

};

int main()
{
    Vertex *vertex_set;
    int vertex_set_size {14};
    try
    {
        vertex_set = new Vertex[vertex_set_size];
    }
    catch(const std::bad_alloc& e)
    {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    

    vertex_set[0].element = {"A"};
    vertex_set[0].left = &vertex_set[1];
    vertex_set[0].right = &vertex_set[2];

    vertex_set[1].element = {"B"};
    vertex_set[1].left = &vertex_set[3];
    vertex_set[1].right = &vertex_set[4];

    vertex_set[2].element = {"C"};
    vertex_set[2].left = &vertex_set[5];
    vertex_set[2].right = &vertex_set[6];

    vertex_set[3].element = {"D"};
    vertex_set[3].left = &vertex_set[7];
    vertex_set[3].right = &vertex_set[8];

    vertex_set[4].element = {"E"};
    vertex_set[4].left = &vertex_set[9];
    vertex_set[4].right = nullptr;

    vertex_set[5].element = {"F"};
    vertex_set[5].left = &vertex_set[10];
    vertex_set[5].right = nullptr;

    vertex_set[6].element = {"G"};
    vertex_set[6].left = &vertex_set[11];
    vertex_set[6].right = &vertex_set[12];

    vertex_set[7].element = {"H"};
    vertex_set[7].left = nullptr;
    vertex_set[7].right = nullptr;

    vertex_set[8].element = {"I"};
    vertex_set[8].left = nullptr;
    vertex_set[8].right = nullptr;

    vertex_set[9].element = {"J"};
    vertex_set[9].left = nullptr;
    vertex_set[9].right = nullptr;

    vertex_set[10].element = {"K"};
    vertex_set[10].left = nullptr;
    vertex_set[10].right = nullptr;

    vertex_set[11].element = {"L"};
    vertex_set[11].left = nullptr;
    vertex_set[11].right = nullptr;

    vertex_set[12].element = {"M"};
    vertex_set[12].left = &vertex_set[13];
    vertex_set[12].right = nullptr;

    vertex_set[13].element = {"N"};
    vertex_set[13].left = nullptr;
    vertex_set[13].right = nullptr;

    Queue <Vertex> queue_vertex {50};
    std::vector <std::string> visited_vertex {};
    bool check;

    std::string input_vertex {};
    int v_number {0};
    for(;;)
    {
        int br {0};
        std::cout << "Введите заглавную букву с какой читаем" <<std::endl;
        std::cin >> input_vertex;
        for(int i = 0; i < vertex_set_size; i++)
        {
            if(vertex_set[i].element == input_vertex)
            {
                v_number = i;
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
    queue_vertex.addElementToQueue(vertex_set[v_number]);

    while(true)
    {
        // печать очереди на каждом шаге
        std::vector <Vertex> data_from_queue {};
        queue_vertex.getAllQueue(data_from_queue);
        for(int i = 0; i < data_from_queue.size(); i++)
            std::cout << data_from_queue[i].element << " ";
        std::cout << std::endl;

        // получение верхнего элемента
        Vertex dropedValue;
        check = queue_vertex.deleteElementFromQueue(dropedValue);
        if(check == 1)
        {
            std::cout << "Очередь пуста" << std::endl;
            break;
        }
        std::cout << dropedValue.element << std::endl;

        // заносим значение дочерних в очередь
        if(dropedValue.left != nullptr)
        {
            bool check_add {0};
            check_add = queue_vertex.addElementToQueue(*dropedValue.left);
            if(check_add == 1)
            {
                std::cout << "Очередь полна" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        if(dropedValue.right != nullptr)
        {
            bool check_add {0};
            check_add = queue_vertex.addElementToQueue(*dropedValue.right);
            if(check_add == 1)
            {
                std::cout << "Очередь полна" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        visited_vertex.push_back(dropedValue.element);

    }
    // печать списка посещенных вершин
    for(int i = 0; i < visited_vertex.size(); i++)
        std::cout << visited_vertex[i] << " ";
    std::cout << std::endl;
    

    delete [] vertex_set;
    vertex_set = nullptr;

    return 0;
}