#include <iostream>
#include "Huffman.h"
  \
int main() {
    Huffman huffman(R"(C:\Users\Pietro\Desktop\HuffmanCompressor\png.png)", "output.txt");

    try {
        huffman.criarFilaPriorizada();

        // List and print elements in filaPriorizada
        std::list<NoHuffman*> elements = huffman.getFilaPriorizada().Listar();
        for (const auto& node : elements) {
            std::cout << "Character: " << node->getInfo() << ", Frequency: " << node->getFrequencia() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}