#include "read_file.hpp"
#include "tokenize.hpp"
#include "character_tokenizer.hpp"
#include <string>
#include <vector>
#include <unordered_set>

namespace tokenizers{
	std::vector<token> character_tokenizer(std::string file_content){
		std::unordered_set<char> char_set;
		for(char file_char : file_content){
			if(char_set.find(file_char) == char_set.end()){
				char_map.insert(file_char)
			}
			std::vector<token> result;
			// Leave 0-9 for special tokens
			int i = 10;
			for(const auto& uniq_char: char_set){
				result.push_back(token{i, std::string{unique_char}});
			}
			return result;
		}	
	}	
}
