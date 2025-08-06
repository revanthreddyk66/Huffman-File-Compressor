# Huffman-File-Compressor
# Huffman Coding File Compressor in C++

This project is a command-line application that compresses and decompresses text files using the **Huffman coding algorithm**. It's a classic computer science project that provides a deep, practical understanding of data structures, bit manipulation, and greedy algorithms.

---

## 🚀 Core Features

* **Efficient Compression**: Achieves a compression ratio of **20%-90%** on text files by assigning variable-length codes to characters based on their frequency.
* **Data Structure Implementation**: Built from scratch using fundamental data structures:
    * **Priority Queue (Min-Heap)**: To efficiently build the Huffman tree.
    * **Binary Tree**: The Huffman tree itself, used for encoding and decoding.
    * **HashMap (`unordered_map`)**: To store character frequencies and the generated Huffman codes.
* **Lossless Decompression**: Implements a seamless decoder to perfectly reconstruct the original file, ensuring **100% data integrity**.
* **Bit-level I/O**: Writes the compressed data to a binary file one bit at a time, demonstrating an understanding of low-level data manipulation.

---

## 🛠️ Tech Stack

* **Language**: C++17
* **Core Concepts**: Greedy Algorithms, Data Structures, Bit Manipulation, Object-Oriented Programming
* **Build System**: `make`

---

## ⚙️ How to Build and Run

### Prerequisites

* A C++ compiler that supports C++17 (like `g++`).
* The `make` build automation tool.

### Build Instructions

1.  **Clone the repository:**
    ```bash
    git clone <your-repo-link>
    cd <your-repo-directory>
    ```

2.  **Build the executable:**
    ```bash
    make
    ```
    This will create an executable file named `compressor`.

### Running the Application

1.  **Run the program:**
    ```bash
    ./compressor
    ```
2.  **Follow the prompts**: You can either type the name of a text file you want to compress (e.g., `my_text_file.txt`) or type `demo` to use a built-in sample text.
3.  The program will compress the text and save the result as a new file with a `.huf` extension. It will then decompress it to verify data integrity and show you the compression statistics.
