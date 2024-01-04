#pragma once
#include <string>
#include <vector>

namespace tokenizers{
constexpr int CHAR_TOKENIZER = 0;
constexpr int MULTICHAR_TOKENIZER = 1;
constexpr int SYLLABLE_TOKENIZER = 2;

constexpr int SPECIAL_TOKEN_OFFSET = 15;
struct token{
  int id;
  std::string token;	
};

std::vector<tokenizers::token> tokenize_string(std::vector<tokenizers::token>& tokens, std::string word);
}
