#include <ifstream>
#include <iostream>
namespace tokenizers{
	// Read wordlist, return as raw string
	std::string read_wordlist(std::string filepath){
		std::ifstream filestream(filepath);
		std::string data(std::istreambuf_iterator<char>(filestream),
			std::istreambuf_iterator<char>());	
		return data;	
	}
}
