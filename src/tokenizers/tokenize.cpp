#include "tokenize.hpp"
#include <algorithm>
#include <limits.h>
#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, int> *
tokenizers::tokens_to_map(std::vector<tokenizers::token> &tokens) {

  auto token_map = new std::unordered_map<std::string, int>;
  for (auto curr_token : tokens) {
    (*token_map)[curr_token.token] = curr_token.id;
  }
  return token_map;
}
int tokenizers::get_max_toklen(std::vector<tokenizers::token> &tokens) {
  int max_token_length = INT_MIN;
  for (auto curr_token : tokens) {
    max_token_length = std::max<int>(max_token_length, curr_token.token.size());
  }
  return max_token_length;
}
std::vector<tokenizers::token>
tokenizers::tokenize_string(std::unordered_map<std::string, int> *tokens,
                            std::string word, int max_token_length) {
  std::vector<token> result;
  int token_begin = 0;
  while (token_begin < word.size()) {
    for (int i = std::min<int>(max_token_length, word.size() - token_begin);
         i != 0; i--) {
      if ((word.size() - 1 - i) <= 0) {
        continue;
      }
      if (word.size() >= token_begin + i &&
          tokens->find(word.substr(token_begin, i)) != tokens->end()) {
        int found_token = (*tokens)[word.substr(token_begin, i)];
        result.push_back(token{found_token, word.substr(token_begin, i)});
        token_begin += i;
      }
    }
  }
  return result;
}
