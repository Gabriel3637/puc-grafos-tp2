#include "graph.hpp"

#include <algorithm>
#include <cstdint>
#include <sstream>

Graph::Graph(size_t vertexes) : _v(vertexes), _e() {}

inline bool Graph::isFirst(size_t v) { return v == 0; }
inline bool Graph::isLast(size_t v) { return v == vertexCount() - 1; }

size_t Graph::vertexCount() { return _v.size(); }
size_t Graph::edgeCount() { return _e.size(); }

void Graph::_setEdge(size_t u, size_t v, uint8_t w)
{
    if (isLast(u))
    {
        _e.emplace_back(Edge{v, w});
        return;
    }

    if (isFirst(u) || _v[u] == 0)
    {
        firstWithNeighbor = u;
    }
    else if (_v[u] == _v[u - 1])
    {
        _v[u]++;
    }

    for (int i = u + 1; i < vertexCount(); i++)
    {
        _v[i]++;
    }

    _e.emplace(_e.begin() + _v[u], Edge{v, w});
}

void Graph::setEdge(size_t u, size_t v, uint8_t w)
{
    _setEdge(u, v, w);
    if (v != u)
    {
        _setEdge(v, u, w);
    }
}

std::optional<uint8_t> Graph::getEdge(size_t u, size_t v)
{
    if (edgeCount() == 0 || u < firstWithNeighbor ||
        u != firstWithNeighbor && _v[u] == _v[u - 1])
    {
        return {};
    }

    auto it = std::find_if(_e.begin() + _v[u],
                           isLast(u) ? _e.end() : _e.begin() + _v[u + 1],
                           [v](const Edge &edge) { return edge.n == v; });

    if (it != _e.end())
    {
        return it->w;
    }
    else
    {
        return {};
    }
}

std::string Graph::toString()
{
    std::stringstream ss;

    ss << vertexCount() << " vertexes" << std::endl;
    ss << edgeCount() << " edges" << std::endl;

    int first = firstWithNeighbor;

    for (int i = first; i < vertexCount(); i++)
    {
        if (i == first || _v[i] != _v[i - 1])
        {
            ss << i << " => ";

            int end = isLast(i) ? edgeCount() : _v[i + 1];
            for (int j = _v[i]; j < end; j++)
            {
                ss << "(" << _e[j].n << ", " << (int)_e[j].w << ")";
                if (j < end - 1)
                {
                    ss << ", ";
                }
            }
            ss << std::endl;
        }
    }

    return ss.str();
}
