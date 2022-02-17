//
// Created by lenovo on 28.12.2021.
//

#include <iostream>
#include <algorithm>

using namespace std;

#include "TrieNode.h"

TrieNode::TrieNode(char letter, const string &word) : letter(letter), word(word) {}

TrieNode::TrieNode(TrieNode *parent, char letter, const string &word) : parent(parent), letter(letter), word(word) {}

TrieNode::TrieNode(TrieNode *parent, const vector<TrieNode *> &childs, char letter, const string &word) : parent(parent), childs(childs), letter(letter), word(word) {}

TrieNode *TrieNode::getParent() const {
    return parent;
}

void TrieNode::setParent(TrieNode *parent) {
    TrieNode::parent = parent;
}

const vector<TrieNode *> &TrieNode::getChilds() const {
    return childs;
}

void TrieNode::setChilds(const vector<TrieNode *> &childs) {
    TrieNode::childs = childs;
}

char TrieNode::getLetter() const {
    return letter;
}

void TrieNode::setLetter(char letter) {
    TrieNode::letter = letter;
}

const string &TrieNode::getWord() const {
    return word;
}

void TrieNode::setWord(const string &word) {
    TrieNode::word = word;
}


void TrieNode::addChild(TrieNode *node , TrieNode *newNode) {
    vector<TrieNode*> childsVector;
    childsVector = node->getChilds();
    childsVector.push_back(newNode);
    sort(childsVector.begin(),childsVector.end(), compare);
    node->setChilds(childsVector);
    newNode->setParent(node);
}

TrieNode *TrieNode::isInTrie(char letterChar) {
    for (int i = 0; i < childs.size(); ++i) {
        if (childs[i]->getLetter() == letterChar){
            // buldu
            return childs[i];
        }
    }
    // bulamadi
    return NULL;
}

void TrieNode::dlt() {
    vector<TrieNode*> childsCopy = parent->getChilds();
    for (int i = 0; i < childsCopy.size(); ++i) {
        if (childsCopy[i]->getLetter() == letter){
            // child bulundu
            childsCopy.erase(childsCopy.begin() + i);
            parent->setChilds(childsCopy);
            break;
        }
    }
}

bool TrieNode::compare(TrieNode *node1, TrieNode *node2) {
    // child node larini siralamak icin kullanildi
    return (node1->getLetter() < node2->getLetter());
}
