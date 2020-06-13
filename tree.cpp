/*
 Filename: tree.cpp
 Description: Tree class methods
 Author: Rami Isaac
 Date: 06/12/2020
 Course: Data Structures II
*/

#include "tree.h"

/**
* Tree Constructor
* Default tree constructor, sets root to nullptr
* @param -
* @returns -
*/
Tree::Tree() {
    _root = nullptr;
}

/**
* Tree Destructor
* Clears tree _root, node destruct located in tree.h
* @param -
* @returns -
*/
Tree::~Tree() {
    _root = nullptr;
    delete _root;
}

/* Set Tree Root */

/**
* setRoot()
* Sets the _root of the huffman tree
* @param -
* @returns -
*/
void Tree::setRoot(Node* root){
    _root = root;
}

/**
* Action Handler
* Intended to implement -encode and -decode, however, -decode is not implemented in this lab,
 * though framework is there for it and I intend to complete at a later time.
 *
 * -encode builds a huffman tree as per class instructions, see comments in method for step-by-step
 * explanation of the logic for this.
 *
* @param const string& inFile, const string& outFile, const string& action
* @returns void
*/
void Tree::handleAction(const string& inFile, const string& outFile, const string& action){

    if(action == "-encode"){

        /* 1. Read File */
        string fileText = fileToString(inFile);

        /* 2. Map Frequency Table */
        map<char, size_t> frequencyTable;
        for (char ch : fileText) {
            frequencyTable[ch]++;
        }

        /* 3. Build Priority Queue of All Leaf Nodes */
        priority_queue<Node*, vector<Node*>, least> nodesQueue;
        for (auto pair : frequencyTable)
            nodesQueue.push(new Node(pair.first, pair.second, true));

        /* 4. Generate Huffman Tree */
        while (nodesQueue.size() > 1){
            Node* left = nodesQueue.top();
            nodesQueue.pop();
            Node* right = nodesQueue.top();
            nodesQueue.pop();

            size_t sum = left->_frequency + right->_frequency;

            Node* internal = new Node(sum, left, right);
            nodesQueue.push(internal); // Parent node
        }

        /* 5. Set Root */
        setRoot(nodesQueue.top());

        /* 6.0 Encoding Table: Build Encoding Map */
        // unordered_map<char, string> encodingTable;
        encode(_root, "");

        /* 6.1 Encoding Table: Build Priority Queue of Leaf Nodes */
        priority_queue<Node*, vector<Node*>, reverse> leafsQueue;
        for (auto & leaf : leafs)
            leafsQueue.push(leaf);

        /* 6.2 Encoding Table: Use Priority Leaf Queue to Print */
        cout << "Encoding Table: " << endl;
        while (!leafsQueue.empty()){
            Node* leaf = leafsQueue.top();
            if (leaf->_data == int(10)) {
                cout << "{key:" << setw(3) << "CR" << ", code: " << leaf->_code << "}" << endl;
            }else if (leaf->_data == int(13)) {
                cout << "{key:" << setw(3) << "LF" << ", code: " << leaf->_code << "}" << endl;
            } else {
                cout << "{key:" << setw(3) << leaf->_data << ", code: " << leaf->_code << "}" << endl;
            }
            leafsQueue.pop();
        }

        /* 9. Generate Binary String */
        string huffmanBinary = "";
        for (char ch : fileText) {
            huffmanBinary += encodingTable[ch];
        }

        /* 10. Print String to File */
        ofstream out(outFile);
        out << huffmanBinary; // Print encoding to file
        out.close();          // Close file
        /* This is the code I was planning to use to store tree at head of file to
         * decode for extra credit but ran out of time. Idea was to have 128 lines representing each
         * ascii code possible and then place the huff code corresponding to it on that line - or an empty string.
         * Line 129 would be the actual encoding, 'huffmanBinary' below. */

        /*string arr[128];
        for (int i = 0; i < 128; i++){
            arr[i] = "";
        } for(auto code = encodingTable.begin(); code != encodingTable.end(); ++code){
            arr[code->first] = code->second;
        } for (int i = 0; i < 128; i++){
            out << arr[i] << endl;
        }*/

    } else if (action == "-decode"){

        /*
         * For Decode, did not have enough time to complete
         */

        cout << "I ran out of time to implement -decode method" << endl;

        //        ifstream fin("output.txt", fstream::in);
        //
        //        map<string, char> codeMap;
        //
        //        for (int i = 0; i < 128; i++){
        //
        //            string code;
        //            getline(fin, code);
        //            char c = i;
        //
        //            codeMap.insert(pair < string, char > (code, i));
        //        }
    }
}

/**
* fileToString()
* Reads file, char by char, into string. Accounts for whitespaces.
* @param const string& file
* @returns A string containing contents of file
*/
string Tree::fileToString(const string& file) {
    string fileText;
    char ch;
    fstream fin(file, fstream::in);
    while (fin >> noskipws >> ch) {
        fileText += ch;
    }
    return fileText;
}

/**
* Encode()
 * Traverses tree to generate huffman codes, pushes codes to vector
 * of nodes <only> and map which is used to create the overall huffman binary string
 * written to the output file.
* @param Node* root and string to hold huffman binary sequence
* @returns Void
*/
void Tree::encode(Node* root, const string& str){
    if (root == nullptr)
        return;

    if (root->_isLeaf) {

        cout << root->_data << endl;

        /*
         * Encoding table is used to generate
         * the encoded string
         */
        encodingTable[root->_data] = str;
        cout << encodingTable[root->_data] << endl;

        /*
         * The leafs vector is used along with a
         * priority queue to print the encoding table
         * in JSON format
         */
        root->_code = str;
        cout << root->_code << endl;
        leafs.push_back(root);

    }
    encode(root->_left, str + "1");
    encode(root->_right, str + "0");
}

/* Decode Tree */
void Tree::decode(Node* root, int& index, string str){
    // Incomplete
}