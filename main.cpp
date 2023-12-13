#include <iostream>
#include <map>
#include "Huffman.h"

int main() {
    Huffman huffman(R"(C:\Users\Pietro\Desktop\HuffmanCompressor\txt.txt)", R"(C:\Users\Pietro\Desktop\HuffmanCompressor\txt2.txt)");

    // Create the priority queue
    huffman.criarFilaPriorizada();

    huffman.getFilaPriorizada().ImprimirFilaPriorizada();

    // Create the Huffman tree
    huffman.criarArvoreBinaria();

    // Print the Huffman tree
    huffman.getArvoreBinaria().ImprimirArvore();


    // Calculate Huffman codes
    huffman.calcularHuffmanCodigos();

    // Access the Huffman codes
    std::map<char, std::string> huffmanCodes = huffman.getCodigoHuffman().getHuffmanCodes();

    // Print the codes
    for (const auto& pair : huffmanCodes) {
        std::cout << "Character: " << pair.first << ", Code: " << pair.second << std::endl;
    }

    //huffman.salvarCodificacao();


    return 0;
}