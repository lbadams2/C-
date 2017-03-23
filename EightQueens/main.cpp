#include <iostream>
#include "queen.h"
using namespace std;

Queen::Queen(int col, Queen * ngh) : column(col), neighbor(ngh){
	row = 1;
}

bool Queen::canAttack(int testRow, int testColumn) const{
	if(row == testRow)
		return true;

	//test diagonals
	int columnDifference = testColumn - column;
	if((row + columnDifference == testRow) || (row - columnDifference == testRow))
		return true;

	//left most queen won't have a neighbor
	return neighbor && neighbor->canAttack(testRow, testColumn);
}

bool Queen::findSolution(){
	while(neighbor && neighbor->canAttack(row, column))
		if(!advance())
			return false;
		return true;
}

/*
 * while the current queen can advance find a solution, if not then advance the neighbor
 * and have the neighbor find a solution, this will percolate down the queens in each column
 */
bool Queen::advance(){
	if(row < 8){
		row++;
		return findSolution();
	}
	// neighbor is implicitly passed to advance to in order to access its row member
	if(neighbor && !neighbor->advance())
		return false;
	// this is reached if the current queen cannot advance and
	// the neighbor successfully advances and finds a solution.
	// current queen will reset to 1 and continue to advance itself in the context where
	// its neighbor has advanced itself
	row = 1;
	return findSolution();
}

void Queen::print() const{
	if(neighbor)
		neighbor->print();
	cout << "column " << column << " row " << row << '\n';
}

int main(){
	Queen * lastQueen = 0;

	for(int i = 1; i <= 8; i++){
		// what lastQueen points to changes after every invocation of new.  each queen object
		// saves a different pointer for its neighbor
		lastQueen = new Queen(i, lastQueen);
		if(!lastQueen->findSolution())
			cout << "no solution\n";
	}
	lastQueen->print();
	return 0;
}
