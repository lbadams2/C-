/*
 * queen.h
 *
 *  Created on: Jun 16, 2014
 *      Author: Liam
 */

#ifndef QUEEN_H_
#define QUEEN_H_

class Queen{
public:
	Queen(int, Queen *);
	bool findSolution();
	bool advance();
	void print() const;

private:
	int row;
	const int column;
	Queen * neighbor;

	bool canAttack(int, int) const;

};



#endif /* QUEEN_H_ */
