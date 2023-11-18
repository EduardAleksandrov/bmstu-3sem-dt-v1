/*
    Task: Реализация бинарного поиска
    тест - готово
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int search(vector <int>&, int);
void test(int, int, vector <int>&);


int main()
{
    
    vector <int> mass_one {-3,1,2,3,4,8,12,14};
    vector <int> mass_two {-3};

    int search_elem {-3};

    // int result {-1};
    // result = search(mass_two, search_elem);
    // if(result == -1) cout << "Элемент не найден" << endl;
    // else cout << "Индекс равен: " << result << endl;
    

    test(-5, 18, mass_one);

    return 0;
}

void test(int fv, int lv, vector <int>& mass)
{
    int result {-1};
    for(int i = fv; i <=lv; i++)
    {
        result = search(mass, i);

        cout << "i = "<< i << ", индекс = ";
        if(result == -1) cout << "не найден" << endl;
        else cout << result << endl;
    }
    
}

int search(vector <int>& mass, int search_elem)
{
    if(mass.size() == 0) return -1;
    int index {0};
    int L {0};
    int size = mass.size()-1;
    int R {size};
    
    int mid_ind{0};
    // int num = 0;
    while(true)
    {
        mid_ind = round((R-L+1)/2.0) - 1;
        if(mid_ind < 0) mid_ind = 0;
        // cout << L << " "<< R <<  " " << mid_ind << " " <<mass[L+mid_ind] << "\n";

        if(mass[L+mid_ind] == search_elem)
        {
            index = L+mid_ind;
            break;
        } else if(mass[L+mid_ind]<search_elem) 
        {
            L += mid_ind;
        } else if(mass[L+mid_ind]>search_elem) 
        {
            R -= mid_ind;
        }

        if(L==R)
        {
            if(mass[L] == search_elem)
            {
                index = L;
                break;
            }
            index = -1;
            break;
        }
        if(R-L == 1)
        {
            if(mass[L] == search_elem)
            {
                index = L;
                break;
            }else if(mass[R] == search_elem)
            {
                index = R;
                break;
            } else {
                index = -1;
                break;
            }
        }
        // if(num++ == 5) break;
    }
    return index;
}

