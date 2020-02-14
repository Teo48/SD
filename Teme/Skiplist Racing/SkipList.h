// Copyright Teodor Matei 313 - CA
#ifndef SKIPLIST_H_
#define SKIPLIST_H_

/*
	SkipNode(T key, int level) -> Constructor. Seteaza key-ul nodului, creeaza
		un array de pointeri SkipNode de dimensiune level + 1 pe care il
		initializeaza cu 0.
	explicit SkipNode(const SkipNode& node) -> Copy Constructor
	SkipNode& operator=(const SkipNode& node) -> Copy Assignment
	~SkipNode() - Destructorul. Se elibereaza memoria alocata lui forward.
*/

template <typename T>
class SkipNode {
 public:
	T key;
	SkipNode<T> **forward;
	SkipNode(T key, int level);
	explicit SkipNode(const SkipNode& node);
	SkipNode& operator=(const SkipNode& node);
	~SkipNode();
};

/*
	SkipList(T key, int maxLevel, float probability) -> Constructorul.
		Se initializeaza key, maxlevel si probability. Level se seteaza pe 0
		si se creeaza nodul header cu parametrii (key, maxLevel).
	~SkipList() -> Destructorul. Se ia un pointer la header. Cat timp headerul
		nu este nullptr se elibereaza memoria pentru fiecare nod din SkipList.
	randomLevel() -> Returneaza un numar intreg random cuprins intre 0 si 
		maxLevel bazandu-se pe principiul unui CoinFlip.
	getHeader() -> returneaza un pointer la header-ul SkipList-ului.
	insert(T key) -> Insereaza key in SkipList. Inserarea se va face in O(log n).
	displaySkipList() -> Afiseaza SkipListul in formatul urmator:
		Level i: Elementele de pe nivelul i.
	remove(T Key) -> Sterge key din SkipList. Stergerea se va face in O(log n).
	search(T Key) -> Returneaza un pointer la key-ul din SkipList. Cautarea se
		va face in O(logn).
*/

template <typename T>
class SkipList {
 private:
	int maxLevel, level;
	float probability;
	T key;
	SkipNode<T>* header;

 public:
	SkipList(T key, int maxLevel, float probability);
	~SkipList();
	int randomLevel();
	SkipNode<T>* getHeader();
	void insert(T key);
	void displaySkipList();
	void remove(T key);
	SkipNode<T>* search(T key);
};

#endif  //  SKIPLIST_H_
