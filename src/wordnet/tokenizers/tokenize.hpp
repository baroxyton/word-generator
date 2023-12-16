#pragma once
#include <string>
namespace tokenizers{
	constexpr int SPECIAL_TOKEN_OFFSET = 15;
	struct token{
		int tokenID;
		std::string token;	
	}
}
