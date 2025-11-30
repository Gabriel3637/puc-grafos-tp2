#include "../inc/graph.hpp"  // ou ajuste do caminho conforme o build

#include <algorithm>
#include <cstdint>
#include <sstream>
#include <cmath>

Graph::Graph(int numVertices)
{
    vertexes.resize(numVertices);
    listaAdjacencia.resize(numVertices);

    for (int i = 0; i < numVertices; i++)
        vertexes[i] = i;
}

std::string Graph::toString(){
    std::stringstream ss;
    
    for (size_t i = 0; i < listaAdjacencia.size(); i++)
    {
        ss << i << ": ";
        for (Edge e : listaAdjacencia[i])
        {
            ss << "(" << e.u << " -> " << e.v << ") w="<<e.w << " | ";
        }
        ss << "\n";
    }

    return ss.str();
}

void Graph::addEdge(int u, int v, int w){
    listaAdjacencia[u].push_back(Edge(u,v,w));
}



Graph Graph::optimumBranchingTarjan(){
    //S = componente com a raiz
    //W = componente fracamente conexo contendo S
    //c(v,w) = valores da aresta (provavel peso)
    //root componet = componente raiz se nenhuma aresta entra nele

    //pré-passo: determinar CFCs

    //passo 1: escolher um vértice em que uma aresta > 0
    //selecionar a aresta de maior valor
    //adcionar a aresta em H

    //loop:
    //1: componente raiz que tem um vértice interno não examinado > 0
    //2: Achar o maior vértice não examinado
    //3: 

    int roots = 0;
    for(int i=1;i<=vertexes.size();i++){
        std::vector<int> v;
    }
}