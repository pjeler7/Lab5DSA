#pragma once

#include "SortedMultiMap.h"
#include <stack>

class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	BSTNode* currentNode;
	//std::stack<BSTNode*> stack;
	std::vector<BSTNode*> vct;
	int currentNodeIndex;
	int currentIndex;

	void traverse(BSTNode* node);

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

