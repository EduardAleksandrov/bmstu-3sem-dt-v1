/*
    Task: алгоритм сжатия текста по Хаффману
    получили из файла данные в таблицу
    собрали таблицу
    вычислили коды
    запись бинарных данных в файл и получение
    запись данных в файл и получение без второго сегмента
    второй сегмент добавлен
    запись в файл готова
    чтение символов для таблицы готово
    нужно распаковать бинарные данные - готово

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

// Запись в файл wchar

    std::wfstream in_file_wchar("7.2.5.bits.dat", std::wios::out | std::ios::binary);
    if(!in_file_wchar) {
        std::cout << "Cannot open file!" << std::endl;
        return 1;
    }
    in_file_wchar.imbue(std::locale(""));
    wchar_t vOut = (wchar_t)num_unique_element;
    // wchar_t vout = L'в';
    wchar_t vOut_t;
    in_file_wchar.write((wchar_t*)&vOut, (int)sizeof(wchar_t));
    // std::wcout << sizeof(vOut) << std::endl;
    for(int i = 0; i < num_unique_element; i++)
    {
        in_file_wchar.write(&table[i].node_label, 1);
        vOut_t = (wchar_t)table[i].node_weight;
        in_file_wchar.write(&vOut_t, (int)sizeof(wchar_t));
        // std::wcout << (int)sizeof(wchar_t) << " ";
    }
    in_file_wchar.close();

// --- end запись в файл wchar

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

    std::fstream wf("7.2.5.bits.dat", std::ios::app | std::ios::binary);
    if(!wf) {
        std::wcout << "Cannot open file!" << std::endl;
        return 1;
    } 

    //  запись нуля во второй сегмент
    int num_zero {0};
    char vOut_zero = (char)num_zero;
    int32_t file_seekp_pointer_set = in_file_wchar.tellg();
    // std::wcout << in_file_wchar.tellg() << " fwefw"<< "\n";
    wf.write(&vOut_zero, 1);
    // ---

    //запись битов
    int32_t k {7}; // счетчик битов
    int br = 0;
    int32_t segment_two {0};
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
    // ---

    wf.seekp(file_seekp_pointer_set, std::ios::beg);
    char segment_two_t = (char)segment_two;
    wf.write(&segment_two_t, 1);

    wf.close();
    frr.close();

// --- end запись данных в бинарный файл





// получение wchar из файла
    std::vector <Table_column> new_table {};
    std::wfstream out_file_wchar("7.2.5.bits.dat", std::wios::in | std::ios::binary);
    if(!out_file_wchar) {
        std::cout << "Cannot open file!" << std::endl;
        return 1;
    }
    out_file_wchar.imbue(std::locale(""));
    
    wchar_t first_element;
    out_file_wchar.read(&first_element, (int)sizeof(wchar_t));
    int first_element_int = (int)first_element;

    int ind {1};
    for(int i = 0; i<first_element_int; i++)
    {
        new_table.push_back(Table_column());
        out_file_wchar.read(&new_table[i].node_label, 1);
        wchar_t w;
        out_file_wchar.read(&w, (int)sizeof(wchar_t));
        int w_int = (int)w;
        new_table[i].node_weight = w_int;
        new_table[i].index = ind++;
        new_table[i].union_flag = 1;
        new_table[i].left_index= -1;
        new_table[i].right_index= -1;
    }

    int32_t file_seekp_pointer_get = out_file_wchar.tellg();
    // std::wcout << out_file_wchar.tellg() <<"\n";
    out_file_wchar.close();

    std::wcout << std::endl;
    
    // собрали таблицу
    get_full_table(new_table);

    for(int i = 0; i < table.size(); i++)
        std::wcout << new_table[i].index << " " << new_table[i].node_label << " " << new_table[i].node_weight << " " << new_table[i].union_flag << " " << new_table[i].left_index << " " << new_table[i].right_index << std::endl;
    // --- end собрали таблицу
// ---



// чтение бинарных данных
    Binary_node tmp;
    int kk {7};

    // считывание первого элемента из файла
    wchar_t first_el;
    std::wfstream f_read("7.2.5.bits.dat", std::wios::in | std::wios::binary);
    if(!f_read) {
        std::wcout << "Cannot open file!" << std::endl;
        return 1;
    }
    f_read.seekp(0);
    f_read.read(&first_el, 1);
    f_read.close();
    int first_el_int = (int)first_el;
    // std::wcout << first_el_int << std::endl;
    /// ---

    // подсчет байтов из битов
    std::fstream wff_bits("7.2.5.bits.dat", std::ios::in | std::ios::binary);
    if(!wff_bits) {
        std::wcout << "Cannot open file!" << std::endl;
        return 1;
    }
    wff_bits.seekp(file_seekp_pointer_get, std::ios::beg);
    int32_t num_of_bites{0};
    char count_bites;

    while(wff_bits.read((char *) &count_bites, 1))
    {
        num_of_bites++;
    }
    wff_bits.close();
    num_of_bites--; // первый байт - количество бит в последнем байте
    std::wcout<<L"Количество байт в бит коде: "<<num_of_bites<<"\n";
    // --- end подсчет байтов из битов

    std::fstream wff("7.2.5.bits.dat", std::ios::in | std::ios::binary);
    if(!wff) {
        std::wcout << "Cannot open file!" << std::endl;
        return 1;
    }
    std::bitset<8> upper_read(0);
    wff.seekp(file_seekp_pointer_get, std::ios::beg);

    //получение второго сегмента
    char upper_read_seg_two;
    wff.read((char *) &upper_read_seg_two, 1);
    int segment_two_tt = (int)segment_two;
    std::wcout <<L"Количество бит в последнем байте:";
    std::wcout << segment_two_tt << std::endl;
    //---

    int32_t count_of_bites{0};
    int num_of_bits_in_bite {0};
    int32_t ind_bite = new_table[new_table.size()-1].index;
    // std::wcout << ind_bite << "\n";
    while(wff.read((char *) &upper_read, 1))
    {
        tmp.binary_number.clear();
        count_of_bites++;
        if(count_of_bites == num_of_bites)
        {
            num_of_bits_in_bite = segment_two_tt;
        } else {
            num_of_bits_in_bite = 8;
        }
        for(int i = 0; i < num_of_bits_in_bite ; i++)
        {
            tmp.binary_number.push_back(upper_read[kk--]);
            if(kk < 0) kk = 7;
        }
        // for(int j=0;j < tmp.binary_number.size(); j++)
        // {
        //     std::wcout << tmp.binary_number[j];
        // }
        // std::wcout << std::endl;
        
        // вычисление символов из байт кода и печать их
        for(int i = 0; i < tmp.binary_number.size(); i++)
        {
            if(tmp.binary_number[i] == 0)
            {
                ind_bite = new_table[ind_bite-1].left_index;
            }
            if(tmp.binary_number[i] == 1)
            {
                ind_bite = new_table[ind_bite-1].right_index;
            }
            if(ind_bite>=1 && ind_bite<=first_element_int)
            {
                std::wcout << new_table[ind_bite-1].node_label;
                ind_bite = new_table[new_table.size()-1].index;
            }
        }
    }
    wff.close();
    std::wcout << std::endl;

    // for(int j=0;j < tmp.binary_number.size(); j++)
    // {
    //     std::wcout << tmp.binary_number[j];
    // }
    // std::wcout << std::endl;

    // std::wcout << segment_two << " "<< br<< std::endl;

// --- end чтение бинарных данных



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










