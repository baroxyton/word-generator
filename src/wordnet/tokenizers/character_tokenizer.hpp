#pragma once
#include "tokenize.hpp"
#include <vector>
namespace tokenizers{
	std::vector<tokenizers::token> character_tokenizer(std::string filecontent);
}
