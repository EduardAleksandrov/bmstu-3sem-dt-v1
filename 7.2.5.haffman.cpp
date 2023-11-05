/*
    Task: алгоритм сжатия текста по Хаффману
    получили из файла данные в таблицу
    собрали таблицу
    вычислили коды
    запись бинарных данных в файл и получение
*/
#include <iostream>
#include <bitset>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>



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

struct Binary_node
{
    wchar_t binary_node_label;
    std::vector <bool> binary_number;
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
        if(existence_flag == 0 && ch != L'\0' && ch != '\n' && ch != EOF)
        {
            table.push_back(Table_column());
            table[index_number].index = index_number+1;
            table[index_number].node_label = ch;
            table[index_number].node_weight = 1;
            table[index_number].union_flag = 1;
            table[index_number].left_index= -1;
            table[index_number].right_index= -1;
            index_number++;
        }
    }
    std::wcout << std::endl;
    // table.pop_back();
    fr.close();

    int32_t num_unique_element = table.size(); // количество уникальных элементов
// --- end Считываем из файла и заполняем таблицу

    for(int i = 0; i < table.size(); i++)
        std::wcout << table[i].index << " " << table[i].node_label << " " << table[i].node_weight << " " << table[i].union_flag << std::endl;
    std::wcout << num_unique_element << std::endl;

// собрали таблицу
    get_full_table(table);

    for(int i = 0; i < table.size(); i++)
        std::wcout << table[i].index << " " << table[i].node_label << " " << table[i].node_weight << " " << table[i].union_flag << " " << table[i].left_index << " " << table[i].right_index << std::endl;
// --- end собрали таблицу



// вычислили коды для каждого элемента
    std::vector <Binary_node> binary_node_table {};

    for(int i = 0; i<num_unique_element; i++)
    {
        binary_node_table.push_back(Binary_node());
        binary_node_table[i].binary_node_label = table[i].node_label;
        int32_t t_ind = table[i].index;

        while(true)
        {
            
            for(int j = num_unique_element; j<table.size(); j++)
            {
                if(t_ind == table[j].left_index)
                {
                    binary_node_table[i].binary_number.push_back(0);
                    t_ind = table[j].index;
                    break;
                }
                if(t_ind == table[j].right_index)
                {
                    binary_node_table[i].binary_number.push_back(1);
                    t_ind = table[j].index;
                    break;
                }
            }
            if(t_ind == table[table.size()-1].index)
            {
                break;
            }
        }
        std::reverse(binary_node_table[i].binary_number.begin(), binary_node_table[i].binary_number.end());
    }

    for(int i = 0; i < binary_node_table.size(); i++)
    {
        std::wcout << binary_node_table[i].binary_node_label << " ";
        for(int j=0;j < binary_node_table[i].binary_number.size(); j++)
        {
            std::wcout << binary_node_table[i].binary_number[j];
        }
        std::wcout << std::endl;
    }
// --- end вычислили коды для каждого элемента

// запись битов данных в бинарный файл
    std::bitset<8> bits(0);
    // bits.set(0);

    wchar_t chh;
    std::wfstream frr("7.2.1.string.txt", std::wios::in);
    if(!frr) {
        std::wcout << "Cannot open file!" << std::endl;
        return 1;
    }
    frr.imbue(std::locale(""));

    std::fstream wf("7.2.4.bits.dat", std::ios::out | std::ios::binary);
    if(!wf) {
        std::wcout << "Cannot open file!" << std::endl;
        return 1;
    }

    int32_t k {7}; // счетчик битов
    int br = 0;
    int segment_two {0};
    while(frr)
    {
        ch = frr.get();
        for(int i = 0; i <binary_node_table.size(); i++)
        {   
            if(binary_node_table[i].binary_node_label == ch)
            {
                for(int j = 0; j<binary_node_table[i].binary_number.size(); j++)
                {
                    bits[k--] = binary_node_table[i].binary_number[j];
                    segment_two++;
                    if(k < 0)
                    {
                        k = 7;
                        wf.write(reinterpret_cast<char*>(&bits), 1);
                        br++;
                        segment_two = 0;
                    }
                }
            // if(br == 3) break;
            }
        }
        // if(br == 3) break;
    }
    wf.write(reinterpret_cast<char*>(&bits), 1);
    wf.close();
    frr.close();


    // чтение бинарных
    Binary_node tmp;
    int kk {7};

    std::fstream wff("7.2.4.bits.dat", std::ios::in | std::ios::binary);
    if(!wff) {
        std::wcout << "Cannot open file!" << std::endl;
        return 1;
    }
    std::bitset<8> upper_read(0);
    while(wff.read((char *) &upper_read, 1))
    // for(int i = 0; i < 9; i++)
    {
        // wff.read((char *) &upper_read, 1);
        // if(upper_read == EOF) break;
        for(int i = 0; i < 8 ; i++)
        {
            tmp.binary_number.push_back(upper_read[kk--]);
            if(kk < 0) kk = 7;
        }
    }
    wff.close();

    for(int j=0;j < tmp.binary_number.size(); j++)
    {
        std::wcout << tmp.binary_number[j];
    }
    std::wcout << std::endl;

    std::wcout << segment_two << " "<< br<< std::endl;



// --- end запись данных в бинарный файл










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










