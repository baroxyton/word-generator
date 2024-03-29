#pragma once
#include "../tokenizers/tokenize.hpp"
#include <vector>
namespace network {
struct weighted_token {
  tokenizers::token* token;
  std::vector<double>* weigths_out;
};
class Network {
public:
  std::vector<std::vector<weighted_token *> *> layers;
  std::string get_output(int length,
                         std::vector<tokenizers::token> start_tokens);
};
}; // namespace network
