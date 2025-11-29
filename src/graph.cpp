#include "graph.hpp"
#include <cstdint>

Graph::Graph(unsigned int vertexes)
    : vCount(vertexes), matrix(vertexes * vertexes)
{
}

inline size_t Graph::idx(unsigned int x, unsigned int y)
{
    return y * matrix.size() + x;
}

unsigned int Graph::vertexCount() { return vCount; }

void Graph::setEdge(unsigned int u, unsigned int v, uint8_t w)
{
    matrix[idx(u, v)] = w;
}

uint8_t Graph::getEdge(unsigned int u, unsigned int v)
{
    return matrix[idx(u, v)];
}
