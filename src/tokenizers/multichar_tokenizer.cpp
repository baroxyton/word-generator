#include "multichar_tokenizer.hpp"
#include "tokenize.hpp"
#include <vector>
#include <unordered_map>
#include <boost/algorithm/string.hpp>

std::vector<tokenizers::token> tokenizers::multichar_tokenizer(std::string &file_content)
{
	int TOKEN_COUNT_THRESHHOLD = 50;
	std::unordered_map<std::string, int> tokens;
	std::vector<std::string> current_strings(MULTICHAR_COUNT);
	for (int i = 0; i < file_content.size(); i++)
	{
		for (int j = 0; j < MULTICHAR_COUNT; j++)
		{
			if (i + j >= file_content.size())
			{
				break;
			}
			current_strings[j] += std::string{file_content[i + j]};
			if (current_strings[j].size() - 1 == j)
			{
				if (!boost::algorithm::contains(current_strings[j], "\n"))
				{
					if(tokens.find(current_strings[j]) == tokens.end()){
						tokens[current_strings[j]] = 0;
					}
					tokens[current_strings[j]]++;
					current_strings[j] = "";
				}
				else
				{
					std::vector<std::string> split_string;
					boost::split(split_string, current_strings[j], boost::is_any_of("\n"));
					current_strings[j] = split_string[split_string.size() - 1];
				}
			}
		}
	}
	std::vector<token> result;
	int tokenid = SPECIAL_TOKEN_OFFSET;
	for (auto &curr_token : tokens)
	{
		auto content = curr_token.first;
		int count = curr_token.second;

		if (content.size() == 1 || count >= TOKEN_COUNT_THRESHHOLD)
		{
			result.push_back(token{tokenid, content});
			tokenid++;
		}
	}
	return result;
}
