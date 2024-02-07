#pragma once
#include <string>
#include <unordered_map>
#include <vector>

namespace tokenizers {
constexpr int CHAR_TOKENIZER = 0;
constexpr int MULTICHAR_TOKENIZER = 1;
constexpr int SYLLABLE_TOKENIZER = 2;

constexpr int SPECIAL_TOKEN_OFFSET = 15;
struct token {
  int id;
  std::string token;
};

std::unordered_map<std::string, int> *
tokens_to_map(std::vector<tokenizers::token> &tokens);

int get_max_toklen(std::vector<tokenizers::token> &tokens);

std::vector<tokenizers::token>
tokenize_string(std::unordered_map<std::string, int> *tokens, std::string word,
                int max_token_length);
} // namespace tokenizers
