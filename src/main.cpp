#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>

#include "graph.hpp"

int main(void) { 
    
    //retorna a imagem convertida em super array

    //fazer um grafo pra cada cor, no grafo, a aresta é o resultado da subtração do maior pro menor, apontando pro menor

    Graph graph = Graph(5);

    graph.addEdge(0, 1, 10);  
    graph.addEdge(0, 2, 5);   
    graph.addEdge(1, 2, 2);   
    graph.addEdge(1, 3, 1);   
    graph.addEdge(3, 4, 7);   
    graph.addEdge(2, 4, 3);   

    graph.addEdge(4, 0, 8);   
    std::cout << graph.toString() << std::endl;

    return 0; }
