/*
 Filename: tree.h
 Description: Declaration of the class Tree to represent the binary Huffman Tree
 Author: Rami Isaac
 Date: 06/12/2020
 Course: Data Structures II
*/

#ifndef HUFFMAN_RAMIISAAC_TREE_H
#define HUFFMAN_RAMIISAAC_TREE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <fstream>
#include <queue>
#include <iomanip>

using namespace std;

class Tree{

private:
    struct Node{
        char _data;
        size_t _frequency;
        string _code;
        bool _isLeaf;

        Node* _left = nullptr;
        Node* _right = nullptr;

        // Leaf constructor
        Node(char data, size_t frequency, bool isLeaf) :
                _data(data), _frequency(frequency),
                _left(nullptr), _right(nullptr),
                _isLeaf(isLeaf){}

        // Internal Node Constructor
        Node(size_t frequency, Node* left, Node* right) :
                _frequency(frequency),
                _left(left), _right(right),
                _isLeaf(false) {}

        ~Node() {
            delete _left;
            delete _right;
            _left = _right = nullptr;
        }
    };

    struct least{
        bool operator()(Node* l, Node* r){
            return (l->_frequency > r->_frequency || l->_frequency == r->_frequency && int(l->_data) > int(r->_data));
        }
    };

    struct reverse{
        bool operator()(Node* l, Node* r){
            return (l->_frequency < r->_frequency || l->_frequency == r->_frequency && int(l->_data) < int(r->_data));
        }
    };

    Node* _root;
    vector <Node*> leafs;
    unordered_map<char, string> encodingTable;

public:
    Tree();
    ~Tree();
    void setRoot(Node* root);

    void handleAction(const string& inFile, const string& outFile, const string& action);
    static string fileToString(const string& file);

    void decode(Node* root, int& index, string str);
    void encode(Node* root, const string& str);
};

#endif //HUFFMAN_RAMIISAAC_TREE_H