#ifndef HUFFMAN_COMPRESSOR_H
#define HUFFMAN_COMPRESSOR_H

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

// Node structure for the Huffman Tree
struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char ch, int freq);
};

// Comparator for the Priority Queue (Min-Heap)
struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b);
};

// Main class for handling compression and decompression
class HuffmanCompressor {
private:
    HuffmanNode* root;
    unordered_map<char, string> huffmanCodes;

    void generateCodes(HuffmanNode* node, const string& code);
    void deleteTree(HuffmanNode* node);

public:
    HuffmanCompressor();
    ~HuffmanCompressor();

    void buildTree(const unordered_map<char, int>& freqMap);
    string compress(const string& text);
    string decompress(const string& compressedText);
    const unordered_map<char, string>& getCodes() const;
};

// Class for handling file input/output
class FileHandler {
public:
    static string readFile(const string& filename);
    static void writeBinaryFile(const string& filename, const string& binaryString, const unordered_map<char, int>& freqMap);
    static pair<string, unordered_map<char, int>> readBinaryFile(const string& filename);
};

#endif // HUFFMAN_COMPRESSOR_H
