//
// Created by Pietro on 11/12/2023.
//

#include <stdexcept>
#include <fstream>
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

int Huffman::binary_to_decimal(std::string& in)
{
    int result = 0;
    for (int i = 0; i < in.size(); i++)
        result = result * 2 + in[i] - '0';
    return result;
}

std::string Huffman::decimal_to_binary(int in)
{
    std::string temp;
    std::string result;
    while (in)
    {
        temp += ('0' + in % 2);
        in /= 2;
    }
    result.append(8 - temp.size(), '0');													//append '0' ahead to let the result become fixed length of 8
    for (int i = temp.size() - 1; i >= 0; i--)
    {
        result += temp[i];
    }
    return result;
}

/*void Huffman::salvarCodigos() {
    in_file.open(in_file_name, std::ios::in);
    out_file.open(out_file_name, std::ios::out | std::ios::binary);

    std::string in, s;
    in += static_cast<char>(filaPriorizada.getQuantosNos()); // Save the size of the priority queue

    // Iterate through the priority queue and save characters and their Huffman codes
    FilaPriorizada tempQueue = filaPriorizada; // Create a copy of the priority queue
    while (!tempQueue.isEmpty()) {
        NoHuffman* atual = tempQueue.Retirar();
        in += atual->getInfo();

        s.assign(255 - atual->getCodigo().size(), '0'); // Set the codes with a fixed 128-bit string form
        s += '1'; // '1' indicates the start of Huffman code
        s.append(atual->getCodigo());

        in += static_cast<char>(binary_to_decimal(s.substr(0, 8)));
        for (int i = 0; i < 15; i++) {
            s = s.substr(8);
            in += static_cast<char>(binary_to_decimal(s.substr(0, 8)));
        }
    }

    char id;
    in_file.get(id);
    while (!in_file.eof()) {
        s += node_array[id]->getCodigo();
        while (s.size() > 8) {
            in += static_cast<char>(binary_to_decimal(s.substr(0, 8)));
            s = s.substr(8);
        }
        in_file.get(id);
    }

    int count = 8 - s.size();
    if (s.size() < 8) {
        s.append(count, '0');
    }
    in += static_cast<char>(binary_to_decimal(s)); // Save the last few codes
    in += static_cast<char>(count); // Save the number of 'count' at last

    out_file.write(in.c_str(), in.size());
    in_file.close();
    out_file.close();
}*/