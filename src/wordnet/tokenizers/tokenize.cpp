#include "tokenize.hpp"
#include "write_tokens.hpp"
#include "character_tokenizer.hpp"
#include "read_file.hpp"
#include <iostream>
#include <vector>

#include <string>
int main(int argc, char *argv[]){
	if(argc == 1){
		std::cerr << "Please enter file name" << std::endl;
		exit(-1);
	}
	else if (argc == 2){
		std::cerr << "Please enter tokenizer method (1=char, 2=multichar, 3=syllable)" << std::endl;
		exit(-1);
	}
	std::string filename{argv[1]};	

	int selectedTokenizer = atoi(argv[2]);
	bool file_status = tokenizers::file_exists(filename);
	if(!file_status){
		std::cerr << "Error: file " << filename << " does not exist." << std::endl;
		exit(-1);
	}
	std::string file_contents = tokenizers::read_wordlist(filename);

	switch(selectedTokenizer){
		case 1: {
				std::cout << "Using character tokenization." << std::endl;
				auto file_tokens = tokenizers::character_tokenizer(file_contents);
				std::cout << "Saving to file to tokens.txt.." << std::endl;
				tokenizers::write_tokens(file_tokens, "tokens.txt");
				break;
			}
		case 2:{ 
			       break;
		       }
		case 3:
		       {
			       break;
		       }
		default:
		       std::cout << "Invalid option: " << selectedTokenizer << ". Please select an option 1-3.";
	}

}
