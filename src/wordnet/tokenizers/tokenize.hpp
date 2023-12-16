#include <string>
namespace tokenizers{
	constexpr int SPECIAL_TOKEN_OFFSET = 10;
	struct token{
		int tokenID;
		std::string token;	
	}
}
