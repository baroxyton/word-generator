#include "../tokenizers/read_file.hpp"
#include "../tokenizers/read_tokens.hpp"
#include "./wordnet.hpp"
#include "read_wordnet.hpp"
#include <cstdlib> // for rand and srand
#include <iostream>
#include <numeric>
#include <vector>

size_t choose_random_index(std::vector<double> *weights) {
  double random_value = (rand() / (RAND_MAX + 1.0)) *
                        std::accumulate(weights->begin(), weights->end(), 0.0);
  double cumulative = 0.0;

  for (size_t i = 0; i < weights->size(); ++i) {
    cumulative += weights->at(i);
    if (random_value < cumulative) {
      return i;
    }
  }

  return weights->size() - 1;
}

std::string generate_word(network::Network *net,
                          std::vector<tokenizers::token> &toks) {
  std::string result = "";
  std::vector<int> tokens;
  int token = -1;
  int layer = 0;
  while (token != 0) {
  }
}

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  if (argc < 2) {
    std::cout << "Please enter network filename" << std::endl;
    exit(1);
  }
  if (argc < 3) {
    std::cout << "Please enter token filename" << std::endl;
    exit(1);
  }
  std::string networkfile{argv[1]};
  std::string tokenfile{argv[2]};

  if (!tokenizers::file_exists(networkfile) ||
      !tokenizers::file_exists(tokenfile)) {
    std::cout << "Error: no such file or directory" << std::endl;
    exit(1);
  }
  network::Network *net = network::read_net(networkfile);
  std::vector<tokenizers::token> all_tokens =
      tokenizers::read_tokens(tokenfile);
  std::string word = generate_word(net, all_tokens);

  return 0;
}
