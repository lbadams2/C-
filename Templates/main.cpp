/*
 * main.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: Liam
 */
#include <stdlib.h>
#include <memory>
#include <string>
#include <type_traits>
using namespace std;

 /*template<typename T> and template<class T> are synonymous. good design practice to create non template version first then generalize to template
   class templates should have non template copy constructor and assignment, same for move. type checking done at instantiation time. Templates provide
   compile time parametric polymorphism
   template is a generalized algorithm, can accept a variety of types and operations
*/
template<typename T>
class Xref {
public:
	Xref(int i, T* p) : index{i}, elem{p}, owned{true}
	{}

	Xref(int i, T& r):index{i}, elem{&r}, owned{false}
	{}

	Xref(int i, T&& r):index{i}, elem{new T{move(r)}}, owned{true}
		{}

	~Xref(){
		if(owned) delete elem;
	}

private:
	int index;
	T* elem;
	bool owned;
};

template<typename T>
T&& forward(typename remove_reference<T>::type& t)noexcept;

template<typename T>
T&& forward(typename remove_reference<T>::type&& t)noexcept;

/*
 * construct a T from and arg without making any extra copies and have it maintained by unique_ptr, this can be done when an rvalue is passed
 */
template<typename TT, typename A>
unique_ptr<TT> make_unique(int i, A&& a){
	return unique_ptr<TT>{new TT{i, forward<A>(a)}};
}


int main(){
	string x{"There and"};
	Xref<string> r1 {7, "Here"}; // rvalue
	Xref<string> r2 {9, x}; // lvalue
	Xref<string> r3 {3, new string{"There"}}; // rvalue

	auto p1 = make_unique<Xref<string>, ?>(7, "Here"); // forward(string&&)
	auto p2 = make_unique<Xref<string>, ?>(9, x); // forward(string&), returns string& &&, means string&, lvalue constructor for Xref called
}

/*
 * funtion overload rules for templates pick out the best specialization if function is not explicitly parameterized
 */


template<int>
struct int_exact_traits { // int_exact_traits<N>::type is a type with exactly N bits
	using type = int; // type is an alias for int, assigning something to type is assigning something to the type int
};

template<>
struct int_exact_traits<16> {
	using type = short;
};

template<int>
struct int_exact_traits<8> {
	using type = char;
};

// specializations used through the alias
template<int N>
using int_exact = typename int_exact_traits<N>::type;

int_exact<8> a = 7; // 8 is an int, setting the type int to 8, an int with 8 bits

/*
 * declare templates in a header and include them wherever they are needed, whichever translation unit they are needed. place definition in cpp file. a user
 * will include both files into their translation or compilation unit
 */
