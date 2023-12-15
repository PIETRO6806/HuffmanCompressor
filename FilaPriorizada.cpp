//
// Created by Pietro on 11/12/2023.
//

#include <stdexcept>
#include <iostream>
#include "FilaPriorizada.h"

FilaPriorizada::FilaPriorizada() : quantosNos(0) {}

int FilaPriorizada::getQuantosNos() const{
    return quantosNos;
}

void FilaPriorizada::Enfileirar(const NoHuffman& novoNo) {
    // Create a copy of the NoHuffman object to avoid memory issues
    NoHuffman* newNode = new NoHuffman(novoNo);

    // Add the new node to the priority queue
    filaPriorizada.push(newNode);

    // Increment the count of nodes
    quantosNos++;
}

NoHuffman* FilaPriorizada::Retirar() {
    if (!isEmpty()) {
        NoHuffman* topNode = filaPriorizada.top();
        filaPriorizada.pop();
        quantosNos--;
        return topNode;
    }
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

void FilaPriorizada::ImprimirFilaPriorizada() const {
    // Create a copy of the priority queue (so it doesn't modify the original)
    std::priority_queue<NoHuffman*, std::vector<NoHuffman*>, CompareNodes> tempQueue = filaPriorizada;

    std::cout << "Fila Priorizada:\n";

    while (!tempQueue.empty()) {
        NoHuffman* node = tempQueue.top();
        std::cout << "Frequencia: " << node->getFrequencia()
                  << " | Info: " << node->getInfo() << "\n";
        tempQueue.pop();
    }

    std::cout << "Fim da Fila Priorizada\n";
}

FilaPriorizada::~FilaPriorizada() {
    while (!filaPriorizada.empty()) {
        delete filaPriorizada.top();
        filaPriorizada.pop();
    }
}

// Copy constructor
FilaPriorizada::FilaPriorizada(const FilaPriorizada& other) : quantosNos(other.quantosNos) {

    // Copy priority queue
    std::priority_queue<NoHuffman*, std::vector<NoHuffman*>, CompareNodes> tempQueue = other.filaPriorizada;

    while (!tempQueue.empty()) {
        NoHuffman* node = tempQueue.top();
        this->filaPriorizada.push(new NoHuffman(*node));  // Create a copy of NoHuffman and push it to the new queue
        tempQueue.pop();
    }
}

// Assignment operator
FilaPriorizada& FilaPriorizada::operator=(const FilaPriorizada& other) {
    if (this != &other) {
        // Clear the current contents
        while (!this->filaPriorizada.empty()) {
            delete this->filaPriorizada.top();
            this->filaPriorizada.pop();
        }

        // Copy quantosNos
        this->quantosNos = other.quantosNos;

        // Copy priority queue
        std::priority_queue<NoHuffman*, std::vector<NoHuffman*>, CompareNodes> tempQueue = other.filaPriorizada;

        while (!tempQueue.empty()) {
            NoHuffman* node = tempQueue.top();
            this->filaPriorizada.push(new NoHuffman(*node));  // Create a copy of NoHuffman and push it to the new queue
            tempQueue.pop();
        }
    }
    return *this;
}
