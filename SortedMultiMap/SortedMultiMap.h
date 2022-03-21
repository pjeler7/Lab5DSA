#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111)
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

typedef struct BSTNode {
    TValue* elem;
    TKey key;
    int capacity;
    int length;
    BSTNode* left;
    BSTNode* right;
};

class SortedMultiMap {
	friend class SMMIterator;
private:
        //int capacity;
        int root;
        int length;
        //int firstEmpty;
        Relation r;

        void recomputeFirstEmpty();

        void resize(BSTNode* node);

        BSTNode* addElemNode(BSTNode* node, TValue v);

        BSTNode* addRec(BSTNode* node, TKey c, TValue v);
        void traverse(BSTNode* node);

      //  int insertRec(int node, TElem e);


        //int removeRec(int node, TElem e, bool& found);

        BSTNode* minimum(BSTNode* node);

        BSTNode* removeNode(BSTNode* node);

        BSTNode* removeRec(BSTNode* node, TKey c, TValue v, bool &isFound);

        BSTNode* removeMin(BSTNode* node);

public:
    BSTNode* head;

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    void print(BSTNode* node);

    // destructor
    ~SortedMultiMap();
};
