//
// Created by Pietro on 11/12/2023.
//

#include <stdexcept>
#include <fstream>
#include <bitset>
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

void Huffman::contarFrequencias(std::ifstream& file) {
    char ch;
    while (file.get(ch)) {
        // Increment the frequency of the character
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

    // Count frequencies of each character in the file
    contarFrequencias(input_file);

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

    // Write the Huffman codes to the output file
    const auto& huffmanCodes = codigoHuffman.getHuffmanCodes();
    int numUniqueChars = huffmanCodes.size();

    output_file.write(reinterpret_cast<const char*>(&numUniqueChars), sizeof(int));

    for (const auto& codePair : huffmanCodes) {
        char currentChar = codePair.first;
        const std::string& huffmanCode = codePair.second;
        int codeLength = huffmanCode.length();

        output_file.write(&currentChar, sizeof(char));
        output_file.write(reinterpret_cast<const char*>(&codeLength), sizeof(int));
        output_file.write(huffmanCode.c_str(), codeLength);
    }

    // Read the input file and write the Huffman-encoded data to the output file
    std::ifstream input_file(in_file_name, std::ios::binary);

    if (!input_file.is_open()) {
        // Handle the case where the input file cannot be opened
        throw std::runtime_error("Unable to open input file");
    }

    char ch;
    std::string encodedData;
    while (input_file.get(ch)) {
        // Get the Huffman code for the current character
        std::string huffmanCode = arvoreBinaria.getCodigoHuffman(ch);

        // Append the Huffman code to the encoded data
        encodedData += huffmanCode;

        // Write the encoded data to the output file whenever it forms a byte
        while (encodedData.length() >= 8) {
            std::bitset<8> byte(encodedData.substr(0, 8));
            output_file.write(reinterpret_cast<const char*>(&byte), sizeof(char));
            encodedData = encodedData.substr(8);
        }
    }

    // Write the remaining bits if any
    if (!encodedData.empty()) {
        std::bitset<8> byte(encodedData + std::string(8 - encodedData.length(), '0'));
        output_file.write(reinterpret_cast<const char*>(&byte), sizeof(char));
    }

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

void Huffman::escreverFrequenciasNoArquivo() {

    std::ofstream output_file(out_file_name, std::ios::binary);

    if (!output_file.is_open()) {
        // Throw an exception with an error message
        throw std::runtime_error("Error opening file");
    }

    unsigned int amout_of_frequency_pairs = frequencias.size();

    output_file.write(reinterpret_cast<const char*>(&amout_of_frequency_pairs), sizeof(amout_of_frequency_pairs));

    for (const auto& pair : frequencias) {
        output_file.write(&pair.first, 1); // Write the char to the file.

        // Write the unsigned to the file:
        output_file.write(reinterpret_cast <const char*> (&pair.second),sizeof(pair.second));
    }

    output_file.close();
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