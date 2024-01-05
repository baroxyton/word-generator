#include "create_net.hpp"
#include "wordnet.hpp"
#include <iostream>
int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Please enter a filename." << std::endl;
    return 1;
  }
  network::Network net =
      network::create_net(std::string{argv[1]}, std::string{argv[2]});
  for (auto layer : net.layers) {
    std::cout << "BEGIN WEIGHT" << std::endl;
    for(auto weighted_tok : layer){
      std::cout << weighted_tok.token.token << std::endl;
    }
  }

  return 0;
}
