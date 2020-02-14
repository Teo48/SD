// Copyright Teodor Matei 313 CA - 2019
#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <list>
#include <iterator>
#include <string>

template <typename Tkey, typename Tvalue> struct info {
    Tkey key;
    Tvalue value;
};

template <typename Tkey, typename Tvalue> class Hashtable {
 private:
    std::list<struct info<Tkey, Tvalue>> *H;
    int size;
    int capacity;

 public:
    /*
      Constructorul ce seteaza capcitatea hashtable-ului.
      hash(std::string str) --> functia de hashing ce intoarce un int fara semn.
      put --> adauga in hashtable o pereche de tip (Cheie, Valoare).
      get --> returneaza valoarea cheii din hashtable.
    */
    explicit Hashtable(int capacity);
    ~Hashtable();
    unsigned int hash(Tkey str);
    void put(Tkey key, Tvalue value);
    Tvalue get(Tkey key);
};

#endif  // HASHTABLE_H_
