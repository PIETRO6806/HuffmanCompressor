//
// Created by Pietro on 11/12/2023.
//

#ifndef HUFFMANCOMPRESSOR_CODIGOHUFFMAN_H
#define HUFFMANCOMPRESSOR_CODIGOHUFFMAN_H

#include "NoHuffman.h"
#include "ArvoreBinaria.h"
#include <map>

class CodigoHuffman {
private:
    void setCodigos (NoHuffman*, std::string);
    std::map<char, std::string> huffmanCodes; // Map to store the codes
public:
    void calcularCodigos (const ArvoreBinaria&);
    std::map<char, std::string> getHuffmanCodes() const; // New method to get the codes
};



#endif //HUFFMANCOMPRESSOR_CODIGOHUFFMAN_H
