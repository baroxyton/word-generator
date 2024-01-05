#include "tokenize.hpp"
#include <algorithm>
#include <limits.h>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<tokenizers::token>
tokenizers::tokenize_string(std::vector<tokenizers::token> &tokens,
                            std::string word) {
  int max_token_length = INT_MIN;
  std::unordered_map<std::string, int> token_map;
  for (auto curr_token : tokens) {
    max_token_length = std::max<int>(max_token_length, curr_token.token.size());
    token_map[curr_token.token] = curr_token.id;
  }
  std::vector<token> result;
  int token_begin = 0;
  while (token_begin < word.size()) {
    for (int i = std::min<int>(max_token_length, word.size() - token_begin); i != 0; i--) {
      if ((word.size() - 1 - i) <= 0) {
        continue;
      }
      if (token_map.find(word.substr(token_begin, i)) != token_map.end()) {
        int found_token = token_map[word.substr(token_begin, i)];
        result.push_back(token{found_token, word.substr(token_begin, i)});
        token_begin += i;
      }
    }
  }
  return result;
}
