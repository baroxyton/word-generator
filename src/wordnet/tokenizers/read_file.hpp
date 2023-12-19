#pragma once
#include <string>
namespace tokenizers{
	std::string read_wordlist(std::string& filepath);
	bool file_exists(std::string& filepath);
}

