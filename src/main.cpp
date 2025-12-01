#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>

#include "graph.hpp"

#include <cmath>
#include <cstdint>

#include "tarjanMSA.cpp"






int main(void) { 
    /* 
     int width=2, height=2, channels = 3;
    
    unsigned char *img =
        stbi_load("imgs/test.png", &width, &height, &channels, 3);
    
    
    //retorna a imagem convertida em super array
    for(int i=0;i<width*height*3;i++){
        std::cout << "[" << (int)img[i] << "] ";
    }
    std::cout << '\n';
    //cada vértice é de 3 em 3
    std::vector<Edge> red(width*height);
    std::vector<Edge> green(width*height);
    std::vector<Edge> blue(width*height);

    size_t countPixels = 0;
    int incremento;
    //para cada vértice, conecta ele com os vizinhos, o peso da aresta = maior - menor

    Edge insertEdge;
    for(int i=0;i<width*height*3;i++){
        //exclui primeira linha e primeira coluna
            if(i%3==0){//red
                incremento = 0;
                //esq
                if((i/3)%width>0){
                    if(img[i]>= img[i-3]){
                        red[countPixels+ incremento] = {i/3,(i/3)-1, static_cast<u_int8_t>(img[i]-img[i-3])};
                    }else if(img[i] < img[i-3]){
                        red[countPixels+ incremento] = {(i/3)-1,i/3, static_cast<u_int8_t>(img[i-3]-img[i])};
                    }
                    incremento++;
                }
                //cima
                if(i/3/width>0){
                    if(img[i]>= img[i-width*3]){
                        red[countPixels+incremento] = {i/3,i/3-width,static_cast<u_int8_t>(img[i]-img[i-width*3])};
                    }else if(img[i] < img[i - width*3]){
                        red[countPixels+incremento] = {i/3-width,i/3,static_cast<u_int8_t>(img[i-width*3]-img[i])};
                    }
                }
            }else if(i%3==1){//green
                incremento = 0;
                if((i/3)%width>0){
                    if(img[i]>= img[i-3]){
                        green[countPixels+incremento] = {i/3,(i/3)-1,static_cast<u_int8_t>(img[i]-img[i-3])};
                    }else if(img[i] < img[i-3]){
                        green[countPixels+incremento] = {(i/3)-1,i/3, static_cast<u_int8_t>(img[i-3]-img[i])};
                    }
                    incremento++;
                }
                //cima
                if(i/3/width>0){
                    if(img[i]>= img[i-width*3]){
                        green[countPixels+incremento] = {i/3,(i/3-width),static_cast<u_int8_t>(img[i]-img[i-width*3])};
                    }else if(img[i] < img[i - width*3]){
                        green[countPixels+incremento] = {(i/3-width),i/3, static_cast<u_int8_t>(img[i-width*3]-img[i])};
                    }
                }
            }else{//blue
                incremento = 0;
                if((i/3)%width>0){
                    if(img[i]>= img[i-3]){
                        blue[countPixels+incremento] = {i/3,(i/3)-1, static_cast<u_int8_t>(img[i]-img[i-3])};
                    }else if(img[i] < img[i-3]){
                        blue[countPixels+incremento] = {(i/3)-1,i/3, static_cast<u_int8_t>(img[i-3]-img[i])};
                    }
                    incremento++;
                }
                //cima
                if(i/3/width>0){
                    if(img[i]>= img[i-width*3]){
                        blue[countPixels+incremento] = {i/3,(i/3-width),static_cast<u_int8_t>(img[i]-img[i-width*3])};
                    }else if(img[i] < img[i - width*3]){
                        blue[countPixels+incremento] = {(i/3-width),i/3, static_cast<u_int8_t>(img[i-width*3]-img[i])};
                    }
                }
            }
            
            if(i%3 == 2 && (i/3/width>0))
                countPixels++;

            if(i%3 == 2 && (i/3)%width>0)
                countPixels++;
            


        //imaginando como uma matriz, n existe acima se for menor
    } */

    //fazer um grafo pra cada cor, no grafo, a aresta é o resultado da subtração do maior pro menor, apontando pro menor

    //std::cout << graph.toString() << std::endl;
/* 

    std::cout << "---------------------RED-----------------" << std::endl;
    for(int i = 0; i < width*height; i++){
        std::cout << red[i] << std::endl;
    }

    std::cout << "---------------------GREEN-----------------" << std::endl;
    for(int i = 0; i < width*height; i++){
        std::cout << green[i] << std::endl;
    }


    std::cout << "---------------------BLUE-----------------" << std::endl;
    for(int i = 0; i < width*height; i++){

        std::cout << blue[i] << std::endl;
    } */

    std::vector<Edge> teste = {
        {0, 1, 10},  
        {0, 2, 5},
        {2, 0, 1},     
        {1, 2, 2},   
        {1, 3, 1},   
        {3, 4, 7},   
        {2, 4, 3},
        {2, 3, 2},
        {3, 1, 1},  
        {4, 0, 8},
        {5, 0, 1}   
    };

    Graph graph = Graph( 9 ,teste);
    std::cout << "graph: \n" << graph.toString() << std::endl;



    tarjanMSA tarjan = tarjanMSA();
    std::vector<Edge> aresstasH = tarjan.solveMaximumBranching(6, 5, teste);

    for(Edge e : aresstasH){
        std::cout << e << std::endl;
    }


    /* Dmsta testeMsta = Dmsta();
    testeMsta.optimumBranchingTarjan(5, teste); */

    
    
    /* std::cout << "MSA: \n" << << std::endl;

    stbi_image_free(img); */

    return 0; 
}
