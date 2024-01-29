#include "write_wordnet.hpp"
#include "create_net.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  if(argc < 2){
    std::cout << "Error: No wordlist file provided";
  }
  if(argc < 3){
    std::cout << "Error: No token file provided" << std::endl;
  }
  network::Network net = network::create_net(std::string{argv[1]}, std::string{argv[2]});
  network::write_net("wordnet.txt", &net);
}
