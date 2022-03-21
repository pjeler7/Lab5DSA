#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
	currentIndex = 0;
	currentNodeIndex = 0;
	traverse(map.head);
	if (!this->vct.empty()) {
		this->currentNode = this->vct[currentNodeIndex];
	}
	else {
		this->currentNode = nullptr;
	}
}

void SMMIterator::traverse(BSTNode* node) {
	if (node == nullptr) {
		return;
	}
	BSTNode* left = node->left;
	BSTNode* right = node->right;
	if (left != nullptr)
	{
		traverse(left);
	}
	vct.push_back(node);

	if (right != nullptr)
	{
		traverse(right);
	}
}


void SMMIterator::first() {
	vct.clear();
	currentIndex = 0;
	currentNodeIndex = 0;
	traverse(map.head);
	if (!this->vct.empty()) {
		this->currentNode = this->vct[currentNodeIndex];
	}
	else {
		this->currentNode = nullptr;
	}
}

void SMMIterator::next() {
	if (!valid())
		throw std::exception();
	if (currentIndex < currentNode->length - 1) {
		currentIndex += 1;
		return;
	}
	else {
		currentIndex = 0;
		currentNodeIndex++;
		if (this->currentNodeIndex < this->vct.size()) {
			this->currentNode = this->vct[currentNodeIndex];
		}
		else {
			this->currentNode = nullptr;
		}
	}
}

bool SMMIterator::valid() const {
	if (map.isEmpty())
		return false;
	return this->currentNode != NULL;
}

TElem SMMIterator::getCurrent() const {
	if (!valid())
		throw std::exception();
	return std::make_pair(currentNode->key, currentNode->elem[currentIndex]);
}


