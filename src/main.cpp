#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>

#include "graph.hpp"

int main(void) { 

    Graph graph = Graph(5);
    
    graph.addEdge(0, 1, 10);  // peso 10
    graph.addEdge(0, 2, 5);   // peso 5
    graph.addEdge(1, 2, 2);   // peso 2
    graph.addEdge(1, 3, 1);   // peso 1
    graph.addEdge(3, 4, 7);   // peso 7
    graph.addEdge(2, 4, 3);   // peso 3

    // Criando um ciclo com peso
    graph.addEdge(4, 0, 8);   // peso 8
    std::cout << graph.toString() << std::endl;

    return 0; }
