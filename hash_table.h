
#ifndef HASHTABLE_H
#define HASHTABLE_H





#include <iostream>
#include "cache_list.h"
#include <string>
#include <functional>
#include <cstring>
#include <vector>
#include <memory>
#include <ctime>
#include <nmmintrin.h>

const unsigned long long Max_val = 18446744073709551615U;
const int NumTimes = 200;




typedef unsigned int hash_t;
typedef std::function<hash_t (const unsigned char*, unsigned long)> hash_func_t;

template <typename Tp>
class HashTable {
    static hash_t default_hash (const unsigned char* string, unsigned long len);
    size_t size;
    hash_func_t hash;
public:
    std::unique_ptr<list<std::pair<const char*, Tp >>[]> table;

    explicit HashTable (size_t size, const hash_func_t& hash_func = HashTable::default_hash) :
            size (size), table (new list<std::pair<const char*, Tp >> [size]), hash (hash_func) {}

    void SizesOfListsInTable (FILE* f_out);

    void LoadTambleFromVec (std::vector<char*> &vec);

    void insert (const char* str, Tp value);

    std::pair<const char*, Tp>* find (const char* key) const;
};

void cleaning_text (FILE* f_in, unsigned long long FileSize);

unsigned long long int SizeOfFile (const char* NameOfFile);

void GetWords (std::vector<char*>& words, char* buf);

hash_t CRC_32_fast (const unsigned char* string, unsigned long len);

void print_time_of_search (const HashTable<char*>& table, const std::vector<char*>& words, const char* massege);



void GetWords (std::vector<char*>& words, char* buf) {
    char* buf_p = buf;
    char* temp_str = buf;
    while (*buf_p != '\0') {
        if (*buf_p == ' ') {
            *buf_p = '\0';
            words.push_back (temp_str);
            temp_str = buf_p + 1;
        }
        ++buf_p;
    }
}

template <typename Tp>
std::pair<const char*, Tp>* HashTable<Tp>::find (const char* key) const {
    unsigned int pos = hash ((const unsigned char*) key, strlen (key)) % size;
    for (auto it = table[pos].begin (); it !=  table[pos].end (); ++it) {
        if (strcmp (key, (*it).first) == 0) {
            return &*it;
        }
    }
    return nullptr;
}

template <typename Tp>
void HashTable<Tp>::SizesOfListsInTable (FILE* f_out) {

    for (int i = 0; i < size; ++i) {
        fprintf (f_out, "%ld,", table[i].list_size ());
    }
    fprintf (f_out, "\n");
}

template <typename Tp>
void HashTable<Tp>::LoadTambleFromVec (std::vector<char*> &vec) {
    for (auto c : vec) {
        insert (c, c);
    }
}

template <typename Tp>
void HashTable<Tp>::insert (const char* str, Tp value) {
    unsigned long long index = (hash (reinterpret_cast<const unsigned char*> (str), strlen (str)) % size);
    for (auto c : table[index]) {
        if (strcmp (str, c.first) == 0) {
            return;
        }
    }
    table[index].PushBack ({str, value});
}


unsigned long long int SizeOfFile (const char* NameOfFile) {
    assert (NameOfFile != nullptr);

    FILE* f = fopen (NameOfFile, "r");
    fseek (f, 0, SEEK_END);
    unsigned long long FileSize = ftell (f);
    fseek (f, 0, SEEK_SET);

    fclose (f);
    return FileSize;
}

void cleaning_text (FILE* f_in, unsigned long long FileSize) {
    char* buf = new char[FileSize];
    char* new_buf = new char[FileSize];
    fread (buf, sizeof (char), FileSize, f_in);
    unsigned long long col = FileSize;
    char* new_buf_ptr = new_buf;
    char* buff = buf;
    while (col > 1) {
        if (*buf == ' ' || isalpha (*buf)) {
            *new_buf_ptr = *buf;
            ++new_buf_ptr;
        }
        ++buf;
        --col;
    }

    FILE* f_out = fopen ("output.txt", "w");
    fwrite (new_buf, sizeof (char), FileSize, f_out);
    delete[] (buff);
    delete[] (new_buf);
    fclose (f_out);
}

template <typename Tp>
hash_t HashTable<Tp>::default_hash (const unsigned char* string, unsigned long len)
{
    unsigned long crc_table[256];
    unsigned long crc;
    for (int i = 0; i < 256; i++)
    {
        crc = i;
        for (int j = 0; j < 8; j++) {
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
        }
        crc_table[i] = crc;
    }
    crc = 0xFFFFFFFFUL;
    while (len--) {
        crc = crc_table[(crc ^ *string++) & 0xFF] ^ (crc >> 8);
    }
    return crc ^ 0xFFFFFFFFUL;
}


void print_time_of_search (const HashTable<char*>& table, const std::vector<char*>& words, const char* massege) {
    clock_t time = clock();
    for (int i = 0; i < NumTimes; ++i) {
        for (auto el : words) {
            table.find (el);
        }
    }
    std::cout << massege << double (clock () - time) / CLOCKS_PER_SEC << std::endl;
    
}

hash_t CRC_32_fast (const unsigned char* string, unsigned long len) {
    hash_t hash = 0;
    if (len == 1) return _mm_crc32_u8  (hash, *string);
    if (len == 2) return _mm_crc32_u16 (hash, *(unsigned short*) string);
    unsigned int i = 0;
    while (len >= 4)
    {
        hash = _mm_crc32_u32 (hash, *(unsigned int*) (string + i));
        len -= 4;
        i += 4;
    }
    
    if (len >= 2) {
        hash = _mm_crc32_u16 (hash, *(unsigned short*) (string + i));
        len -= 2;
        i += 2;
    }

    if (len == 1) return _mm_crc32_u8  (hash, *string);

    return hash;
}

#endif // HASHTABLE_H