#pragma once
#include <string>
namespace tokenizers{
	constexpr int CHAR_TOKENIZER = 0;
	constexpr int MULTICHAR_TOKENIZER = 1;
	constexpr int SYLLABLE_TOKENIZER = 2;

	constexpr int SPECIAL_TOKEN_OFFSET = 15;
	struct token{
		int id;
		std::string token;	
	};
}
