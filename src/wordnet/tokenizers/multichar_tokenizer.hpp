#pragma once
#include <vector>
#include "tokenize.hpp"
namespace tokenizers{
	constexpr int MULTICHAR_COUNT = 5;
	std::vector<token> multichar_tokenizer(std::string& file_content);
}
