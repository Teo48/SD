// Copyright Teodor Matei 313 CA - 2019
#include <list>
#include <iterator>
#include <string>
#include "./Hashtable.h"

template <typename Tkey, typename Tvalue>
Hashtable<Tkey, Tvalue>::Hashtable(int capacity) {
        this->capacity = capacity;
        size = 0;
        H = new std::list<struct info<Tkey, Tvalue>> [capacity];
    }
template <typename Tkey, typename Tvalue>
Hashtable<Tkey, Tvalue>::~Hashtable() {
        H->clear();
        delete [] H;
    }
template <typename Tkey, typename Tvalue>
unsigned int Hashtable<Tkey, Tvalue>::hash(Tkey str) {
    const unsigned int fnv_prime = 0x811C9DC5;
    unsigned int hash = 0;
    unsigned int i = 0;
    unsigned int len = str.length();

    for (i = 0; i < len; i++) {
        hash *= fnv_prime;
        hash ^= (str[i]);
    }

    return hash;
}
template <typename Tkey, typename Tvalue>
void Hashtable<Tkey, Tvalue>::put(Tkey key, Tvalue value) {
        typename std::list<struct info<Tkey, Tvalue>>::iterator it;
        int sw = 0;
        int index = hash(key) % capacity;

        for (it = H[index].begin() ; it != H[index].end() ; ++it) {
            if (it->key == key) {
                it->value = value;
                sw = 1;
                break;
            }
        }

        if (sw == 0) {
            info<Tkey, Tvalue> *node = new info<Tkey, Tvalue>;
            node->key = key;
            node->value = value;
            H[index].push_back(*node);
            delete node;
            ++size;
        }
    }
template <typename Tkey, typename Tvalue>
Tvalue Hashtable<Tkey, Tvalue>::get(Tkey key) {
        typename std::list<struct info<Tkey, Tvalue>>::iterator it;
        int index = hash(key) % capacity;

        for (it = H[index].begin() ; it != H[index].end() ; ++it) {
            if (it->key == key) {
                return it->value;
            }
        }

        return 0;
}

template class Hashtable <std::string, int>;
