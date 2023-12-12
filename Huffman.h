//
// Created by Pietro on 11/12/2023.
//

#ifndef HUFFMANCOMPRESSOR_HUFFMAN_H
#define HUFFMANCOMPRESSOR_HUFFMAN_H

#include "NoHuffman.h"
#include "FilaPriorizada.h"
#include "ArvoreBinaria.h"
#include "CodigoHuffman.h"
#include <fstream>

class Huffman {
protected:
    NoHuffman* node_array[256];
    std::fstream in_file, out_file;
    std::string in_file_name, out_file_name;
    FilaPriorizada filaPriorizada;
    ArvoreBinaria arvoreBinaria;
    CodigoHuffman codigoHuffman;
    void create_node_array();
    void contarFrequencias(std::ifstream& file);
    void construirFilaPriorizada();
    int binary_to_decimal(std::string&);															//convert a 8-bit 0/1 string of binary code to a decimal integer
    std::string decimal_to_binary(int);

public:
    Huffman(std::string, std::string);
    void criarFilaPriorizada();
    void criarArvoreBinaria();
    void calcularHuffmanCodigos();
    void salvarCodigos();
    FilaPriorizada getFilaPriorizada() const;
    ArvoreBinaria getArvoreBinaria() const;
};


#endif //HUFFMANCOMPRESSOR_HUFFMAN_H
