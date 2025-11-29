#include "graph.hpp"

#include <algorithm>
#include <cstdint>
#include <sstream>

Graph::Graph(size_t vertexes) : _e(vertexes) {}

void Graph::setEdge(size_t u, size_t v, uint8_t w)
{
    for (int i = 0; i < _e[u].size(); i++)
    {
        if (_e[u][i].n == v)
            return;
    }
    _e[u].emplace_back(v, w);
    _e[v].emplace_back(u, w);
}

std::string Graph::toString()
{
    std::stringstream ss;

    for (int i = 0; i < _e.size(); i++)
    {
        if (_e[i].size() > 0)
        {
            ss << i << " -> ";
            for (int j = 0; j < _e[i].size(); j++)
            {
                ss << "(" << _e[i][j].n << ", " << (int)_e[i][j].w << ")";
                if (j > _e[i].size() - 1)
                {
                    ss << ", ";
                }
            }
            ss << std::endl;
        }
    }

    return ss.str();
}
