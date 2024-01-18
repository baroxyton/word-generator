#include "create_net.hpp"
#include <iostream>
#include "../tokenizers/read_file.hpp"
#include "../tokenizers/read_tokens.hpp"
#include "../tokenizers/tokenize.hpp"
#include "wordnet.hpp"
#include <string>
#include <vector>
#include <numeric>

void network::normalize_weights(std::vector<double>& weights) {
    double total = std::accumulate(weights.begin(), weights.end(), 0.0);

    if (total != 0.0) {
        for (double& weight : weights) {
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
  std::vector<std::string> wordlist;
  std::string wordlist_raw = tokenizers::read_wordlist(filename);
  std::string current_word;
  for (auto curr_char : wordlist_raw) {
    if (std::string{curr_char} == "\n") {
      if(current_word.size() != 0){
      wordlist.push_back(current_word);
      }
      current_word = "";
      continue;
    }
    current_word += std::string{curr_char};
  }

  Network output;
  output.layers.push_back(std::vector<weighted_token>{
      weighted_token{tokenizers::token{0, "<BEGIN>"}, std::vector<double>(0)}});
  
  for (auto word : wordlist) {
    std::cout << word << std::endl;
    std::vector<tokenizers::token> word_tokens =
        tokenizers::tokenize_string(tokens, word);

    while (output.layers.size() < word_tokens.size() + 2) {
      output.layers.push_back(std::vector<weighted_token>(0));
      for(auto layer : output.layers){
        if(layer.size() == 0) continue;
        std::cout << "SIZE: " << layer.size() << layer[0].token.token;
      }
      std::cout << std::endl;
    }
    int i = 0;
    word_tokens.push_back(tokenizers::token{1, "<END>"}); 
    for (auto word_token : word_tokens) {
      int last_token = i==0 ? 0 : word_tokens[i-1].id;
      if(find_layer_tokindex(output.layers[i+1], word_token.id) == -1){
        try{
        output.layers[i+1].push_back(weighted_token{word_token, std::vector<double>(std::min<int>(10000,output.layers[i+2].size()))});
        }
        catch(std::bad_alloc){
          std::cout << "ERROR_badalloc [" << output.layers[i+2].size() <<  "]" << std::endl;
          for(int j = 0; j <  output.layers[i+2].size(); j++){
            std::cout << output.layers[i+2][j].token.token << std::endl;
          }
        }
        
        catch(std::length_error err){
          std::cout << "ERROR_len [" << std::min<int>(10000, (uint)output.layers[i+2].size()) << "]" << std::endl;
        }

        for(weighted_token& weighted_tok : output.layers[i]){
          weighted_tok.weigths_out.push_back(0);
        }
        //output.layers[i][find_layer_tokindex(output.layers[i], last_token)].weigths_out.push_back(0);
      }
     output.layers[i][find_layer_tokindex(output.layers[i], last_token)].weigths_out[find_layer_tokindex(output.layers[i+1], word_token.id)]++;
      i++;
    }
  }
  for (size_t i = 0; i < output.layers.size() - 1; ++i) {
        for (size_t j = 0; j < output.layers[i].size(); ++j) {
            normalize_weights(output.layers[i][j].weigths_out);
        }
    }

  return output;
};
