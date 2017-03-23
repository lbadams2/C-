#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

struct inputLine
{
	int population;
	string city;
	string state;
	vector<string> interstates;
};

vector<inputLine> inputLines;

vector<string> arguments(int argc, char* argv[]){
	vector<string> args;
	for(int i = 0; i!=argc; ++i)
		args.push_back(argv[i]);
	return args;
}

bool compareByPopulation(const inputLine& a, const inputLine& b){
	return a.population < b.population;
}

bool compareByCity(const inputLine& a, const inputLine& b){
	return a.city < b.city;
}

bool compareByState(const inputLine& a, const inputLine& b){
	return a.state < b.state;
}

vector<string> &split(const string &s, char delim, vector<std::string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

void writeToOutputFile(){
	sort(inputLines.begin(), inputLines.end(), compareByPopulation);
	string ranges = "";
	int prevPopulation, index  = 0;
	bool match = false;

	for(struct inputLine i : inputLines){
		if(i.population == prevPopulation){
			if(match)
				ranges += index;
			else{
				if(ranges.size() > 0){
					ranges += ";";
					ranges += index;
				}
				else
					ranges += index;
			}
			match = true;
		}
		else
			match = false;

		prevPopulation = i.population;
		index++;
	}

	vector<string> tokens = split(ranges, ';');
			for(auto s : tokens){
				char first = s.at(0);

				for(unsigned int i = 1; i < s.size(); i++)
					inputLines[s.at(i)].population = 0;

				char last;
				unsigned int i = 0;
				while(i < s.size()){
					last = s[i];
					i++;
				}
				int begin = first - '\0';
				int end = last - '\0';
				//sort(inputLines.begin() + begin, inputLines.end() + end, compareByState);
			}

	for(auto i : inputLines)
		sort(i.interstates.begin(), i.interstates.end());

	ofstream out("Cities_By_Population.txt");

	for(auto i : inputLines){
		if(i.population > 0){
			out << i.population << '\n' << '\n';
			out << i.city << ", " << i.state << '\n';
			out << "Interstates: ";
			for(auto is : i.interstates) {
				out << is;
				if(is != *(i.interstates.end() - 1))
					out << ", ";
			}
		}
		else {
			out << i.city << ", " << i.state << '\n';
			out << "Interstates: ";
			for(auto is : i.interstates) {
				out << is;
				if(is != *(i.interstates.end() - 1))
					out << ", ";
				else
					out << '\n';
			}
		}
	}
}

void addToStructVector(vector<string>& tokens){
	struct inputLine s;
	for(auto token : tokens){
		s.population = atoi(tokens.at(0).c_str());
		s.city = tokens.at(1);
		s.state = tokens.at(2);
		for(auto it = tokens.begin() + 3; it != tokens.end(); ++it){
			s.interstates.push_back(*it);
		}
	}
	inputLines.push_back(s);
}

void parseInputFile(char* filename){
	ifstream infile(filename);
	string line;
	vector<string> tokens;
	while(getline(infile, line)){
		size_t prev = 0, pos;
		    while ((pos = line.find_first_of("|;", prev)) != string::npos)
		    {
		        if (pos > prev)
		            tokens.push_back(line.substr(prev, pos-prev));
		        prev = pos+1;
		    }
		    if (prev < line.length())
		        tokens.push_back(line.substr(prev, string::npos));
		    addToStructVector(tokens);
		    tokens.clear();
	}
	writeToOutputFile();
}

int main(int argc, char* argv[]){

	vector<string> args = arguments(argc, argv);
	switch(args.size()){
	case 1:
		cerr << "Enter file name";
		break;
	case 2:
		parseInputFile(argv[1]);
		break;
	default:
		cerr << "Too many arguments";
	}

	return 0;
}
