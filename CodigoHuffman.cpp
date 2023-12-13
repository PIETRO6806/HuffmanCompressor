//
// Created by Pietro on 11/12/2023.
//

#include <map>
#include "CodigoHuffman.h"

void CodigoHuffman::setCodigos(NoHuffman* node, std::string codigoAtual) {
    if (node == nullptr) {
        return;
    }

    // If the node is a leaf, set its Huffman code
    if (!node->getEsquerda() && !node->getDireita()) {
        huffmanCodes[node->getInfo()] = codigoAtual;
        return;
    }

    // Traverse left with '0'
    setCodigos(node->getEsquerda(), codigoAtual + '0');

    // Traverse right with '1'
    setCodigos(node->getDireita(), codigoAtual + '1');
}

void CodigoHuffman::calcularCodigos(const ArvoreBinaria& arvore) {
    setCodigos(arvore.getRaiz(), "");
}

std::map<char, std::string> CodigoHuffman::getHuffmanCodes() const {
    return huffmanCodes;
}