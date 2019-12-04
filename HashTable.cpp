//
// Created by kusha on 11/29/2019.
//

#include "HashTable.h"
#include <climits>

using namespace std;
HashTable::HashTable(int size) {
    table=new vector<int>[size];
    this->size=size;
}
HashTable::~HashTable() {
    delete []table;
}
long HashTable::hashFunction(std::string &key) {
    unsigned long long temp=0;
    int i=0;

    for(const char &c:key){
        temp+=((c-'a'+1)*(37^i));
        temp%=LONG_MAX;
        i++;
    }

    return (long)temp;
}

std::vector<int> HashTable::insert(std::string &key, int data) {
    int index = (int) (hashFunction(key) % size);

    vector<int> collisions= table[index];
    table[index].push_back(data);

    return collisions;
}

std::vector<int> HashTable::get(std::string &key) {
    int index = (int) (hashFunction(key) % size);
    return table[index];
}






