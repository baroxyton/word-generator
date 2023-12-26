#pragma once
#include "tokenize.hpp"
#include <vector>
#include <string>
namespace tokenizers{
    std::vector<token> read_tokens(std::string filename);
}