#include "read_tokens.hpp"
#include "tokenize.hpp"
#include "read_file.hpp"
#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>

std::unordered_set<std::string> integers{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
std::vector<tokenizers::token> tokenizers::read_tokens(std::string filename)
{
  if (!file_exists(filename))
  {
    std::cerr << "Error: filename doesn't exist." << std::endl;
    exit(-1);
  }
  std::string file_content = read_wordlist(filename);
  std::vector<token> result;

  bool in_tokenid = true;
  bool in_token = false;
  std::string token_content = "";
  std::string token_id = "";

  for(int i = 0; i < file_content.size(); i++){
    auto currentstr = std::string{file_content[i]};
    int id;
    if(in_tokenid && integers.find(currentstr) != integers.end()){
      token_id += currentstr;
    }
    else if (in_tokenid){
      // End of token id
      id = atoi(token_id.c_str());
      in_tokenid = false;
      token_id = "";
      in_token = true;
      continue;
    }
    if(in_token && (currentstr == "\n" || i == file_content.size() - 1)){
      in_token = false;
      in_tokenid = true;
      result.push_back(token{id, token_content});
      token_content = "";
      continue;
    }
    if(in_token){
      token_content += currentstr;
    }


  } 
  return result;
}

