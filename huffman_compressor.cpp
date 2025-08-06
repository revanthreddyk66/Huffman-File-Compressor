#include "huffman_compressor.h"
#include <fstream>
#include <bitset>

// --- HuffmanNode Implementation ---
HuffmanNode::HuffmanNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}

// --- CompareNodes Implementation ---
bool CompareNodes::operator()(HuffmanNode* a, HuffmanNode* b) {
    return a->frequency > b->frequency;
}

// --- HuffmanCompressor Implementation ---
HuffmanCompressor::HuffmanCompressor() : root(nullptr) {}

HuffmanCompressor::~HuffmanCompressor() {
    deleteTree(root);
}

void HuffmanCompressor::deleteTree(HuffmanNode* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void HuffmanCompressor::buildTree(const unordered_map<char, int>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> minHeap;

    for (const auto& pair : freqMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();

        HuffmanNode* merged = new HuffmanNode('\0', left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;
        minHeap.push(merged);
    }
    root = minHeap.top();
    generateCodes(root, "");
}

void HuffmanCompressor::generateCodes(HuffmanNode* node, const string& code) {
    if (!node) return;
    if (!node->left && !node->right) {
        huffmanCodes[node->character] = code.empty() ? "0" : code;
        return;
    }
    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

string HuffmanCompressor::compress(const string& text) {
    string compressed = "";
    for (char ch : text) {
        compressed += huffmanCodes[ch];
    }
    return compressed;
}

string HuffmanCompressor::decompress(const string& compressedText) {
    string decompressed = "";
    HuffmanNode* current = root;
    for (char bit : compressedText) {
        current = (bit == '0') ? current->left : current->right;
        if (!current->left && !current->right) {
            decompressed += current->character;
            current = root;
        }
    }
    return decompressed;
}

const unordered_map<char, string>& HuffmanCompressor::getCodes() const {
    return huffmanCodes;
}

// --- FileHandler Implementation ---
string FileHandler::readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

void FileHandler::writeBinaryFile(const string& filename, const string& binaryString, const unordered_map<char, int>& freqMap) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Cannot create binary file: " + filename);
    }

    // 1. Write frequency map (header)
    uint32_t map_size = freqMap.size();
    file.write(reinterpret_cast<const char*>(&map_size), sizeof(map_size));
    for (const auto& pair : freqMap) {
        file.write(&pair.first, sizeof(pair.first));
        file.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
    }

    // 2. Write padding info
    uint8_t padding = (8 - binaryString.length() % 8) % 8;
    file.write(reinterpret_cast<const char*>(&padding), sizeof(padding));

    // 3. Write compressed data
    for (size_t i = 0; i < binaryString.length(); i += 8) {
        string byte_string = binaryString.substr(i, 8);
        if (byte_string.length() < 8) {
            byte_string.append(8 - byte_string.length(), '0');
        }
        char byte = static_cast<char>(bitset<8>(byte_string).to_ulong());
        file.write(&byte, 1);
    }
    file.close();
}

pair<string, unordered_map<char, int>> FileHandler::readBinaryFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Cannot open binary file: " + filename);
    }

    // 1. Read frequency map
    unordered_map<char, int> freqMap;
    uint32_t map_size;
    file.read(reinterpret_cast<char*>(&map_size), sizeof(map_size));
    for (uint32_t i = 0; i < map_size; ++i) {
        char ch;
        int freq;
        file.read(&ch, sizeof(ch));
        file.read(reinterpret_cast<char*>(&freq), sizeof(freq));
        freqMap[ch] = freq;
    }

    // 2. Read padding info
    uint8_t padding;
    file.read(reinterpret_cast<char*>(&padding), sizeof(padding));

    // 3. Read compressed data
    string binaryString = "";
    char byte;
    while (file.read(&byte, 1)) {
        binaryString += bitset<8>(byte).to_string();
    }
    
    // Remove padding
    if (padding > 0) {
        binaryString.erase(binaryString.length() - padding);
    }

    file.close();
    return {binaryString, freqMap};
}
