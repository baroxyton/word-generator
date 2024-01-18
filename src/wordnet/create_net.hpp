#pragma once
#include "wordnet.hpp"
namespace network {
Network create_net(std::string filename, std::string token_name);
void normalize_weights(std::vector<double>& weights); 
}
