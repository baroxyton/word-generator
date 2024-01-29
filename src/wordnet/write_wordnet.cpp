#include "write_wordnet.hpp"
#include "fstream"
#include "wordnet.hpp"
void network::write_net(std::string filename, Network* net) {
  std::string output = "";
  // Newline = layer separator
  // Tab = neuron separator
  // Comma = value separator
  // neuron data: token id, weight_1, ..., weight_n

  for (std::vector<weighted_token *> *tok : net->layers) {
    std::string layer_output = "";
    for (weighted_token *tok : *tok) {
      if (layer_output.size() != 0) {
        layer_output += "\t";
      }
      layer_output += std::to_string(tok->token->id);
      for (double weight : *tok->weigths_out) {
       layer_output += ",";
       layer_output += std::to_string(weight);
      }
    }
    output += layer_output;
    output += "\n";
  }
  std::ofstream net_output{};
  net_output.open(filename);
  net_output << output;
}
