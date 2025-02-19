# Wordkit
Generate & analyze words based on a word list or text

# Installation
```bash
git clone https://github.com/baroxyton/word-generator &&
cd word-generator &&
mkdir -p build &&
make
```
# Usage Examples

## Generating fictional german words
1. generate word list of 10'000 words: `curl https://raw.githubusercontent.com/enz/german-wordlist/refs/heads/main/words | shuf -n 10000 > words.txt`
2. generate tokens for word list: `./build/tokenizer words.txt 2`
3. generate word model: `./build/create_net words.txt tokens.txt`
4. generate 10 words: `./build/generate_word wordnet.txt tokens.txt`

sample output:

```
Word generated: adarkenniver
Word generated: zubstikonbare
Word generated: Biomente
Word generated: xynthet
Word generated: Schorchzen
Word generated: einklattegigeremin
Word generated: flockswerenal
Word generated: spejekt
Word generated: küfteblenze
Word generated: Lärktivierens
```
