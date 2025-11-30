#include "graph.hpp"

#include <cstdint>
#include <sstream>

Graph::Graph(int v, std::vector<Edge> &edges) : _e(v)
{
    for (size_t i = 0; i < edges.size(); i++)
    {
        setEdge(edges[i].u, edges[i].v, edges[i].w);
    }
}

void Graph::setEdge(size_t u, size_t v, uint8_t w)
{
    for (int i = 0; i < _e[u].size(); i++)
    {
        if (_e[u][i].v == v)
            return;
    }
    _e[u].emplace_back(u, v, w);
    _e[v].emplace_back(v, u, w);
}

std::expected<void, GraphError> Graph::neighbors(std::vector<size_t> &n,
                                                 size_t v)
{
    if (v >= _e[v].size())
    {
        return std::unexpected(GraphError::invalidVertex);
    }

    for (size_t i = 0; i < _e[v].size(); i++)
    {
        n.push_back(_e[v][i].v);
    }

    return {};
}

std::expected<std::optional<uint8_t>, GraphError> Graph::getWeight(size_t u,
                                                                   size_t v)
{
    if (u >= _e.size() || v >= _e.size())
    {
        return std::unexpected(GraphError::invalidVertex);
    }

    for (int i = 0; i < _e[u].size(); i++)
    {
        if (_e[u][i].v == v)
        {
            return _e[u][i].w;
        }
    }

    return {};
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
                ss << "(" << _e[i][j].v << ", " << (int)_e[i][j].w << ")";
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
