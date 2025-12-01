#pragma once

#include <cstdint>
#include <expected>
#include <optional>
#include <string>
#include <vector>
#include <iostream>



enum GraphError
{
    invalidVertex
};

typedef struct Edge
{
    size_t u;
    size_t v;
    uint8_t w;

    Edge() : u(0), v(0), w(0) {}
    Edge(size_t u, size_t v, uint8_t w)
    {
        this->u = u;
        this->v = v;
        this->w = w;
    }

    bool operator<(const Edge& EdgeComp){
      return w < EdgeComp.w;
    }

    bool operator>(const Edge& EdgeComp){
      return w > EdgeComp.w;
    }
    friend std::ostream& operator<<(std::ostream& str, const Edge& currentEdge) {
      str << "Edge(OrigemU: " << currentEdge.u << " DestinoV: " << currentEdge.v << " Peso: " << (int)currentEdge.w << " )"; 
      return str;
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