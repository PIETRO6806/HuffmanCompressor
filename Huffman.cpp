//
// Created by Pietro on 11/12/2023.
//

#include <stdexcept>
#include <fstream>
#include <bitset>
#include <iostream>
#include "Huffman.h"

void Huffman::create_node_array()
{
    for (int i = 0; i < 256; i++)
    {
        node_array[i] = new NoHuffman;
        node_array[i]->setInfo(i);
        node_array[i]->setFrequencia(0);
    }
}

Huffman::Huffman(std::string in, std::string out)
{
    in_file_name = in;
    out_file_name = out;
    create_node_array();
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

    // Clear the existing frequencies map
    frequencias.clear();

    // Iterate through each node in the priority queue
    while (!copia.isEmpty()) {
        NoHuffman* node = copia.Retirar();
        char info = node->getInfo();
        unsigned freq = node->getFrequencia();

        // Add the node information and frequency to the vector
        frequencias.emplace_back(info, freq);
    }
}

void Huffman::criarFilaPriorizada() {
    // Open the input file in binary mode
    std::ifstream input_file(in_file_name, std::ios::binary);

    if (!input_file.is_open()) {
        // Handle the case where the file cannot be opened
        throw std::runtime_error("Unable to open input file");
    }

    char ch;
    while (input_file.get(ch)) {
        buffer.push_back(ch); // Add each character to the buffer
    }

    // Count frequencies of each character in the file
    contarFrequencias();

    // Build the priority queue using the counted frequencies
    construirFilaPriorizada();

    criarMapFrequencias();

    // Close the input file
    input_file.close();
}

void Huffman::criarArvoreBinaria() {
    // Create an instance of ArvoreBinaria by passing the priority queue
    arvoreBinaria = ArvoreBinaria(filaPriorizada);
}

FilaPriorizada Huffman::getFilaPriorizada() const {
    return filaPriorizada;
}

void Huffman::calcularHuffmanCodigos() {
    // Now that you have the binary tree, calculate Huffman codes
    codigoHuffman.calcularCodigos(arvoreBinaria);
}

ArvoreBinaria Huffman::getArvoreBinaria() const {
    return arvoreBinaria;
}

// Implement the method in your Huffman.cpp file
void Huffman::salvarCodificacao() {
    // Open the output file in binary mode
    std::ofstream output_file(out_file_name, std::ios::binary);

    if (!output_file.is_open()) {
        // Handle the case where the output file cannot be created
        throw std::runtime_error("Unable to create output file");
    }

    // Read the input file and write the Huffman-encoded data to the output file
    std::ifstream input_file(in_file_name, std::ios::binary);

    if (!input_file.is_open()) {
        // Handle the case where the input file cannot be opened
        throw std::runtime_error("Unable to open input file");
    }

    escreverFrequenciasNoArquivo(output_file);

    escreverExtensaoNoArquivo(output_file, getExtensionFile());

    std::string textoEmBits = converterTextoEmBitsString(buffer, getCodigoHuffman().getHuffmanCodes());

    escreverBitsNoArquivo(output_file, textoEmBits);

    // Close the files
    input_file.close();
    output_file.close();
}


CodigoHuffman Huffman::getCodigoHuffman() const {
    return codigoHuffman;
}

NoHuffman* Huffman::getNodeArray() const {
    return *node_array;
}

// Add the following public method to get the frequencies map
std::vector<std::pair<char, unsigned>> Huffman::getFrequencies() const {
    return frequencias;
}

void Huffman::escreverFrequenciasNoArquivo(std::ofstream& output_file) {

    if (!output_file.is_open()) {
        // Throw an exception with an error message
        throw std::runtime_error("Error opening file");
    }

    unsigned int qtosCaracteresDiferentes = frequencias.size();

    output_file.write(reinterpret_cast<const char*>(&qtosCaracteresDiferentes), sizeof(qtosCaracteresDiferentes));

    for (const auto& pair : frequencias) {
        output_file.write(&pair.first, 1); // Write the char to the file.

        // Write the unsigned to the file:
        output_file.write(reinterpret_cast <const char*> (&pair.second),sizeof(pair.second));
    }

}

std::string Huffman::getExtensionFile() const{
    size_t ultimoPonto = in_file_name.find_last_of('.');
    std::string extension = in_file_name.substr(ultimoPonto + 1);

    return extension;
}

void Huffman::escreverStringNoArquivo(const std::string& str, std::ofstream& file) {
    int str_length = str.length();

    file.write(reinterpret_cast<const char*>(&str_length), sizeof(str_length));

    file.write(str.c_str(), str_length);
}

void Huffman::escreverExtensaoNoArquivo(std::ofstream& file, std::string extension) {
    int integer = 14;

    // This will be replaced by the amount of redundant bits:
    file.write(reinterpret_cast<const char*>(&integer), sizeof(integer));

    escreverStringNoArquivo(extension, file);
}

void Huffman::escreverBitsNoArquivo(std::ofstream& output_file, const std::string& bits){
    if (!output_file.is_open()) {
        // Throw an exception with an error message
        throw std::runtime_error("Error opening file");
    }

    char current_byte = 0; // Current byte being filled with bits.
    int  bit_count = 0; // Number of bits in the current byte.

    for (char bit : bits) {
        anexarBitNoArquivo(output_file, bit, current_byte, bit_count);
    }

    // If there are remaining bits in the buffer, write them to the file:
    if (bit_count > 0) {
        current_byte <<= (BYTE_SIZE - bit_count);
        output_file.write(&current_byte, 1);
    }

    int redundant_bits = BYTE_SIZE - bit_count; // Keep track of the amount of redundant bits.

    // Write the amount of redundant bits to the first line of the file
    output_file.seekp(0, std::ios::beg);
    output_file.write(reinterpret_cast<const char*>(&redundant_bits), sizeof(redundant_bits));
}

void Huffman::anexarBitNoArquivo(std::ofstream& file, char bit, char& current_byte, int& bit_count) {
    if (bit != '0' && bit != '1') {
        // Throw an exception with an error message
        throw std::runtime_error("Invalid bit: " + bit);
    }

    current_byte = (current_byte << 1) | (bit - '0'); // Shift left by 1 bit to make room for the new bit and add the new bit to the buffer.

    bit_count++; // Increment the number of bits in the buffer.

    // If the buffer is full, write the byte to the file:
    if (bit_count == BYTE_SIZE) {
        file.write(&current_byte, 1); // Write the byte to the file.
        current_byte = 0;
        bit_count = 0;
    }
}


// Turns the text into it's corresponding Huffman codes:
std::string Huffman::converterTextoEmBitsString(const std::vector<char>& buffer, const std::map<char, std::string>& codes) {
    std::string bits_string;

    for (char c : buffer) {
        bits_string += codes.at(c);
    }

    return bits_string;
}
