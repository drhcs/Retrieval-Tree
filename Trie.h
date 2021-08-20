#ifndef TRIE
#define TRIE

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#define ALPHA_SIZE 256

struct Node {

    bool end_of_word_;
    std::vector<Node *> children_;

    explicit Node(bool end_of_word) {
        end_of_word_ = end_of_word;
        children_ = std::vector<Node *>(ALPHA_SIZE, nullptr);
    }

};

class Trie {

    Node * root_;

    void DeleteTrie(Node * root);
    std::string ReadFileToString(std::string file_path);
    void WordDFS(Node * root, std::string word, std::vector<std::string> & all_words);
    void RemoveWordRecursively(Node * root, std::string word, int letter);
    bool HasChildren(Node * root);

public:

    Trie();
    ~Trie();

    std::string RemoveWord(std::string word);
    void InsertWord(std::string word);
    bool IsWord(std::string word);

    void ReadDictionaryFile(std::string file_path);

    std::vector<std::string> FindAllWords();
    std::vector<std::string> StartsWithPrefix(std::string prefix);
};

#endif
