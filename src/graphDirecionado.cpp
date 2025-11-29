#include "../inc/graph.hpp"  // ou ajuste do caminho conforme o build

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
        for (const auto& e : listaAdjacencia[i])
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