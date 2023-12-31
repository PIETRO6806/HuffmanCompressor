#include <iostream>
#include <map>
#include "Huffman.h"

int main() {
    Huffman huffman(R"(C:\Users\Pietro\Desktop\testes\Bloxstrap.exe)", R"(C:\Users\Pietro\Desktop\testes\Bloxstrap.pietro)");

    // Create the priority queue
    huffman.criarFilaPriorizada();

    // Get the frequencies vector
    //std::vector<std::pair<char, unsigned>> frequencies = huffman.getFrequencies();

    // Print the frequencies vector
    /*std::cout << "Frequencies:\n";
    for (const auto& pair : frequencies) {
        std::cout << "Character: " << pair.first << " Frequency: " << pair.second << std::endl;
    }*/

    //huffman.getFilaPriorizada().ImprimirFilaPriorizada();

    // Create the Huffman tree
    huffman.criarArvoreBinaria();

    // Print the Huffman tree
    //huffman.getArvoreBinaria().ImprimirArvore();


    // Calculate Huffman codes
    huffman.calcularHuffmanCodigos();

    // Access the Huffman codes
    /*std::map<char, std::string> huffmanCodes = huffman.getCodigoHuffman().getHuffmanCodes();

    // Print the codes
    for (const auto& pair : huffmanCodes) {
        std::cout << "Character: " << pair.first << ", Code: " << pair.second << std::endl;
    }*/

    huffman.salvarCodificacao();

    return 0;
}