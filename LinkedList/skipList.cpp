#include <iostream>
#include "skipList.h"
using namespace std;

int main(){
	int r;
	SkipListNode<int> *searchResult;
	SkipList<int> *list = new SkipList<int>();
	for(int i = 0; i<16; i++){
		r = rand()%16;
		list->skipListInsert(r);
	}

	for(int i = 0; i<16; i++){
		searchResult = list->searchReturnNode(i);
		if(searchResult){
			SkipListNode<int> *pointerToNextNode = *(searchResult->next);
			cout << "Found " << searchResult->key << " next node " << pointerToNextNode->key << "\n";
		}
	}
}
