/*
    Task: алгоритм сжатия текста по Хаффману
    получили из файла данные в таблицу
*/
#include <iostream>
#include <bitset>
#include <string>
#include <fstream>
#include <vector>


// #include <locale>

struct Table_column
{
    int32_t index;
    wchar_t node_label;
    int32_t node_weight;
    int32_t left_index;
    int32_t right_index;
    bool union_flag;
    Table_column(){}
};

int main()
{
    setlocale(LC_ALL, "");

    std::vector <Table_column> table {};
    
    // Считываем из файла и заполняем таблицу
    wchar_t ch;
    std::wfstream fr("7.2.1.string.txt", std::wios::in);
    if(!fr) {
        std::wcout << "Cannot open file!" << std::endl;
        return 1;
    }
    fr.imbue(std::locale(""));
    int32_t index_number {0};
    while(fr)
    {
        ch = fr.get();
        std::wcout << ch << " ";

        bool existence_flag = 0;
        for(int i = 0; i < table.size(); i++)
        {
            if(ch == table[i].node_label)
            {
                table[i].node_weight++;
                existence_flag = 1;
                break;
            }
        }
        if(existence_flag == 0 && ch != L'\0' && ch != '\n')
        {
            table.push_back(Table_column());
            table[index_number].index = index_number+1;
            table[index_number].node_label = ch;
            table[index_number].node_weight = 1;
            table[index_number].union_flag = 1;
            index_number++;
        }
    }
    std::wcout << std::endl;
    table.pop_back();
    fr.close();
    // --- end Считываем из файла и заполняем таблицу


    for(int i = 0; i < table.size(); i++)
        std::wcout << table[i].index << " " << table[i].node_label << " " << table[i].node_weight << " " << table[i].union_flag << std::endl;

    return 0;
}