//
// Created by Pietro on 14/12/2023.
//

#include <iostream>
#include "Huffman.h"

int main() {
    std::string inputFile, outputFile;

    // Get input file from the user
    std::cout << "Enter the input file path: ";
    std::getline(std::cin, inputFile);

    // Get output file from the user
    std::cout << "Enter the output file path: ";
    std::getline(std::cin, outputFile);

    Huffman h(inputFile, outputFile);
    h.criarFilaPriorizada();
    h.criarArvoreBinaria();
    h.calcularHuffmanCodigos();
    h.salvarCodificacao();

    std::cout << "Huffman encoding completed successfully." << std::endl;

    return 0;
}
