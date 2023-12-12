//
// Created by Pietro on 11/12/2023.
//

#ifndef HUFFMANCOMPRESSOR_FILAPRIORIZADA_H
#define HUFFMANCOMPRESSOR_FILAPRIORIZADA_H


#include <vector>
#include <queue>
#include <list>
#include "NoHuffman.h"

class FilaPriorizada {
private:
    int quantosNos;

    // Change the comparison operator for the min heap
    struct CompareNodes {
        bool operator()(const NoHuffman* lhs, const NoHuffman* rhs) const {
            return *lhs > *rhs;  // get the pointers values and use the greater-than operator for min heap
        }
    };

    std::priority_queue<NoHuffman*, std::vector<NoHuffman*>, CompareNodes> filaPriorizada;

public:
    //default constructor
    FilaPriorizada();

    int getQuantosNos() const;
    std::list<NoHuffman*> Listar() const;

    void Enfileirar(const NoHuffman&);
    NoHuffman* Retirar();
    bool isEmpty() const;
};


#endif //HUFFMANCOMPRESSOR_FILAPRIORIZADA_H
