cmake_minimum_required(VERSION 3.26)
project(HuffmanCompressor)

set(CMAKE_CXX_STANDARD 17)

add_executable(HuffmanCompressor CodificacaoHuffman.cpp
        NoHuffman.h
        NoHuffman.cpp
        FilaPriorizada.h
        FilaPriorizada.cpp
        ArvoreBinaria.h
        ArvoreBinaria.cpp
        CodigoHuffman.h
        CodigoHuffman.cpp
        Huffman.h
        Huffman.cpp
        DecodificacaoHuffman.cpp

)
