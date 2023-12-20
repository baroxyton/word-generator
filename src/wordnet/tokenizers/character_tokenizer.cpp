#include "read_file.hpp"
#include "tokenize.hpp"
#include "character_tokenizer.hpp"
#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>

std::vector<tokenizers::token> tokenizers::character_tokenizer(std::string file_content){
	std::unordered_set<char> char_set;
	for(char file_char : file_content){
		if(char_set.find(file_char) == char_set.end()){
			char_set.insert(file_char);
		}
	}	
	std::vector<tokenizers::token> result;

	// Leave 0-15 for special tokens
	int i = SPECIAL_TOKEN_OFFSET;
	for(const auto& uniq_char: char_set){
		if(std::string{uniq_char} == "\n"){
			continue;
		}
		result.push_back(token{i, std::string{uniq_char}});
		i++;
	}
	return result;
}	
