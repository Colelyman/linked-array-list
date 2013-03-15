#include "list.h"
#include <fstream>
#include <map>
#include <string>

using std::ifstream;
using std::ofstream;
using std::map;
using std::string;

int main(int argc, char* argv[]) {
	ifstream input;
	input.open(argv[1]);
	ofstream output;
	output.open(argv[2]);

	string command;
	while(input >> command) {

	}
	
	list<string> test = list<string>(5);

	return 0;
}
