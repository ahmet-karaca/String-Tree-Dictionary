//
// Created by lenovo on 28.12.2021.
//

#ifndef ASSIGNMENT4_TRIENODE_H
#define ASSIGNMENT4_TRIENODE_H

#include <vector>
#include <string>

using namespace std;

class TrieNode {
private:
    TrieNode *parent;
    vector<TrieNode*> childs;
    char letter;
    string word;

public:
    TrieNode(char letter, const string &word);

    TrieNode(TrieNode *parent, char letter, const string &word);

    TrieNode(TrieNode *parent, const vector<TrieNode *> &childs, char letter, const string &word);

    TrieNode *getParent() const;

    void setParent(TrieNode *parent);

    const vector<TrieNode *> &getChilds() const;

    void setChilds(const vector<TrieNode *> &childs);

    char getLetter() const;

    void setLetter(char letter);

    const string &getWord() const;

    void setWord(const string &word);


    static void addChild(TrieNode *node , TrieNode *newNode);

    static bool compare(TrieNode *node1, TrieNode *node2);

    TrieNode* isInTrie(char letterChar);

    void dlt();
};


#endif //ASSIGNMENT4_TRIENODE_H
