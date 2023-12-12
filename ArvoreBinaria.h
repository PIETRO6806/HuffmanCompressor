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


    // Helper function to delete the entire binary tree
    void DeletarArvore(NoHuffman* node);

public:
    ArvoreBinaria(FilaPriorizada& fila);

    NoHuffman* getRaiz() const;

    void ConstruirArvore(FilaPriorizada& fila);

    ~ArvoreBinaria();
};


#endif //HUFFMANCOMPRESSOR_ARVOREBINARIA_H
