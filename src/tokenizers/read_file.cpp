#include <fstream>
#include <iostream>
#include "read_file.hpp"
// Read wordlist, return as raw string
std::string tokenizers::read_wordlist(std::string& filepath){
	std::ifstream filestream(filepath);
	std::string data = std::string{std::istreambuf_iterator<char>(filestream),
		std::istreambuf_iterator<char>()};	
	return data;	
}
bool tokenizers::file_exists(std::string& filepath){
	std::ifstream f(filepath.c_str());
	return f.good();	
}
