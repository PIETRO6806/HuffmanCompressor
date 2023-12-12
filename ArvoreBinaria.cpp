//
// Created by Pietro on 11/12/2023.
//

#include "ArvoreBinaria.h"

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