#include "huffman_compressor.h"
#include <chrono>

// Function to calculate character frequencies from text
unordered_map<char, int> calculateFrequencies(const string& text) {
    unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }
    return freqMap;
}

// Function to display compression statistics
void showCompressionStats(const string& original, const string& compressed) {
    int originalBits = original.length() * 8;
    int compressedBits = compressed.length();
    if (originalBits == 0) return;
    double ratio = static_cast<double>(originalBits - compressedBits) / originalBits * 100.0;

    cout << "\n=== COMPRESSION STATISTICS ===" << endl;
    cout << "Original size: " << originalBits << " bits (" << original.length() << " chars)" << endl;
    cout << "Compressed size: " << compressedBits << " bits" << endl;
    cout << "Compression ratio: " << ratio << "%" << endl;
}

int main() {
    try {
        cout << "=== HUFFMAN CODING FILE COMPRESSOR ===" << endl;
        cout << "Enter filename to compress (or 'demo' for sample text): ";
        
        string input;
        getline(cin, input);

        string original_text;
        if (input == "demo") {
            original_text = "abracadabra! huffman coding is a lossless data compression algorithm.";
        } else {
            original_text = FileHandler::readFile(input);
        }

        if (original_text.empty()) {
            cout << "Input text is empty. Nothing to compress." << endl;
            return 0;
        }

        cout << "\nOriginal text: " << original_text << endl;

        // --- COMPRESSION ---
        cout << "\n--- Compressing... ---" << endl;
        auto freqMap = calculateFrequencies(original_text);
        
        HuffmanCompressor compressor;
        compressor.buildTree(freqMap);
        string compressed_binary = compressor.compress(original_text);

        cout << "Compressed binary string: " << compressed_binary.substr(0, 100) << "..." << endl;
        
        string compressed_filename = (input == "demo" ? "demo.huf" : input + ".huf");
        FileHandler::writeBinaryFile(compressed_filename, compressed_binary, freqMap);
        cout << "Compressed file saved as: " << compressed_filename << endl;

        showCompressionStats(original_text, compressed_binary);

        // --- DECOMPRESSION ---
        cout << "\n--- Decompressing... ---" << endl;
        auto [read_binary, read_freqMap] = FileHandler::readBinaryFile(compressed_filename);

        HuffmanCompressor decompressor;
        decompressor.buildTree(read_freqMap);
        string decompressed_text = decompressor.decompress(read_binary);

        cout << "Decompressed text: " << decompressed_text << endl;

        // --- VERIFICATION ---
        cout << "\n--- Verifying Data Integrity ---" << endl;
        if (original_text == decompressed_text) {
            cout << "SUCCESS: Decompressed text matches original text. ✓" << endl;
        } else {
            cout << "FAILURE: Decompressed text does not match original. ✗" << endl;
        }

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
