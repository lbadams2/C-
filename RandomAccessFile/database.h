/*
 * database.h
 *
 *  Created on: Jun 22, 2014
 *      Author: Liam
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <fstream>
#include <stdio.h>
#include <iostream>
using namespace std;

template<class T>
class MyDatabase {
public:
	MyDatabase();
	void run();
private:
	fstream database;
	char fName[20];
	ostream& print(ostream&);
	void add(T&);
	bool find(const T&);
	void modify(const T&);
	friend ostream& operator<<(ostream& out, MyDatabase& db){
		return db.print(out);
	}
};
#endif /* DATABASE_H_ */
