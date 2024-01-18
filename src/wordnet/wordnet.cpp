#include "wordnet.hpp"
int network::find_layer_tokindex(std::vector<network::weighted_token*>* layer,
                                 int tokenid) {
  int result = -1;
  for (int i = 0; i < layer->size(); i++) {
    weighted_token* tok = (*layer)[i];
    bool is_id = tok->token->id == tokenid;
    if (is_id) {
      result = i;
      return result;
    }
  }
  return result;
}
