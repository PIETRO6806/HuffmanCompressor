//
// Created by Pietro on 11/12/2023.
//

#include <iostream>
#include "ArvoreBinaria.h"

ArvoreBinaria::ArvoreBinaria() : raiz(nullptr) {}

ArvoreBinaria::ArvoreBinaria(FilaPriorizada& fila) {
    ConstruirArvore(fila);
}

void ArvoreBinaria::ConstruirArvore(FilaPriorizada& fila) {
    while (fila.getQuantosNos() > 1) {
        // Get the first two nodes from the priority queue
        NoHuffman* node1 = fila.Retirar();
        NoHuffman* node2 = fila.Retirar();

        // Create a new node with data as '\0' and frequency as the sum of frequencies
        NoHuffman* newNode = new NoHuffman(node1->getFrequencia() + node2->getFrequencia(), node1, node2);

        // Enqueue the new node back into the priority queue
        fila.Enfileirar(*newNode);
    }

    // The last remaining node in the priority queue is the root of the binary tree
    raiz = fila.Retirar();
}

NoHuffman* ArvoreBinaria::getRaiz() const {
    return raiz;
}

void ArvoreBinaria::DeletarArvore(NoHuffman* node) {
    if (node == nullptr) {
        return;
    }

    // Recursively delete left and right subtrees
    DeletarArvore(node->getEsquerda());
    DeletarArvore(node->getDireita());

    // Delete the current node
    delete node;
}

ArvoreBinaria::~ArvoreBinaria() {
    // Call the helper function to delete the entire binary tree
    DeletarArvore(raiz);
}

// Function to print the binary tree using in-order traversal
void ArvoreBinaria::PrintTreeHelper(const NoHuffman* node, int depth) const {
    if (node == nullptr) {
        return;
    }

    // Increase indentation based on the depth of the node
    for (int i = 0; i < depth; ++i) {
        std::cout << "      ";
    }

    // Print node information
    std::cout << "Frequency:" << node->getFrequencia() << " Data:" << node->getInfo() << std::endl;

    // Recursively print left and right subtrees
    PrintTreeHelper(node->getEsquerda(), depth + 1);
    PrintTreeHelper(node->getDireita(), depth + 1);
}

// Function to print the binary tree
void ArvoreBinaria::ImprimirArvore() const {
    std::cout << "Binary Tree:" << std::endl;
    PrintTreeHelper(raiz, 0);
    std::cout << std::endl;
}

// Helper method to get Huffman codes
void ArvoreBinaria::getCodigoHuffmanHelper(const NoHuffman* node, char character, std::string currentCode, std::string& huffmanCode) const {
    if (node != nullptr) {
        if (node->getInfo() == character && node->getEsquerda() == nullptr && node->getDireita() == nullptr) {
            huffmanCode = currentCode;
            return;
        }

        getCodigoHuffmanHelper(node->getEsquerda(), character, currentCode + "0", huffmanCode);
        getCodigoHuffmanHelper(node->getDireita(), character, currentCode + "1", huffmanCode);
    }
}

// Method to get Huffman codes
std::string ArvoreBinaria::getCodigoHuffman(char character) const {
    std::string huffmanCode;
    getCodigoHuffmanHelper(raiz, character, "", huffmanCode);
    return huffmanCode;
}