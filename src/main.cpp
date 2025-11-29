#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>

#include "graph.hpp"

int main(void) { 
    
     int width=2, height=2, channels = 3;
    
    unsigned char *img =
        stbi_load("imgs/test.png", &width, &height, &channels, 3);
    
    stbi_image_free(img);
    //retorna a imagem convertida em super array
    for(int i=0;i<width*height*3;i++){
        std::cout << "[" << (int)img[i] << "] ";
    }
    std::cout << '\n';
    //cada vértice é de 3 em 3
    Graph red = Graph(width*height);
    Graph green = Graph(width*height);
    Graph blue = Graph(width*height);
    //para cada vértice, conecta ele com os vizinhos, o peso da aresta = maior - menor
    for(int i=0;i<width*height*3;i++){
        //exclui primeira linha e primeira coluna
            if(i%3==0){//red
                //esq
                if((i/3)%width>0){
                    if(img[i]> img[i-3]){
                        red.addEdge(i/3,(i/3)-1,img[i]-img[i-3]);
                    }else if(img[i] < img[i-3]){
                        red.addEdge((i/3)-1,i/3,img[i-3]-img[i]);
                    }
                }
                //cima
                if(i/3/width>0){
                    if(img[i]> img[i-width*3]){
                        red.addEdge(i/3,i/3-width,img[i]-img[i-width*3]);
                    }else if(img[i] < img[i - width*3]){
                        red.addEdge(i/3-width,i/3,img[i-width*3]-img[i]);
                    }
                }
            }else if(i%3==1){//green
                if((i/3)%width>0){
                    if(img[i]> img[i-3]){
                        green.addEdge(i/3,(i/3)-1,img[i]-img[i-3]);
                    }else if(img[i] < img[i-3]){
                        green.addEdge((i/3)-1,i/3,img[i-3]-img[i]);
                    }
                }
                //cima
                if(i/3/width>0){
                    if(img[i]> img[i-width*3]){
                        green.addEdge(i/3,(i/3-width),img[i]-img[i-width*3]);
                    }else if(img[i] < img[i - width*3]){
                        green.addEdge((i/3-width),i/3,img[i-width*3]-img[i]);
                    }
                }
            }else{//blue
                if((i/3)%width>0){
                    if(img[i]> img[i-3]){
                        blue.addEdge(i/3,(i/3)-1,img[i]-img[i-3]);
                    }else if(img[i] < img[i-3]){
                        blue.addEdge((i/3)-1,i/3,img[i-3]-img[i]);
                    }
                }
                //cima
                if(i/3/width>0){
                    if(img[i]> img[i-width*3]){
                        blue.addEdge(i/3,(i/3-width),img[i]-img[i-width*3]);
                    }else if(img[i] < img[i - width*3]){
                        blue.addEdge((i/3-width),i/3,img[i-width*3]-img[i]);
                    }
                }
            }
        //imaginando como uma matriz, n existe acima se for menor
    }

    //fazer um grafo pra cada cor, no grafo, a aresta é o resultado da subtração do maior pro menor, apontando pro menor

    //std::cout << graph.toString() << std::endl;
    std::cout << "Red: \n" << red.toString() << std::endl;
    std::cout << "Green: \n" << green.toString() << std::endl;
    std::cout << "Blue: \n" << blue.toString() << std::endl;

    return 0; 
}
