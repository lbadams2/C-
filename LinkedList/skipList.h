/*
 * skipList.h
 *
 *  Created on: Jun 29, 2014
 *      Author: Liam
 */

#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include <stdlib.h>

const int maxLevel = 4;

template<class T>
class SkipListNode {
public:
	SkipListNode(){

	}
	T key;
	SkipListNode **next;
};

template<class T>
class SkipList {
public:
	SkipList();
	bool isEmpty() const;
	void choosePowers();
	int chooseLevel();
	T* skipListSearch(const T&);
	SkipListNode<T> *searchReturnNode(const T&);
	void skipListInsert(const T&);
private:
	typedef SkipListNode<T> *nodePtr;
	nodePtr root[maxLevel];
	int powers[maxLevel];
};

template<class T>
SkipList<T>::SkipList(){
	for(int i = 0; i < maxLevel; i++)
		root[i] = 0;
}

template<class T>
bool SkipList<T>::isEmpty() const {
	return root[0] == 0;
}
/*
 * Generates maxLevel numbers for used for creating distribution of nodes with 1 to maxLevel pointers and stores them in the powers[] array
 */
template<class T>
void SkipList<T>::choosePowers() {
	powers[maxLevel - 1] = (2 << (maxLevel-1)) - 1; // 2^maxLevel - 1
	for(int i = maxLevel - 2, j = 0; i>= 0; i--, j++)
		powers[i] = powers[i+1] - (2 << j); // 2^(j+1)
}

/*
 * i ranges from 1 to maxLevel, indices of array are 0 to maxLevel - 1.  powers[maxLevel-1] is the last element of the array and will contain the
 * value n-1 therefore the maximum value from the % operator is n-2. it is necessary to subtract 1 from i before returning it so that it is 0
 * based like the indices of the array. seems like i could just be initialized to 0 rather than 1
 */
template<class T>
int SkipList<T>::chooseLevel() {
	int i, r = rand() % powers[maxLevel-1] + 1;
	for(i = 1; i < maxLevel; i++)
		if(r < powers[i])
			return i - 1; // return a level < the highest level if the condition is satisfied
	return i - 1; // return highest level, conditional expression was not satisfied
}

template<class T>
SkipListNode<T>* SkipList<T>::searchReturnNode(const T& key){
	if(isEmpty()) return 0;
	nodePtr prev, curr;
	int lvl; // the index of the pointer in the node
	for(lvl = maxLevel -1; lvl >= 0 && !root[lvl]; lvl--); // find the highest non null level
	prev = curr = root[lvl];
	while(true) {
		if(key == curr->key)
			return curr;
		else if(key < curr->key) {
			if(lvl == 0)
				return 0;
			else if(curr == root[lvl])
				curr = root[--lvl];
			//prev->next gets the pointer in the array of pointers in the node, adds lvl to it, then derefernces to get the node pointed to
			else curr = *(prev->next + lvl);
		}
		else {
			prev = curr;
			if(*(curr->next + lvl) != 0)
				curr = *(curr->next + lvl);
			else {
				for(lvl--; lvl >= 0 && *(curr->next + lvl)==0; lvl--);
				if(lvl >= 0)
					curr = *(curr->next + lvl);
				else return 0;
			}
		}
	}
}

/*
 * searching follows the pointers on the highest level until the element is found.  in the case of reaching the end of the list or encountering an
 * element that is greater than the element searched for, the search is restarted from the node preceding this node with a greater value, on a level
 * or position in pointer array lower than before.
 */
template<class T>
T* SkipList<T>::skipListSearch(const T& key){
	if(isEmpty()) return 0;
	nodePtr prev, curr;
	int lvl; // the index of the pointer in the node
	for(lvl = maxLevel -1; lvl >= 0 && !root[lvl]; lvl--); // find the highest non null level
	prev = curr = root[lvl];
	while(true) {
		if(key == curr->key)
			return &curr->key; // -> takes precedence over &
		else if(key < curr->key) {
			if(lvl == 0)
				return 0;
			else if(curr == root[lvl])
				curr = root[--lvl];
			//prev->next gets the pointer in the array of pointers in the node, adds lvl to it, then derefernces to get the node pointed to
			else curr = *(prev->next + lvl);
		}
		else {
			prev = curr;
			if(*(curr->next + lvl) != 0)
				curr = *(curr->next + lvl);
			else {
				for(lvl--; lvl >= 0 && *(curr->next + lvl)==0; lvl--);
				if(lvl >= 0)
					curr = *(curr->next + lvl);
				else return 0;
			}
		}
	}
}

template<class T>
void SkipList<T>::skipListInsert(const T& key){
	nodePtr curr[maxLevel], prev[maxLevel], newNode;
	int lvl, i;
	curr[maxLevel-1] = root[maxLevel-1];
	prev[maxLevel-1] = 0;
	for(lvl = maxLevel -1; lvl >= 0; lvl--) {
		while(curr[lvl] && curr[lvl]->key < key){
			prev[lvl] = curr[lvl];
			curr[lvl] = *(curr[lvl]->next + lvl);
		}
		if(curr[lvl] && curr[lvl]->key == key)
			return;
		if(lvl > 0)
			if(prev[lvl] == 0) {
				curr[lvl-1] = root[lvl-1];
				prev[lvl-1] = 0;
			}
			else {
				curr[lvl-1] = *(prev[lvl]->next + lvl-1);
				prev[lvl-1] = prev[lvl];
			}
	}
	lvl = chooseLevel();
	newNode = new SkipListNode<T>;
	// make the size of the pointer array of the node as large as necessary for the level the node will be inserted in
	newNode->next = new nodePtr[sizeof(nodePtr) * (lvl+1)];
	newNode->key = key;
	for(i = 0; i <= lvl; i++) {
		*(newNode->next + i) = curr[i];
		if(prev[i] == 0)
			root[i] = newNode;
		// next is the array of pointers, increment position in array and dereference, assign pointer to node to point to newNode
		else *(prev[i]->next + i) = newNode;
	}
}
#endif /* SKIPLIST_H_ */
