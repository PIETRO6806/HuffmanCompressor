#include <iostream>
#include "Huffman.h"

int main() {
    Huffman huffman(R"(C:\Users\Pietro\Desktop\HuffmanCompressor\txt.txt)", "output.txt");

    // Create the priority queue
    huffman.criarFilaPriorizada();

    huffman.getFilaPriorizada().ImprimirFilaPriorizada();

    // Create the Huffman tree
    huffman.criarArvoreBinaria();

    // Print the Huffman tree
    huffman.getArvoreBinaria().ImprimirArvore();


    // Calculate Huffman codes
    huffman.calcularHuffmanCodigos();


    return 0;
}