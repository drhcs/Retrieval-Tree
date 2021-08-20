#include "Trie.h"

Trie::Trie() {
    root_ = new Node(false);
}

Trie::~Trie() {
    DeleteTrie(root_);
}

void Trie::DeleteTrie(Node * root) {

    for (int letter = 0; letter < ALPHA_SIZE; letter++)
    {
        Node * child = root->children_[letter];
        if (child != nullptr)
        {
            DeleteTrie(child);
        }
    }

    delete root;
}

std::string Trie::RemoveWord(std::string word) {

    Node * prev_end = nullptr;
    int prev_letter = 0;

    Node * itr = root_;
    for (int letter = 0, size = word.size() - 1; letter < size; letter++)
    {
        Node * child = itr->children_[word[letter]];
        if (child->end_of_word_)
        {
            prev_letter = letter + 1;
            prev_end = child;
        }
        itr = child;
    }
    itr = itr->children_[word.back()];

    bool has_prefix = prev_end != nullptr;
    bool is_prefix = HasChildren(itr);

    if (is_prefix)
    {
        itr->end_of_word_ = false;
    }
    else if (has_prefix)
    {
        RemoveWordRecursively(prev_end, word, prev_letter);
    }
    else
    {
        RemoveWordRecursively(root_, word, 0);
    }

    return word;
}

void Trie::RemoveWordRecursively(Node * root, std::string word, int letter) {

    if (letter >= word.size())
    {
        return;
    }

    Node * child = root->children_[word[letter]];
    root->children_[word[letter]] = nullptr;

    RemoveWordRecursively(child, word, letter + 1);

    delete child;
}

bool Trie::HasChildren(Node * root) {
    for (const auto & child : root->children_)
    {
        if (child != nullptr)
        {
            return true;
        }
    }
    return false;
}

void Trie::InsertWord(std::string word) {

    Node * itr = root_;

    for (const auto & letter : word)
    {
        if (itr->children_[letter] == nullptr)
        {
            itr->children_[letter] = new Node(false);
        }
        itr = itr->children_[letter];
    }

    itr->end_of_word_ = true;
}

bool Trie::IsWord(std::string word) {

    Node * itr = root_;

    for (const auto & letter : word)
    {
        if (itr->children_[letter] == nullptr)
        {
            return false;
        }
        itr = itr->children_[letter];
    }

    return itr->end_of_word_;
}

void Trie::ReadDictionaryFile(std::string file_path) {
    std::string file_contents = ReadFileToString(file_path);
    std::stringstream ss(file_contents);

    std::string line;
    while (std::getline(ss, line))
    {
        InsertWord(line);
    }
}

std::string Trie::ReadFileToString(std::string file_path) {
    std::ifstream file(file_path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

std::vector<std::string> Trie::FindAllWords() {
    std::vector<std::string> all_words;
    WordDFS(root_, "", all_words);
    return all_words;
}

void Trie::WordDFS(Node * root, std::string word, std::vector<std::string> & all_words) {

    if (root->end_of_word_)
    {
        all_words.push_back(word);
    }

    for (int letter = 0; letter < ALPHA_SIZE; letter++)
    {
        Node * child = root->children_[letter];

        if (child != nullptr)
        {
            word.push_back((char) letter);
            WordDFS(child, word, all_words);
            word.pop_back();
        }
    }
}

std::vector<std::string> Trie::StartsWithPrefix(std::string prefix) {
    std::vector<std::string> prefix_words;

    Node * itr = root_;
    for (const auto & letter : prefix)
    {
        if (itr == nullptr)
        {
            return {};
        }
        itr = itr->children_[letter];
    }

    WordDFS(itr, prefix, prefix_words);

    return prefix_words;
}
