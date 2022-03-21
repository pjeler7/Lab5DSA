#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

//Theta(n)
void SortedMultiMap::resize(BSTNode* node) {
	BSTNode* newNodes = new BSTNode[node->capacity * 2];
	for (int i = 0; i < node->length; i++) {
		newNodes->elem[i] = node->elem[i];
	}
	node->capacity *= 2;
	delete[] node->elem;
	node->elem = newNodes->elem;
}


//Theta(1)
SortedMultiMap::SortedMultiMap(Relation r) {
	head = new BSTNode();
	head->capacity = 20;
	head->length = 0;
	head->elem = new TValue[head->capacity];
	head->left = new BSTNode();
	head->right = new BSTNode();

	this->length = 0;
	this->r = r;
}
//O(n)
void SortedMultiMap::add(TKey c, TValue v) {
	if (this->isEmpty()) {
		this->head->key = c;
		this->head->elem[0] = v;
		this->head->length += 1;
		this->head->right = nullptr;
		this->head->left = nullptr;
		this->length++;
		return;
	}
	head = addRec(head, c, v);
	////this->insertRec(this->root, std::make_pair(c, v));
	//BSTNode* current = head;
	//BSTNode* prev = nullptr;
	//bool isRight = true;
	//while (current != nullptr) {
	//	if (current->key == c) {
	//		this->addElemNode(current, v);
	//		this->length++;
	//		return;
	//	}
	//	prev = current;
	//	if (!r(current->key, c)) {
	//		current = current->left;
	//		isRight = false;
	//	}
	//	else {
	//		current = current->right;
	//		isRight = true;
	//	}
	//}
	//current = new BSTNode();
	//current->key = c;
	//current->elem = new TValue[20];
	//current->elem[0] = v;
	//current->length = 1;
	//current->capacity = 20;
	//current->right = nullptr;
	//current->left = nullptr;
	//if (isRight) {
	//	prev->right = current;
	//}
	//else {
	//	prev->left = current;
	//}
	//this->length++;
}

//O(n)
BSTNode* SortedMultiMap::addRec(BSTNode* node, TKey c, TValue v) {
	if (node == nullptr) {
		BSTNode* newNode = new BSTNode();
		newNode->key = c;
		newNode->elem = new TValue[20];
		newNode->elem[0] = v;
		newNode->length = 1;
		newNode->capacity = 20;
		newNode->right = nullptr;
		newNode->left = nullptr;
		this->length++;
		return newNode;
	}

	if (node->key == c) {
		node = this->addElemNode(node, v);
		this->length++;
		return node;
	}
	if (!r(node->key, c)) {
		node->left = addRec(node->left, c, v);
		return node;
	}
	else {
		node->right = addRec(node->right, c, v);
		return node;
	}
}

//O(1)
BSTNode* SortedMultiMap::addElemNode(BSTNode* node, TValue v) {
	if (node->capacity == node->length)
		this->resize(node);
	node->elem[node->length] = v;
	node->length++;
	return node;
}

//O(n)
vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> values;
	BSTNode* current = this->head;
	while (current != nullptr) {
		if (current->key == c) {
			for (int i = 0; i < current->length; i++)
				values.push_back(current->elem[i]);
			return values;
		}
		if (!this->r(current->key, c)) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	return values;
}
//O(n)
bool SortedMultiMap::remove(TKey c, TValue v) {
	bool isRemoved = false;
	head = removeRec(head, c, v, isRemoved);
	return isRemoved;
}

BSTNode* SortedMultiMap::removeRec(BSTNode* node, TKey c, TValue v, bool& isFound) {
	if (node == nullptr) {
		return node;
	}
	if (node->key == c) {
		int len = node->length - 1;
		while (len >= 0) {
			if (node->elem[len] == v) {
				for (int i = len; i < node->length - 1; i++) {
					node->elem[i] = node->elem[i + 1];
				}
				//delete[] node->elem[this->length - 1];
				node->length--;
				length--;
				isFound = true;
				if (node->length == 0) {
					if (node->left == nullptr && node->right == nullptr) {
						return nullptr;
					}
					else if (node->left == nullptr) {
						return node->right;
					}
					else if (node->right == nullptr) {
						return node->left;
					}
					else {
						BSTNode* min = minimum(node);
						node->key = min->key;
						node->elem = min->elem;
						node->length = min->length;
						node->capacity = min->capacity;
						node->right = removeMin(node->right);
						delete min;
						return node;
					}
				}
				return node;
			}
			len--;
		}
		return node;
	}
	else if (!this->r(node->key, c)) {
		node->left = removeRec(node->left, c, v, isFound);
	}
	else {
		node->right = removeRec(node->right, c, v, isFound);
	}
	return node;
}

BSTNode* SortedMultiMap::removeMin(BSTNode* node) {
	while (node->right != nullptr) {
		node = node->right;
	}
	node->right = nullptr;
	return node;
}


BSTNode* SortedMultiMap::removeNode(BSTNode* node) {
	if (node->left == nullptr && node->right == nullptr) {
		return nullptr;
	}
	else if (node->left == nullptr) {
		return node->right;
	}
	else if (node->right == nullptr) {
		return node->left;
	}
	else {
		BSTNode* min = minimum(node);
		node->key = min->key;
		node->elem = min->elem;
		node->length = min->length;
		node->capacity = min->capacity;
		min = nullptr;
		return node;
	}
}

//Theta(1)
int SortedMultiMap::size() const {
	return this->length;
}

//Theta(1)
bool SortedMultiMap::isEmpty() const {
	return this->length == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

BSTNode* SortedMultiMap::minimum(BSTNode* node) {
	BSTNode* current = node;
	while (node->left != nullptr)
		current = node->left;
	return current;
}

SortedMultiMap::~SortedMultiMap() {
	delete[] this->head;
}



void SortedMultiMap::print(BSTNode* node) {
	if (node == nullptr) {
		return;
	}
	std::cout << node->key << " elem: " << node->length;
	if (node->left != nullptr)
		std::cout << " left: " << node->left->key;
	if (node->right != nullptr)
		std::cout << " right " << node->right->key;
	std::cout << endl;
	if (node->left != nullptr)
		print(node->left);
	if (node->right != nullptr)
		print(node->right);
}