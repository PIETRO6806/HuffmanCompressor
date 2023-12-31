//
// Created by Pietro on 11/12/2023.
//

#ifndef HUFFMANCOMPRESSOR_ARVOREBINARIA_H
#define HUFFMANCOMPRESSOR_ARVOREBINARIA_H


#include "NoHuffman.h"
#include "FilaPriorizada.h"

class ArvoreBinaria {
private:
    NoHuffman* raiz; // Root of the binary tree

    // Helper function to build the binary tree from the priority queue
    void ConstruirArvore(FilaPriorizada& fila);

    // Helper function to delete the entire binary tree
    void DeletarArvore(NoHuffman* node);

    void PrintTreeHelper(const NoHuffman* node, int depth) const;

    // Add a helper method to get Huffman codes
    void getCodigoHuffmanHelper(const NoHuffman* node, char character, std::string currentCode, std::string& huffmanCode) const;


public:
    //Constructors
    ArvoreBinaria();
    ArvoreBinaria(FilaPriorizada& fila);

    NoHuffman* getRaiz() const;

    //Testes
    void ImprimirArvore() const;

    // Add the method to get Huffman codes
    std::string getCodigoHuffman(char character) const;

    //Destructor
    ~ArvoreBinaria();
};


#endif //HUFFMANCOMPRESSOR_ARVOREBINARIA_H
