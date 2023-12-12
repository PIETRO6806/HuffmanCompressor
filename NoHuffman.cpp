//
// Created by Pietro on 11/12/2023.
//

#include "NoHuffman.h"

#include <utility>

NoHuffman::NoHuffman() : info('\0'), frequencia(0), esquerda(nullptr), direita(nullptr){}

NoHuffman::NoHuffman(char novoInfo, int novaFrequencia) : info(novoInfo), frequencia(novaFrequencia), esquerda(nullptr), direita(nullptr){}

NoHuffman::NoHuffman(int novaFrequencia, NoHuffman* novoEsquerda, NoHuffman* novoDireita) : info('\0'), frequencia(novaFrequencia), esquerda(novoEsquerda), direita(novoDireita){}

char NoHuffman::getInfo() const {
    return info;
}

int NoHuffman::getFrequencia() const {
    return frequencia;
}

std::string NoHuffman::getCodigo() const {
    return codigo;
}

NoHuffman* NoHuffman::getEsquerda() const {
    return esquerda;
}

NoHuffman* NoHuffman::getDireita() const {
    return direita;
}

void NoHuffman::setInfo(char novaInfo) {
    info = novaInfo;
}

void NoHuffman::setFrequencia(int novaFrequencia) {
    frequencia = novaFrequencia;
}

void NoHuffman::setCodigo(const std::string& novoCodigo) {
    codigo = novoCodigo;
}

void NoHuffman::setEsquerda(NoHuffman* novoEsquerda) {
    esquerda = novoEsquerda;
}

void NoHuffman::setDireita(NoHuffman* novoDireita) {
    direita = novoDireita;
}

bool NoHuffman::operator>(const NoHuffman& other) const {
    return frequencia > other.frequencia;
}

// Destructor to free memory
NoHuffman::~NoHuffman() {
    delete esquerda;
    delete direita;
}