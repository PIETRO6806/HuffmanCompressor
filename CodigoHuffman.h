//
// Created by Pietro on 11/12/2023.
//

#ifndef HUFFMANCOMPRESSOR_CODIGOHUFFMAN_H
#define HUFFMANCOMPRESSOR_CODIGOHUFFMAN_H

#include "NoHuffman.h"
#include "ArvoreBinaria.h"

class CodigoHuffman {
private:
    void setCodigos (NoHuffman*, std::string);
public:
    void calcularCodigos (const ArvoreBinaria&);
};



#endif //HUFFMANCOMPRESSOR_CODIGOHUFFMAN_H
