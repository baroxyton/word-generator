#include "../tokenizers/read_file.hpp"
#include "../tokenizers/read_tokens.hpp"
#include "./wordnet.hpp"
#include "read_wordnet.hpp"
#include <chrono>
#include <cstdlib> // for rand and srand
#include <iostream>
#include <map>
#include <string>
#include <vector>
size_t choose_random_index(std::vector<double> *weights, int i) {
  double random_value = (rand() / (RAND_MAX + 1.0));
  double cumulative = 0.0;

  for (size_t i = 0; i < weights->size(); ++i) {
    cumulative += weights->at(i);
    /*
    if(i <= 2){
      bool is_positive = (rand() / (RAND_MAX + 1.0)) < 0.5;
      int multiplier = is_positive?1:-1;
      cumulative += (rand() / (RAND_MAX + 1.0)) / 50 * -1 * multiplier;
    }
    */
    if (random_value < cumulative) {
      return i;
    }
  }

  return weights->size() - 1;
}
std::map<int, std::string> token_map;

std::string generate_word(network::Network *net,
                          std::vector<tokenizers::token> &toks) {
  std::string result = "";
  std::vector<int> tokens;
  int token = 0;
  int layer = 0;
  while (true) {
    const auto &current_weighted_token = net->layers[layer]->at(token);
    result += token_map[current_weighted_token->token->id];

    // Choose the next token based on out_weights
    token = choose_random_index(current_weighted_token->weigths_out, layer);
    // std::cout << net->layers[layer+1]->at(token)->token->id << std::endl;
    if (net->layers[layer + 1]->at(token)->token->id == 1) {
      break;
    }
    layer++;
  }
  return result;
}

int main(int argc, char *argv[]) {
  auto currentTime = std::chrono::system_clock::now();
  auto duration = currentTime.time_since_epoch();
  auto millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

  srand(static_cast<unsigned int>(millis));

  if (argc < 2) {
    std::cout << "Please enter network filename" << std::endl;
    exit(1);
  }
  if (argc < 3) {
    std::cout << "Please enter token filename" << std::endl;
    exit(1);
  }
  int num_words = 1;
  if (argc >= 4) {
    num_words = std::stoi(argv[3]);
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

  for (auto tok : all_tokens) {
    token_map[tok.id] = tok.token;
  }
  for (int i = 0; i < num_words; i++) {
    std::string word = generate_word(net, all_tokens);
    std::cout << "Word generated: " << word << std::endl;
  }
  return 0;
}
