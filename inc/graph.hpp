#include <cstdint>
#include <optional>
#include <string>
#include <vector>

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

  public:
    Graph(size_t vertexes);

    void setEdge(size_t u, size_t v, uint8_t w);
    std::string toString();
};
