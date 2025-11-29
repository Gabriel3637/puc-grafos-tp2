#include "../inc/graph.hpp"

#include <algorithm>
#include <cstdint>
#include <sstream>

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

void optimumBranching(){
    //achar a raiz

    //pra todo vertice q n é a raiz, escolhe a aresta de entrada de menor peso

    //se um ciclo transforma em super vértice aí repete algoritmo

    //tome
}