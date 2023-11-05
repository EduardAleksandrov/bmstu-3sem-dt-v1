/*
    Task: алгоритм сжатия текста по Хаффману
    получили из файла данные в таблицу
    собрали таблицу
*/
#include <iostream>
#include <bitset>
#include <string>
#include <fstream>
#include <vector>


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


void get_full_table(std::vector <Table_column>&);

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
    int32_t num_unique_element = table.size();
// --- end Считываем из файла и заполняем таблицу

    for(int i = 0; i < table.size(); i++)
        std::wcout << table[i].index << " " << table[i].node_label << " " << table[i].node_weight << " " << table[i].union_flag << std::endl;
    std::wcout << num_unique_element << std::endl;

/*
    in Table_column:
                    index;
                    node_label;
                    node_weight;
                    union_flag;
    out Table_column:
                    node_weight;
                    left_index;
                    right_index;
                    union_flag;

*/
    // for(int z = 0; z < table.size(); z++)
    // {
    //     int ii {-1};
    //     int jj {-1};
    //     int32_t min_weight;
    //     int32_t max_weight {0};
    //     for(int i = 0; i < table.size(); i++)
    //     {
    //         max_weight += table[i].node_weight;
    //     }
    //     min_weight = max_weight;
    //     for(int i = 0; i < table.size()-1; i++)
    //     {
    //         for(int j = i+1; j < table.size(); j++)
    //         {
    //             if((table[i].node_weight + table[j].node_weight < min_weight) && (table[i].union_flag == 1) && (table[j].union_flag == 1))
    //             {
    //                 min_weight = table[i].node_weight + table[j].node_weight;
    //                 ii = i;
    //                 jj = j;
    //             }
    //         }
    //     }
    //     if(ii != -1 && jj != -1)
    //     {
    //         table[ii].union_flag = 0;
    //         table[jj].union_flag = 0;

    //         table.push_back(Table_column());
    //         table[table.size()-1].index = table.size();
    //         table[table.size()-1].node_weight = min_weight;
    //         table[table.size()-1].left_index = ii+1;
    //         table[table.size()-1].right_index = jj+1;
    //         table[table.size()-1].union_flag= 1;
    //     }
    // }
    
    get_full_table(table);




    for(int i = 0; i < table.size(); i++)
        std::wcout << table[i].index << " " << table[i].node_label << " " << table[i].node_weight << " " << table[i].union_flag << " " << table[i].left_index << " " << table[i].right_index << std::endl;


    return 0;
}

/*
    in Table_column:
                    index;
                    node_label;
                    node_weight;
                    union_flag;
    out Table_column:
                    node_weight;
                    left_index;
                    right_index;
                    union_flag;

*/
void get_full_table(std::vector <Table_column>& table)
{
    for(int z = 0; z < table.size(); z++)
    {
        int ii {-1};
        int jj {-1};
        int32_t min_weight;
        int32_t max_weight {0};
        for(int i = 0; i < table.size(); i++)
        {
            max_weight += table[i].node_weight;
        }
        min_weight = max_weight;
        for(int i = 0; i < table.size()-1; i++)
        {
            for(int j = i+1; j < table.size(); j++)
            {
                if((table[i].node_weight + table[j].node_weight < min_weight) && (table[i].union_flag == 1) && (table[j].union_flag == 1))
                {
                    min_weight = table[i].node_weight + table[j].node_weight;
                    ii = i;
                    jj = j;
                }
            }
        }
        if(ii != -1 && jj != -1)
        {
            table[ii].union_flag = 0;
            table[jj].union_flag = 0;

            table.push_back(Table_column());
            table[table.size()-1].index = table.size();
            table[table.size()-1].node_weight = min_weight;
            table[table.size()-1].left_index = ii+1;
            table[table.size()-1].right_index = jj+1;
            table[table.size()-1].union_flag= 1;
        }
    }
}










