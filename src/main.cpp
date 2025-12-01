#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>

#include "graph.hpp"

#include <cmath>
#include <cstdint>

#include "tarjanMSA.cpp"
#include <unordered_map>
#include <array>

double euclidiana(unsigned char *img, int i, int j) {
    int ri = img[i * 3 + 0];
    int gi = img[i * 3 + 1];
    int bi = img[i * 3 + 2];

    int rj = img[j * 3 + 0];
    int gj = img[j * 3 + 1];
    int bj = img[j * 3 + 2];

    double dist = std::sqrt(
        (ri - rj) * (ri - rj) +
        (gi - gj) * (gi - gj) +
        (bi - bj) * (bi - bj)
    );

    return dist;
}

int main(void) { 
    
     int width=2, height=2, channels = 3;
     std::string im = "imgs/teste1.png";
    unsigned char *img =
        stbi_load(im.c_str(), &width, &height, &channels, 3);
    //retorna a imagem convertida em super array
    //cada vértice é de 3 em 3
    double maxDist = 0;
    for(int i = 0; i < width*height*3; i += 3) {
        if((i/3)%width > 0) maxDist = std::max(maxDist, euclidiana(img, i/3, i/3-1));
        if(i/3/width > 0) maxDist = std::max(maxDist, euclidiana(img, i/3, i/3-width));
    }
    double gamma = maxDist * 1.5;
    std::vector<Edge> e;
    
    for(int i=0;i<width*height*3;i=i+3){
        if((i/3)%width>0 ){//n é na esq
            double dist = euclidiana(img, i/3, i/3-1);
            e.push_back(Edge(i/3,i/3-1,dist));
            e.push_back(Edge(i/3-1,i/3,dist));
        }
        if(i/3/width>0){//n é em cima
            double dist = euclidiana(img, i/3, i/3-width);
            e.push_back(Edge(i/3,i/3-width,dist));
            e.push_back(Edge(i/3-width,i/3,dist));
        }
    }

    //adiciono vértice ligando a todo mundo(superroot):

    for (int u = 0; u < width*height; u++) {
        e.push_back(Edge(width*height, u, gamma));
    }
    std::cout<<"a\n";
    tarjanMSA tMSA = tarjanMSA();
    std::vector<Edge> e2 = tMSA.solveMaximumBranching(height*width+1,height*width,e);
    std::cout<<"b\n";
    std::vector<Edge> segmentated;
    //tirar super vértice
    for(Edge ee : e2){
        if(ee.u != height*width){
            segmentated.push_back(ee);
        }
    }

    std::cout<<"c\n";
    std::vector<int> fracamente;
    fracamente = tMSA.componentesFracamenteConexos(height*width,segmentated);

    for (int idx = 0; idx < fracamente.size(); idx++) {
        std::cout << fracamente[idx] << " ";
    }

    struct Acc {
        long r = 0, g = 0, b = 0;
        int count = 0;
    };

    std::unordered_map<int, Acc> acc;

    for (int i = 0; i < width * height; i++) {
        int comp = fracamente[i];

        acc[comp].r += img[i*3 + 0];
        acc[comp].g += img[i*3 + 1];
        acc[comp].b += img[i*3 + 2];
        acc[comp].count++;
    }

    std::unordered_map<int, std::array<unsigned char,3>> corMedia;

    for (auto &p : acc) {
        corMedia[p.first] = {
            (unsigned char)(p.second.r / p.second.count),
            (unsigned char)(p.second.g / p.second.count),
            (unsigned char)(p.second.b / p.second.count)
        };
    }

    unsigned char* out =
        (unsigned char*)malloc(width * height * 3);

    for (int i = 0; i < width * height; i++) {
        auto c = corMedia[fracamente[i]];

        out[i*3 + 0] = c[0];
        out[i*3 + 1] = c[1];
        out[i*3 + 2] = c[2];
    }

    std::cout<<"d\n";
    stbi_write_png(
        "imgs/segmentada_media.png",
        width,
        height,
        3,
        out,
        width * 3
    );
    std::cout<<"e\n";

    free(out);

    stbi_image_free(img);
    return 0;
}
