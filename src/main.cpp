#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>

#include "graph.hpp"
#include "mst.hpp"
#include <vector>

int main(void) { 
    std::cout << "Teste 0" << std::endl;
    Mst testeMst = Mst();

    std::cout << "Teste 1" << std::endl;
    
    std::vector<Edge> teste = {
        {0, 1, 10},
        {1, 2, 5},
        {0, 2, 8}
    };

    for(Edge e: teste){
        std::cout << e << std::endl;
    }



    std::cout << "Teste 2" << std::endl;

    std::vector<size_t> agm = testeMst.generateMST(teste, 3, 10);

    std::cout << "Teste 3" << std::endl;
/* 
    for(Edge e: agm){
        std::cout << e << std::endl;
    } */

    std::cout << "Teste 4" << std::endl;




    return 0; 

}
