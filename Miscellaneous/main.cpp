/*
 * main.cpp
 *
 *  Created on: Jun 20, 2014
 *      Author: Liam
 */
#include "misc.h"

// this function could probably also be implemented recursively
double root(double (*f)(double), double a, double b, double epsilon){
	double middle = (a+b)/2;

	// if a*b < 0, one endpoint is negative, use interval from a to middle for further
	// iterations, else use middle to b. when f(middle) = 0 or f(middle) is less than some
	// small value epsilon, return middle
	while(f(middle) != 0 || fabs(a-b) < epsilon){
		if(a * b < 0)
			b = middle;
		else a = middle;
		middle = (a+b)/2;
	}
	return middle;
}

double g(double input){
	return input -= 1;
}

int main(){
	//cout << root((g*), 34.0, 56.0, .01);

	/*
	 * prompt user for file names, create an input stream for from so that data can be read from the file.  create an iterator for this input stream. do the same for the
	 * output stream.  pass the iterators to the set constructor. a stream is a sequence of characters in this case, can be a sequence of other types like byte, iterators
	 * are used for sequences.
	 */
	string from, to;
	cin >> from >> to;

	ifstream is{from};
	ofstream os{to};

	set<string> b{istream_iterator<string>{is}, istream_iterator<string>{}};
	copy(b.begin(), b.end(), ostream_iterator<string>{os, "\n"});

	return !is.eof() || !os;
}


