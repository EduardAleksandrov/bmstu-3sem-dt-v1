/*
    Task: Реализация бинарного поиска
    тест1
    добавлен тест2 - работает
    второй вариант поиска - работает
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int search(vector <int>&, int, int&);
void test(int, int, vector <int>&);
bool test_two(int, int, vector <int>&);


int main()
{
    
    vector <int> mass_one {-3,1,2,3,4,8,12,14};
    vector <int> mass_two {};
    vector <int> mass_three {-3};
    vector <int> mass_four {-3,4};
    vector <int> mass_five {0,1,3,5,7,9,11};
    vector <int> mass_six {0,1,3,5,7,9,11,12};
    vector <int> mass_seven {2,4,6,8,10,12,14,16,18,20,22,24,26,28};

    int search_elem {3};

    int steps {0};
    int result {-1};
    result = search(mass_one, search_elem, steps);
    if(result == -1) cout << "Элемент не найден" << endl;
    else cout << "Индекс равен: " << result << ", шагов: " << steps << endl;
    
// test 1
    // test(-5, 18, mass_one);
// test 2
    // int ids_size = 7;
    vector <int>* ids[] = {&mass_one, &mass_two, &mass_three, &mass_four, &mass_five, &mass_six, &mass_seven};
    for(int i = 0; i < std::size(ids); i++)
    {
        int res {-1};
        res = test_two(-5, 30, *ids[i]);
        if(res == 0) cout << "Тест пройден" << endl;
        else cout << "Тест не пройден" << endl;
    }
    

    return 0;
}

void test(int fv, int lv, vector <int>& mass)
{
    int result {-1};
    int steps {0};
    for(int i = fv; i <=lv; i++)
    {
        result = search(mass, i, steps);

        cout << "i = "<< i << ", индекс = ";
        if(result == -1) cout << "не найден" << endl;
        else cout << result << ", шагов = " << steps << endl;
    }
    
}
bool test_two(int fv, int lv, vector <int>& mass)
{
    int result {-1};
    int res_num {0};
    int steps {0};
    for(int i = fv; i <=lv; i++)
    {
        result = search(mass, i, steps);
        if(result != -1) res_num++;
    }
    if(res_num == mass.size()) return 0;
    return 1;
    
}

int search(vector <int>& mass, int search_elem, int& steps)
{
    if(mass.size() == 0) return -1;
    int L {0};
    int size = mass.size()-1;
    int R {size};
    steps = 0;
    
    int mid_ind {0};
    while(L <= R)
    {
        steps++;
        mid_ind = (L + R) / 2;
        if(search_elem < mass[mid_ind]) R = mid_ind - 1;
        else if(search_elem > mass[mid_ind]) L = mid_ind + 1;
        else return mid_ind;
    }
    return -1;
}

