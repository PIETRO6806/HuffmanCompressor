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
#include <unordered_map>

constexpr auto BYTE_SIZE = 8;

class Huffman {
protected:
    std::vector<std::pair<char, unsigned>> frequencias;
    std::vector<char> buffer;
    NoHuffman* node_array[256];
    std::string in_file_name, out_file_name;
    FilaPriorizada filaPriorizada;
    ArvoreBinaria arvoreBinaria;
    CodigoHuffman codigoHuffman;
    void create_node_array();
    void contarFrequencias();
    void construirFilaPriorizada();
    void criarMapFrequencias();
    void anexarBitNoArquivo(std::ofstream&, char, char&, int&);
        //int binary_to_decimal(const std::string&);															//convert a 8-bit 0/1 string of binary code to a decimal integer
    //std::string decimal_to_binary(int);

public:
    Huffman(std::string, std::string);
    void criarFilaPriorizada();
    void criarArvoreBinaria();
    void calcularHuffmanCodigos();
    void escreverFrequenciasNoArquivo(std::ofstream&);
    void escreverStringNoArquivo(const std::string&, std::ofstream&);
    void escreverExtensaoNoArquivo(std::ofstream&, std::string);
    void escreverBitsNoArquivo(std::ofstream&, const std::string&);
    std::string converterTextoEmBitsString(const std::vector<char>&, const std::map<char, std::string>&);
    void salvarCodificacao();
    void getFrequencias();
    void salvarDecodificacao();
    void recriarArvoreBinaria();
    NoHuffman* getNodeArray() const;
    FilaPriorizada getFilaPriorizada() const;
    ArvoreBinaria getArvoreBinaria() const;
    CodigoHuffman getCodigoHuffman() const;
    std::vector<std::pair<char, unsigned>> getFrequencies() const;
    std::string getExtensionFile() const;
};


#endif //HUFFMANCOMPRESSOR_HUFFMAN_H
