//
// Created by kusha on 11/29/2019.
//

#ifndef PLAGARISM_CATCHER_HASHTABLE_H
#define PLAGARISM_CATCHER_HASHTABLE_H

#include <vector>
#include <cstdlib>
#include <string>
class HashTable {
public:
    HashTable(int size);
    std::vector<int> insert(std::string &key, int data);
    std::vector<int> get(std::string &key);
    ~HashTable();

private:
    static long hashFunction(std::string &key);
    int size;

    std::vector<int> *table;
};


#endif //PLAGARISM_CATCHER_HASHTABLE_H
