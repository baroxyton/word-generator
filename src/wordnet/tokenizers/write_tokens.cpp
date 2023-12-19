#include "tokenize.hpp"
#include "write_tokens.hpp"
#include <fstream>

void tokenizers::write_tokens(std::vector<token> tokens, std::string filename="tokens.txt"){
	std::string result;
	for(const token& curr_token : tokens){
		result += curr_token.id + "\t" + curr_token.token + "\n";		
	}
	std::ofstream token_output;
	token_output.open(filename);
	token_output << result;
	token_output.close();
	return;
}
