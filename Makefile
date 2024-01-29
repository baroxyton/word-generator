# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -O3

# Source files for build/tokenizer
TOKENIZER_SRC = src/tokenizers/read_file.cpp src/tokenizers/write_tokens.cpp src/tokenizers/tokenize.cpp src/tokenizers/syllable_tokenizer.cpp src/tokenizers/character_tokenizer.cpp src/tokenizers/multichar_tokenizer.cpp src/tokenizers/cli.cpp

# Output binary for build/tokenizer
TOKENIZER_BIN = build/tokenizer

CREATE_NET_SRC = ./src/tokenizers/read_file.cpp ./src/tokenizers/tokenize.cpp ./src/tokenizers/read_tokens.cpp ./src/wordnet/create_net.cpp ./src/wordnet/wordnet.cpp ./src/wordnet/write_wordnet.cpp ./src/wordnet/create_net_cli.cpp

CREATE_NET_BIN = build/create_net


.PHONY: all
all: $(TOKENIZER_BIN) $(CREATE_NET_BIN)

$(TOKENIZER_BIN): $(TOKENIZER_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(CREATE_NET_BIN): $(CREATE_NET_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@



.PHONY: clean
clean:
	rm $(TOKENIZER_BIN) $(CREATE_NET_BIN)

