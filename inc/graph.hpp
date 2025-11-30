#include <cstdint>
#include <optional>
#include <string>
#include <vector>

typedef struct Edge
{
    int u;
    int v;
    double w;

    Edge(int u, int v, double w)
    {
        this->u = u;
        this->v = v;
        this->w = w;
    }
} Edge;

class Graph
{
  private:

  public:
    std::vector<std::vector<Edge>> listaAdjacencia;
    std::vector<int> vertexes;
    Graph(int numVertices);
    std::string toString();
    void addEdge(int u, int v, int w);
    Graph optimumBranchingTarjan();
};
