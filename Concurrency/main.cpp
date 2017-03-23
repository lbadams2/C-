#include <vector>
#include <thread>
#include <functional>
using namespace std;

void f(vector<double>& v);

struct F {
	vector<double>& v;
	F(vector<double>& vv):v(vv){}
	void operator()();
};

int main() {
	vector<double> some_vec {1,2,3,4,5,6};
	vector<double> vec2 {7,8,9,10};
	thread t1 {f, ref(some_vec)};// ref needed to tell thread to treat some_vec as reference rather than an object
								// compiler builds function object from arguments passed to thread constructor.
	thread t2 {F(vec2)};// saves a reference to vec2 in F, hopefully no other task access vec2 during execution. Passing by value would eliminate this risk.

	t1.join();// wait for thread to terminate
	t2.join();
}
