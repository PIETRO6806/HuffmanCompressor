//
// Created by Pietro on 11/12/2023.
//

#include <stdexcept>
#include "FilaPriorizada.h"

FilaPriorizada::FilaPriorizada() : quantosNos(0) {}

int FilaPriorizada::getQuantosNos() const{
    return quantosNos;
}

void FilaPriorizada::Enfileirar(const NoHuffman& novoNo) {
    filaPriorizada.push(new NoHuffman(novoNo));
    quantosNos++;
}

NoHuffman* FilaPriorizada::Retirar() {
    if (!isEmpty()) {
        NoHuffman* topNode = filaPriorizada.top();
        filaPriorizada.pop();
        quantosNos--;
        return topNode;
    }

    // Handle the case when the priority queue is empty.
    // You can throw an exception or return a special value.
    // For now, let's throw an exception.
    throw std::out_of_range("Priority queue is empty");
}

bool FilaPriorizada::isEmpty() const {
    return quantosNos == 0;
}

std::list<NoHuffman*> FilaPriorizada::Listar() const {
    std::list<NoHuffman*> lista;

    // Create a copy of the priority queue (so it doesn't modify the original)
    std::priority_queue<NoHuffman*, std::vector<NoHuffman*>, CompareNodes> tempQueue = filaPriorizada;

    while (!tempQueue.empty()) {
        lista.push_back(tempQueue.top());
        tempQueue.pop();
    }

    return lista;
}