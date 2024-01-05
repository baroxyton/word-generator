#include "create_net.hpp"
#include "../tokenizers/read_file.hpp"
#include "../tokenizers/read_tokens.hpp"
#include "../tokenizers/tokenize.hpp"
#include "wordnet.hpp"
#include <string>
#include <vector>

network::Network network::create_net(std::string filename,
                                     std::string token_filename) {
  if (!tokenizers::file_exists(filename) ||
      !tokenizers::file_exists(token_filename)) {
    exit(127);
  }
  std::vector<tokenizers::token> tokens =
      tokenizers::read_tokens(token_filename);
  std::vector<std::string> wordlist;
  std::string wordlist_raw = tokenizers::read_wordlist(filename);
  std::string current_word;
  for (auto curr_char : wordlist_raw) {
    if (std::string{curr_char} == "\n") {
      wordlist.push_back(current_word);
      current_word = "";
      continue;
    }
    current_word += std::string{curr_char};
  }

  Network output;
  output.layers.push_back(std::vector<weighted_token>{
      weighted_token{tokenizers::token{0, "<BEGIN>"}, std::vector<double>{}}});

  for (auto word : wordlist) {
    std::vector<tokenizers::token> word_tokens =
        tokenizers::tokenize_string(tokens, word);

    while (output.layers.size() < word_tokens.size() + 2) {
      output.layers.push_back(std::vector<weighted_token>{});
    }
    int i = 0;
    word_tokens.push_back(tokenizers::token{1, "<END>"}); 
    for (auto word_token : word_tokens) {
      int last_token = i==0 ? 0 : word_tokens[i-1].id;
      if(find_layer_tokindex(output.layers[i+1], word_token.id) == -1){
        output.layers[i+1].push_back(weighted_token{word_token, std::vector<double>(output.layers[i+2].size())});

        for(weighted_token& weighted_tok : output.layers[i]){
          weighted_tok.weigths_out.push_back(0);
        }
        //output.layers[i][find_layer_tokindex(output.layers[i], last_token)].weigths_out.push_back(0);
      }
     output.layers[i][find_layer_tokindex(output.layers[i], last_token)].weigths_out[find_layer_tokindex(output.layers[i+1], word_token.id)]++;
      i++;
    }
  }
  return output;
};
