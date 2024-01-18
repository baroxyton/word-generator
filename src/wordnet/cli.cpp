#include "create_net.hpp"
#include <numeric>
#include "wordnet.hpp"
#include <iostream>
#include <cstdlib> // for rand and srand
#include <ctime>   // for time

// Function to choose a random index based on weights
size_t choose_random_index(const std::vector<double>& weights) {
    double random_value = (rand() / (RAND_MAX + 1.0)) * std::accumulate(weights.begin(), weights.end(), 0.0);
    double cumulative = 0.0;

    for (size_t i = 0; i < weights.size(); ++i) {
        cumulative += weights[i];
        if (random_value < cumulative) {
            return i;
        }
    }

    return weights.size() - 1;
}

// Function for generating a fake word
std::string generate_fake_word(const network::Network& net) {
    std::string fake_word = "";
    size_t current_layer = 0;
    size_t current_token = 0;

    while (current_token != 1) { // Continue until END token is reached
        const auto& current_weighted_token = net.layers[current_layer][current_token];
        fake_word += current_weighted_token.token.token;
        
        // Choose the next token based on out_weights
        current_token = choose_random_index(current_weighted_token.weigths_out);
        current_layer++;
    }

    return fake_word;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Please enter a filename." << std::endl;
        return 1;
    }

    // Seed for random number generation
    srand(time(nullptr));

    network::Network net = network::create_net(std::string{argv[1]}, std::string{argv[2]});

    // Display BEGIN weights (for illustration)
    std::cout << "BEGIN WEIGHTS" << std::endl;
    for (const auto& weighted_tok : net.layers[0]) {
        std::cout << weighted_tok.token.token << std::endl;
    }

    // Generate a fake word
    std::string fake_word = generate_fake_word(net);

    // Display the generated fake word
    std::cout << "Generated Fake Word: " << fake_word << std::endl;

    return 0;
}

