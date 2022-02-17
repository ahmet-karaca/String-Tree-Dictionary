#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "TrieNode.h"

using namespace std;

void insert(TrieNode *trie, const vector<string>& elements, ofstream *outputFile);
TrieNode *search(TrieNode *trie, string str, ofstream *outputFile, string *outputStr, bool isSearch);
void dlt(TrieNode *trie, string str, ofstream *outputFile);
void list(TrieNode *trie, ofstream *outputFile);
void print2(TrieNode *trie, ofstream *outputFile, string *str);

vector<string> split(const string& text);

int main(int argc, char** argv) {
    // alinan input dosyasi
    ifstream inputFile;
    inputFile.open(argv[1]);

    string line;

    // input satirlarini depolayan vector
    vector<string> inputFileVector;

    while (getline(inputFile, line)){
        inputFileVector.push_back(line);
    }

    inputFile.close();

    // alinan output dosyasi
    ofstream outputFile;
    outputFile.open(argv[2]);

    // root ile trie olusturma
    TrieNode *trie = new TrieNode(NULL, '.', "Root");

    for (int i = 0; i < inputFileVector.size(); ++i) {
        if (inputFileVector[i][0] == 'i'){
            // insert var
            int acParantez = inputFileVector[i].find("(",0);
            int kapaParantez = inputFileVector[i].find(")",0);
            string wordStr = inputFileVector[i].substr(acParantez+1,(kapaParantez-(acParantez+1)));
            vector<string> elements = split(wordStr);
            insert(trie, elements, &outputFile);
        }
        else if (inputFileVector[i][0] == 's'){
            // search var
            int acParantez = inputFileVector[i].find("(",0);
            int kapaParantez = inputFileVector[i].find(")",0);
            string wordStr = inputFileVector[i].substr(acParantez+1,(kapaParantez-(acParantez+1)));
            string tempStr;
            search(trie, wordStr, &outputFile, &tempStr, true);
        }
        else if (inputFileVector[i][0] == 'l'){
            // list var
            list(trie, &outputFile);
        }
        else if (inputFileVector[i][0] == 'd'){
            // delete var
            int acParantez = inputFileVector[i].find("(",0);
            int kapaParantez = inputFileVector[i].find(")",0);
            string wordStr = inputFileVector[i].substr(acParantez+1,(kapaParantez-(acParantez+1)));
            dlt(trie, wordStr, &outputFile);
        }
    }
    outputFile.close();
    return 0;
}

void insert(TrieNode *trie, const vector<string>& elements, ofstream *outputFile){
    TrieNode *trie2 = trie;

    for (int i = 0; i < elements[0].size(); ++i) {
        TrieNode *trie3 = trie2->isInTrie(elements[0][i]);

        if (trie3 == NULL){
            // null yani bu char bu trie nin child larinda yok

            TrieNode *childNode = new TrieNode(elements[0][i],"NULL");
            TrieNode::addChild(trie2, childNode);
            trie2 = childNode;
        }
        else{
            // herhangi bir ekleme yok, sonraki node a gecildi
            trie2 = trie3;
        }
    }
    if (trie2->getWord() == "NULL"){
        // word eklemesi yapiliyor
        trie2->setWord(elements[1]);
        *outputFile << "\"" << elements[0] << "\"" << " was added" << endl;
    }
    else if(trie2->getWord() != elements[1]){
        // word guncellemesi yapiliyor
        trie2->setWord(elements[1]);
        *outputFile << "\"" << elements[0] << "\"" << " was updated" << endl;
    }
    else if(trie2->getWord() == elements[1]){
        // ayni word, herhangi bir sey yapma
        *outputFile << "\"" << elements[0] << "\"" << " already exist" << endl;
    }
}

TrieNode *search(TrieNode *trie, string str, ofstream *outputFile, string *outputStr, bool isSearch){
    TrieNode *node = trie;
    bool isExist = true;
    int counter = 0;
    for (int i = 0; i < str.size(); ++i){
        node = node->isInTrie(str[i]);
        if(node == NULL){
            // eslesme olmadi
            isExist = false;
            break;
        }
        else{
            counter++;
        }
    }
    if (isExist){
        if (node->getWord() == "NULL"){
            *outputStr += "\"";
            *outputStr += "not enough Dothraki word";
            *outputStr += "\"";
            node = NULL;
        }
        else{
            *outputStr += "\"";
            *outputStr += "The English equivalent is ";
            *outputStr += node->getWord();
            *outputStr += "\"";
        }

    }
    if (counter == 0){
        // ilk harf bile yok
        *outputStr += "\"";
        *outputStr += "no record";
        *outputStr += "\"";
        node = NULL;
    }
    else if(counter < str.size()){
        // kelimenin sonuna kadar gidemedik
        *outputStr += "\"";
        *outputStr += "incorrect Dothraki word";
        *outputStr += "\"";
        node = NULL;
    }
    if (isSearch){
        *outputFile << *outputStr << endl;
    }
    return node;
}


