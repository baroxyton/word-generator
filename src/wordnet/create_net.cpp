#include "create_net.hpp"
#include "../tokenizers/read_file.hpp"
#include "../tokenizers/read_tokens.hpp"
#include "../tokenizers/tokenize.hpp"
#include "wordnet.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct pair_hash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
};

std::unordered_map<std::pair<int,int>, int, pair_hash> tokindexes;

int find_layer_tokindex(int layer, int token){
  auto result = tokindexes.find(std::make_pair(layer, token));
  if(result == tokindexes.end()){
    return -1;
  }
  return result->second;
}
void set_layer_tokindex(int layer, int token, int index){
  index = std::max(0, index);
  tokindexes[std::make_pair(layer, token)] = index; 
  return;
}

void network::normalize_weights(std::vector<double> *weights) {
  double total = std::accumulate(weights->begin(), weights->end(), 0.0);

  if (total != 0.0) {
    for (double &weight : *weights) {
      weight /= total;
    }
  }
}

network::Network network::create_net(std::string filename,
                                     std::string token_filename) {

  if (!tokenizers::file_exists(filename) ||
      !tokenizers::file_exists(token_filename)) {
    std::cout << "Missing file." << std::endl;
    exit(127);
  }
  std::vector<tokenizers::token> tokens =
      tokenizers::read_tokens(token_filename);

  std::unordered_map<std::string, int>* token_map = tokenizers::tokens_to_map(tokens);
  int max_toklen = tokenizers::get_max_toklen(tokens);

  std::vector<std::string> wordlist;
  std::string wordlist_raw = tokenizers::read_wordlist(filename);
  std::string current_word;
  for (auto curr_char : wordlist_raw) {
    if (std::string{curr_char} == "\n") {
      if (current_word.size() != 0) {
        wordlist.push_back(current_word);
      }
      current_word = "";
      continue;
    }
    current_word += std::string{curr_char};
  }

  Network output;
  output.layers.push_back(new std::vector<weighted_token *>{new weighted_token{
      new tokenizers::token{0, "<BEGIN>"}, new std::vector<double>(0)}});
          set_layer_tokindex(0, 0, 0);
int wc = 0;
  for (auto word : wordlist) {
    wc++;
    if(wc % 1000 == 0){
    std::cout << word << std::endl;
    }
    std::vector<tokenizers::token> word_tokens =
        tokenizers::tokenize_string(token_map, word, max_toklen);

    while (output.layers.size() < word_tokens.size() + 5) {
      output.layers.push_back(new std::vector<weighted_token *>(0));
      for (auto layer : output.layers) {
        if (layer->size() == 0)
          continue;
        std::cout << "SIZE: " << layer->size() << (*layer)[0]->token->token;
      }
      std::cout << std::endl;
    }
    int i = 0;
    word_tokens.push_back(tokenizers::token{1, "<END>"});
    for (auto word_token : word_tokens) {
      int last_token = i == 0 ? 0 : word_tokens[i - 1].id;
      if (find_layer_tokindex(i + 1, word_token.id) == -1) {
        try {
          output.layers[i + 1]->push_back(new weighted_token{
              new tokenizers::token{word_token.id, word_token.token},
              new std::vector<double>(output.layers[i + 2]->size())});
          set_layer_tokindex(i+1, word_token.id, output.layers[i+1]->size() - 1);
        } catch (std::bad_alloc) {
          std::cout << "ERROR_badalloc [" << output.layers[i + 2]->size() << "]"
                    << std::endl;
          for (int j = 0; j < output.layers[i + 2]->size(); j++) {
            std::cout << output.layers[i + 2]->at(j)->token->token << std::endl;
          }
        }

        for (weighted_token *weighted_tok : *output.layers[i]) {
          weighted_tok->weigths_out->push_back(0);
        }
        // output.layers[i][find_layer_tokindex(output.layers[i],
        // last_token)].weigths_out.push_back(0);
      }
      output.layers[i]
          ->at(find_layer_tokindex(i, last_token))
          ->weigths_out->at(
              find_layer_tokindex(i + 1, word_token.id))++;
      i++;
    }
  }

  int min_sample_threshhold = std::min(5, (int)wordlist.size() / 1000);
  for (int i = 0; i < output.layers.size(); i++) {
    if (i == output.layers.size() - 1)
      break;
    std::vector<int> token_used_total(output.layers[i + 1]->size());
    for (int j = 0; j < output.layers[i]->size(); j++) {
      for (int k = 0; k < output.layers[i + 1]->size(); k++) {
        //std::cout << "TEST " << output.layers[i]->at(j)->weigths_out->at(k);
        token_used_total[k] += (int)output.layers[i]->at(j)->weigths_out->at(k);
      }
    }
    for (int j = 0; j < token_used_total.size(); j++) {
      if (token_used_total[j] < min_sample_threshhold) {
        //std::cout << "SMALLER THAN THRESHHOLD: " << token_used_total[j] << std::endl;
        // Remove all connections then remove the token
        for (weighted_token *tok : *output.layers[i]) {
          tok->weigths_out->erase(tok->weigths_out->begin() + j);
        }
        // Erase the token itself
        output.layers[i + 1]->erase(output.layers[i + 1]->begin() + j);
      }
    }
  }
  std::cout << "THRESHHOLD:" << min_sample_threshhold << std::endl;

  for (size_t i = 0; i < output.layers.size() - 1; ++i) {
    for (size_t j = 0; j < output.layers[i]->size(); ++j) {
      normalize_weights(output.layers[i]->at(j)->weigths_out);
    }
  }

  return output;
};
