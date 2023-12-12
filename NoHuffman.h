//
// Created by Pietro on 11/12/2023.
//

#ifndef HUFFMANCOMPRESSOR_NOHUFFMAN_H
#define HUFFMANCOMPRESSOR_NOHUFFMAN_H

#include <string>

class NoHuffman {
private:
    char info;
    int frequencia;
    std::string codigo;
    NoHuffman* esquerda;
    NoHuffman* direita;

public:
    //default constructor
    NoHuffman();

    // Constructor for leaf nodes
    NoHuffman(char, int);

    // Constructor for internal nodes
    NoHuffman(int, NoHuffman*, NoHuffman*);

    //getters
    char getInfo() const;
    int getFrequencia() const;
    std::string getCodigo() const;
    NoHuffman* getEsquerda() const;
    NoHuffman* getDireita() const;

    //setters
    void setInfo(char);
    void setFrequencia(int);
    void setCodigo(const std::string&);
    void setEsquerda(NoHuffman*);
    void setDireita(NoHuffman*);

    //operators
    // Comparison operator to compare nodes based on frequency
    bool operator>(const NoHuffman& other) const;

    // Destructor to free memory
    ~NoHuffman();
};


#endif //HUFFMANCOMPRESSOR_NOHUFFMAN_H