void dlt(TrieNode *trie, string str, ofstream *outputFile){
    string searchStr;
    TrieNode *node = search(trie, str, outputFile, &searchStr, false);

    if (node == NULL){
        // aranan trie de yok
        *outputFile << searchStr << endl;
    }
    else{
        node->setWord("NULL");
        TrieNode *parentNode = node->getParent();
        while(node->getParent() != NULL){
            if (node->getChilds().size() == 0){
                // bu node un cocugu yok
                // bu node silinebilir
                node->dlt();
            }
            else{
                // bu node un cocugu var
                // silme yapilmayacak
                break;
            }

            node = parentNode;
            parentNode = node->getParent();
        }
        *outputFile << "\"" << str << "\"" << " deletion is successful" << endl;
    }
}

vector<string> split(const string& text){
    vector<string> elemanlar;
    string strToken;

    stringstream ss(text);
    while(getline(ss, strToken, ',')){
        elemanlar.push_back(strToken);
    }
    return elemanlar;
}

void list(TrieNode *trie, ofstream *outputFile){
    TrieNode *node = trie;
    for (int i = 0; i < trie->getChilds().size(); ++i) {
        string str = "-";
        node = trie->getChilds()[i];
        bool finisher = false;
        bool isContinue = false;
        while(!finisher){
            str += node->getLetter();

            // bu olmayabilir

            /*if ((node->getWord() != "NULL") & (node->getChilds().size() != 0)){
                cout << "kelime bulundu" << endl;
                cout << node->getLetter() << "-" << node->getWord() << endl;
                *outputFile << str << "(" << node->getWord() << ")" << endl;
            }*/

            if (node->getChilds().size() == 0){
                // finisher true yapiliyor
                finisher = true;
            }
            else if(node->getChilds().size() > 1){
                // finisher ve isContinue true yapiliyor
                finisher = true;
                isContinue = true;
            }
            else{
                node = node->getChilds()[0];
            }
        }
        if (isContinue){
            if (node->getWord() != "NULL"){
                *outputFile << str << "(" << node->getWord() << ")" << endl;
            }
            else{
                *outputFile << str << endl;
            }
            string str2 = "\t";
            str2 += str;
            print2(node,outputFile,&str2);
        }
        else{
            if (node->getWord() != "NULL"){
                *outputFile << str << "(" << node->getWord() << ")" << endl;
            }
            else{
                *outputFile << str << endl;
            }
        }
    }
}

void print2(TrieNode *trie, ofstream *outputFile, string *str){
    for (int i = 0; i < trie->getChilds().size(); ++i) {
        TrieNode *trie2 = trie->getChilds()[i];
        string str2 = *str;
        bool finisher = false;
        bool isContinue = false;
        while(!finisher){
            str2 += trie2->getLetter();
            if ((trie2->getWord() != "NULL") & (trie2->getChilds().size() != 0) & (str2 != *str)){
                // kelime bulundu
                *outputFile << str2 << "(" << trie2->getWord() << ")" << endl;
            }

            if (trie2->getChilds().size() == 0){
                // 0 cocuk
                finisher = true;
            }
            else if(trie2->getChilds().size() > 1){
                // 1 den fazla cocuk
                finisher = true;
                isContinue = true;
                if (trie2->getWord() != "NULL"){
                    *outputFile << str2 << "(" << trie2->getWord() << ")" << endl;
                }
                else{
                    *outputFile << str2 << endl;
                }
                string str3 = "\t";
                str3 += str2;
                print2(trie2,outputFile,&str3);
            }
            else{
                trie2 = trie2->getChilds()[0];
            }
        }

        if (!isContinue){
            *outputFile << str2 << "(" << trie2->getWord() << ")" << endl;
        }
    }
}