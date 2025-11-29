#include <cstdint>
#include <optional>
#include <string>
#include <vector>

typedef struct
{
    size_t n;
    uint8_t w;
} Edge;

class Graph
{
  private:
    std::vector<size_t> _v;
    std::vector<Edge> _e;

    size_t firstWithNeighbor;

    inline bool isFirst(size_t v);
    inline bool isLast(size_t v);

    void _setEdge(size_t u, size_t v, uint8_t w);

  public:
    Graph(size_t vertexes);
    size_t vertexCount();
    size_t edgeCount();
    void setEdge(size_t u, size_t v, uint8_t w);
    std::optional<uint8_t> getEdge(size_t u, size_t v);
    std::string toString();
};
