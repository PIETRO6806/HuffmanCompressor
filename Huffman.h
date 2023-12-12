//
// Created by Pietro on 11/12/2023.
//

#ifndef HUFFMANCOMPRESSOR_HUFFMAN_H
#define HUFFMANCOMPRESSOR_HUFFMAN_H

#include "NoHuffman.h"
#include "FilaPriorizada.h"
#include "ArvoreBinaria.h"
#include "CodigoHuffman.h"

class Huffman {
protected:
    NoHuffman* node_array[256];
    std::string in_file_name, out_file_name;
    FilaPriorizada filaPriorizada;
    ArvoreBinaria arvoreBinaria;
    void create_node_array();
    void contarFrequencias(std::ifstream& file);
    void construirFilaPriorizada();

public:
    Huffman(std::string, std::string);
    void criarFilaPriorizada();
    // void construirArvoreBinaria();
    FilaPriorizada getFilaPriorizada() const;
};


#endif //HUFFMANCOMPRESSOR_HUFFMAN_H
