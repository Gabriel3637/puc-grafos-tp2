#pragma once

#include <cstdint>
#include <expected>
#include <optional>
#include <string>
#include <vector>

enum GraphError
{
    invalidVertex
};

typedef struct Edge
{
    size_t u;
    size_t v;
    uint8_t w;

    Edge(size_t u, size_t v, uint8_t w)
    {
        this->u = u;
        this->v = v;
        this->w = w;
    }
} Edge;

class Graph
{
  private:
    std::vector<std::vector<Edge>> _e;
    void setEdge(size_t u, size_t v, uint8_t w);

  public:
    Graph(int v, std::vector<Edge> &edges);
    std::expected<void, GraphError> neighbors(std::vector<size_t> &n, size_t v);
    std::expected<std::optional<uint8_t>, GraphError> getWeight(size_t u,
                                                                size_t v);
    std::string toString();
};
