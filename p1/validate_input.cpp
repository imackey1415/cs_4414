#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>

// execute the command "cat scores | grep uva"

int main(int argc, char** argv) // same as int main(int argc, char* argv[])
{
	using namespace std;
	std::ifstream infile("test.txt");
	//char* fileName = argv[1];

	for(std::string line; getline(infile, line); ){

	std::vector < string > delimit_list;

	istringstream iss(line);

	do
	{
	string temp;
	iss >> temp;
	delimit_list.push_back(temp);

	} while (iss);

	
	//get each substring
	//delimit_push_back


	delimit_list.push_back(line);	

	
		for (std::vector<string>::const_iterator i = delimit_list.begin();
			i != delimit_list.end(); i++){
			std::cout << *i << '\n';
		}
	}	

	return 0;
}

