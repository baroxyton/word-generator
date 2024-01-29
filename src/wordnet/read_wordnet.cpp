#include "read_wordnet.hpp"
#include "../tokenizers/read_file.hpp"
#include "wordnet.hpp"
#include <iostream>
#include <string>
#include <vector>

network::Network *network::read_net(std::string filename) {
  if (!tokenizers::file_exists(filename)) {
    std::cerr << "File does not exist" << std::endl;
    exit(1);
  }
  Network *result = new Network;
  // Parser
  // Newline: network separator
  // Tab: token separator
  // Comma: value separator

  std::string raw_network = tokenizers::read_wordlist(filename);
  std::vector<weighted_token *> *current_layer =
      new std::vector<weighted_token *>;
  weighted_token *current_token = new weighted_token{};

  int tokid = -1;
  bool in_num = false;
  std::string current_num = "";

  for (char ch : raw_network) {
    std::string chstr{ch};
    if(chstr == "," || chstr == "\t" || chstr == "\n"){
      float num = std::stof(current_num.c_str());
      if(tokid == -1){
        tokid = (int)num;
        current_token->token->id = tokid;
      }
      else{
        current_token->weigths_out->push_back(num);
      }

    }
    if (chstr == "\t" || chstr == "\n") {
      current_layer->push_back(current_token);
      current_token = new weighted_token{};
      tokid = -1;
    }
    if (chstr == "\n") {
      result->layers.push_back(current_layer);
      current_layer = new std::vector<weighted_token *>;
    }
    if(chstr == "," || chstr == "\t" || chstr == "\n"){
      continue;
    }
    current_num += chstr;
  }
  return result;
}
