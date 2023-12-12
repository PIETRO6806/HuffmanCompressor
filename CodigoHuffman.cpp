//
// Created by Pietro on 11/12/2023.
//

#include "CodigoHuffman.h"

void CodigoHuffman::setCodigos(NoHuffman* no, std::string codigo) {
    if (no->getEsquerda() == nullptr && no->getDireita() == nullptr)
    {
        no->setCodigo(codigo);
    }
    else
    {
        setCodigos(no->getEsquerda(), codigo + '0');
        setCodigos(no->getDireita(), codigo + '1');
    }
}

void CodigoHuffman::calcularCodigos(const ArvoreBinaria& arvore) {
    setCodigos(arvore.getRaiz(), "");
}