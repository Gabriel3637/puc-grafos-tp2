#include <cstdint>
#include <vector>

class Graph
{
  private:
    std::vector<std::uint8_t> matrix;
    unsigned int vCount; // Vertex count

    inline size_t idx(unsigned int x, unsigned int y);

  public:
    Graph(unsigned int vertexes);
    unsigned int vertexCount();
    void setEdge(unsigned int u, unsigned int v, uint8_t w);
    uint8_t getEdge(unsigned int u, unsigned int v);
};
