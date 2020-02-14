// Copyright Teodor Matei 313 - CA
#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>
#include "./SkipList.h"
#include "Racer.h"

template <typename T>
SkipNode<T>::SkipNode(T key, int level) {
	this->key = key;

	forward = new SkipNode<T>*[level + 1];

	memset(forward, 0, sizeof(SkipNode<T>*) * (level + 1));
}

template <typename T>
SkipNode<T>::SkipNode(const SkipNode& node) {
	this->key = node.key;

	while (forward != nullptr) {
		forward = node.forward[0];
	}
}

template <typename T>
SkipNode<T>& SkipNode<T>::operator=(const SkipNode& node) {
	this->key = node.key;

	while (forward != nullptr) {
		forward = node.forward[0];
	}

	return *this;
}

template <typename T>
SkipNode<T>::~SkipNode() {
	delete []forward;
}


template <typename T>
SkipList<T>::SkipList(T key, int maxLevel, float probability) {
	this->maxLevel = maxLevel;
	this->probability = probability;
	this->level = 0;
	this->key = key;
	header = new SkipNode<T>(key, maxLevel);
}

template <typename T>
SkipList<T>::~SkipList() {
	SkipNode<T>* currentNode = header;

	while (currentNode != nullptr) {
		SkipNode<T>* tempNode = currentNode;
		currentNode = currentNode->forward[0];
		delete tempNode;
	}
}

template <typename T>
int SkipList<T>::randomLevel() {
	float r = (float) rand() / RAND_MAX;
	int lvl = 0;

	while (r < probability && lvl < maxLevel) {
		++lvl;
		r = (float) rand() / RAND_MAX;
	}

	return lvl;
}

template <typename T>
SkipNode<T>* SkipList<T>::getHeader() {
	return header;
}

template <typename T>
void SkipList<T>::insert(T key) {
	SkipNode<T> *current = header;

	SkipNode<T> *path[maxLevel + 1];

	memset(path, 0, sizeof(SkipNode<T>*) * (maxLevel + 1));

	for (int i = level ; i >= 0 ; --i) {
		while (current->forward[i] != nullptr && current->forward[i]->key > key) {
			current = current->forward[i];
		}

		path[i] = current;
	}

	current = current->forward[0];

	if (current == nullptr || current->key != key) {
		int randLvl = randomLevel();

		if (randLvl > level) {
			for (int i = level + 1 ; i < randLvl + 1 ; ++i) {
				path[i] = header;
			}

			level = randLvl;
		}

		SkipNode<T> *node = new SkipNode<T>(key, randLvl);

		for (int i = 0 ; i <= randLvl ; ++i) {
			node->forward[i] = path[i]->forward[i];
			path[i]->forward[i] = node;
		}
	}
}

template <typename T>
void SkipList<T>::displaySkipList() {
	for (int i = 0 ; i <= level ; ++i) {
		SkipNode<T> *node = header->forward[i];
		std::cout << "Level " << i << ": ";

		while (node != nullptr) {
			std::cout << node->key << " ";
			node = node->forward[i];
		}

		std::cout << '\n';
	}
}

template <typename T>
void SkipList<T>::remove(T key) {
	SkipNode<T> *current = header;

	SkipNode<T> *path[maxLevel + 1];

	memset(path, 0, sizeof(SkipNode<T>*) * (maxLevel + 1));

	for (int i = level ; i >= 0 ; --i) {
		while (current->forward[i] != nullptr && current->forward[i]->key > key) {
			current = current->forward[i];
		}
		path[i] = current;
	}

	current = current->forward[0];

	if (current != nullptr && current->key == key) {
		for (int i = 0 ; i <= level ; ++i) {
			if (path[i]->forward[i] != current) {
				break;
			}

			path[i]->forward[i] = current->forward[i];
		}

		while (level > 0 && header->forward[level] == 0) {
			--level;
		}
	}

	delete current;
}

template <typename T>
SkipNode<T>* SkipList<T>::search(T key) {
	SkipNode<T>* current = header;

	for (int i = level ; i >= 0 ; --i) {
		while (current->forward[i] != nullptr && current->forward[i]->key > key) {
			current = current->forward[i];
		}
	}

	current = current->forward[0];

	if (current->key == key) {
		return current;
	}

	return nullptr;
}

template class SkipList<int>;
template class SkipList<Racer>;
