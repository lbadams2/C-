#include <iostream>
#include <list>
using namespace std;

typedef list<int> IntegerList;

double power(double x, unsigned int n){
	if(n == 0)
		return 1.0;
	else
		return x*power(x, n-1);
}

/*
 * takes advantage of the run time stack in order to work.  for "ABC" first A is pushed, then B, then C, then when a new line is encountered
 * by hitting enter(this should be a carriage return, not sure exactly how cin works), control returns to the last activation record pushed on
 * the stack for 'C', so ch holds this value which is passed to cout.put(), then control returns to B, then A.
 */
void reverse(){
	char ch;
	cin.get(ch);
	if(ch != '\n')
		reverse();
	cout.put(ch);
}

int binomial(unsigned int n, unsigned int k){
	if(k == 0 || k == n)
		return 1;
	else
		return binomial(n-1, k-1) + binomial(n-1, k);
}


//template<typename T>
int listLength(IntegerList* intlist){
	static IntegerList::iterator i = intlist->begin();
	static int nodes = 0;
	if(i != intlist->end()){
		nodes++;
		i++;
		nodes = listLength(intlist);
	}
	else
		return nodes;
	return nodes;
}

int main() {
	//int result = binomial(8, 6);
	//cout << result;
	//reverse();
	IntegerList intlist();
	for(int i = 0; i < 5; i++)
		intlist->push_front(i);
	listLength(intlist); // pass iterator instead
	return 0;
}
