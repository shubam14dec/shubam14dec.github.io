#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node {
    public:
        vector<Node*> links;
        bool isEndOfWord;
        Node() {
            isEndOfWord = false;
            links.resize(26, nullptr);
        }
};

class Trie {
    Node *root;
    public:
        Trie() {
            root = new Node();
        }

        void addWord(string word) {
            Node *current = root;
            for (char c : word) {
                if (current->links[c - 'a'] == nullptr) {
                    current->links[c - 'a'] = new Node();
                }
                current = current->links[c - 'a'];
            }
            current->isEndOfWord = true;
        }

        bool findWord(string word) {
            Node *current = root;
            for (char c : word) {
                if (current->links[c - 'a'] == nullptr) {
                    return false;
                }
                current = current->links[c - 'a'];
            }
            return current->isEndOfWord;
        }
};

int main() {
    Trie trie;
    trie.addWord("hello");
    trie.addWord("helium");

    cout << trie.findWord("hello") << endl; // should return true
    cout << trie.findWord("helix") << endl; // should return false
    cout << trie.findWord("helium") << endl; // should return true
    cout << trie.findWord("hero") << endl; // should return false

    return 0;
}
