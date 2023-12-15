// Created by Pietro on 11/12/2023.

#include <stdexcept>
#include <fstream>
#include <bitset>
#include <iostream>
#include "Huffman.h"

Huffman::Huffman(std::string in, std::string out) : in_file_name(in), out_file_name(out) {
    create_node_array();
}

void Huffman::create_node_array() {
    for (int i = 0; i < 256; i++) {
        node_array[i] = new NoHuffman;
        node_array[i]->setInfo(i);
        node_array[i]->setFrequencia(0);
    }
}

void Huffman::contarFrequencias() {
    for (char ch : buffer) {
        node_array[static_cast<unsigned char>(ch)]->setFrequencia(node_array[static_cast<unsigned char>(ch)]->getFrequencia() + 1);
    }
}

void Huffman::construirFilaPriorizada() {
    for (int i = 0; i < 256; i++) {
        if (node_array[i]->getFrequencia() > 0) {
            filaPriorizada.Enfileirar(*node_array[i]);
        }
    }
}

void Huffman::criarMapFrequencias() {
    FilaPriorizada copia = filaPriorizada;
    frequencias.clear();

    while (!copia.isEmpty()) {
        NoHuffman* node = copia.Retirar();
        char info = node->getInfo();
        unsigned freq = node->getFrequencia();
        frequencias.emplace_back(info, freq);
    }
}

void Huffman::criarFilaPriorizada() {
    std::ifstream input_file(in_file_name, std::ios::binary);
    if (!input_file.is_open()) {
        throw std::runtime_error("Unable to open input file");
    }

    char ch;
    while (input_file.get(ch)) {
        buffer.push_back(ch);
    }

    contarFrequencias();
    construirFilaPriorizada();
    criarMapFrequencias();

    input_file.close();
}

void Huffman::criarArvoreBinaria() {
    arvoreBinaria = ArvoreBinaria(filaPriorizada);
}

void Huffman::calcularHuffmanCodigos() {
    codigoHuffman.calcularCodigos(arvoreBinaria);
}

void Huffman::escreverFrequenciasNoArquivo(std::ofstream& output_file) {
    if (!output_file.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    unsigned int qtosCaracteresDiferentes = frequencias.size();
    output_file.write(reinterpret_cast<const char*>(&qtosCaracteresDiferentes), sizeof(qtosCaracteresDiferentes));

    for (const auto& pair : frequencias) {
        output_file.write(&pair.first, 1);
        output_file.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
    }
}

std::string Huffman::getExtensionFile() const {
    size_t ultimoPonto = in_file_name.find_last_of('.');
    return in_file_name.substr(ultimoPonto + 1);
}

void Huffman::escreverStringNoArquivo(const std::string& str, std::ofstream& file) {
    int str_length = str.length();
    file.write(reinterpret_cast<const char*>(&str_length), sizeof(str_length));
    file.write(str.c_str(), str_length);
}

void Huffman::escreverExtensaoNoArquivo(std::ofstream& file, std::string extension) {
    int integer = 14;
    file.write(reinterpret_cast<const char*>(&integer), sizeof(integer));
    escreverStringNoArquivo(extension, file);
}

CodigoHuffman Huffman::getCodigoHuffman() const {
    return codigoHuffman;
}

std::string Huffman::converterTextoEmBitsString(const std::vector<char>& buffer, const std::map<char, std::string>& codes) {
    std::string bits_string;
    for (char c : buffer) {
        bits_string += codes.at(c);
    }
    return bits_string;
}

void Huffman::anexarBitNoArquivo(std::ofstream& file, char bit, char& current_byte, int& bit_count) {
    if (bit != '0' && bit != '1') {
        throw std::runtime_error("Invalid bit: " + bit);
    }

    current_byte = (current_byte << 1) | (bit - '0');
    bit_count++;

    if (bit_count == BYTE_SIZE) {
        file.write(&current_byte, 1);
        current_byte = 0;
        bit_count = 0;
    }
}

void Huffman::escreverBitsNoArquivo(std::ofstream& output_file, const std::string& bits) {
    if (!output_file.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    char current_byte = 0;
    int  bit_count = 0;

    for (char bit : bits) {
        anexarBitNoArquivo(output_file, bit, current_byte, bit_count);
    }

    if (bit_count > 0) {
        current_byte <<= (BYTE_SIZE - bit_count);
        output_file.write(&current_byte, 1);
    }

    int redundant_bits = BYTE_SIZE - bit_count;
    output_file.seekp(0, std::ios::beg);
    output_file.write(reinterpret_cast<const char*>(&redundant_bits), sizeof(redundant_bits));
}

void Huffman::salvarCodificacao() {
    std::ofstream output_file(out_file_name, std::ios::binary);
    if (!output_file.is_open()) {
        throw std::runtime_error("Unable to create output file");
    }

    std::ifstream input_file(in_file_name, std::ios::binary);
    if (!input_file.is_open()) {
        throw std::runtime_error("Unable to open input file");
    }

    escreverFrequenciasNoArquivo(output_file);
    escreverExtensaoNoArquivo(output_file, getExtensionFile());
    std::string textoEmBits = converterTextoEmBitsString(buffer, getCodigoHuffman().getHuffmanCodes());
    escreverBitsNoArquivo(output_file, textoEmBits);

    input_file.close();
    output_file.close();
}

NoHuffman* Huffman::getNodeArray() const {
    return *node_array;
}

FilaPriorizada Huffman::getFilaPriorizada() const {
    return filaPriorizada;
}

ArvoreBinaria Huffman::getArvoreBinaria() const {
    return arvoreBinaria;
}

std::vector<std::pair<char, unsigned>> Huffman::getFrequencies() const {
    return frequencias;
}