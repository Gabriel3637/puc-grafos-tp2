#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>

#include "graph.hpp"

int main(void)
{
    int width, height, channels;
    unsigned char *img =
        stbi_load("imgs/test.png", &width, &height, &channels, 3);
    assert(img != NULL);
    assert(width == 2);
    assert(height == 2);
    assert(channels == 4);
    assert(img[0] == 0xFF);
    assert(img[1 * 3 + 1] == 0xFF); // G channel of second pixel
    assert(img[2 * 3 + 2] == 0xFF); // B channel of third pixel
    assert(img[3 * 3] == 0xFF);
    assert(img[3 * 3 + 1] == 0xFF);
    assert(img[3 * 3 + 2] == 0xFF);
    stbi_image_free(img);

    Graph graph = Graph(5);
    assert(graph.vertexCount() == 5);
    assert(graph.edgeCount() == 0);
    for (int i = graph.vertexCount() - 1; i > -1; i--)
    {
        for (int j = i - 1; j > -1; j--)
        {
            std::cout << i << ", " << j << std::endl;
            graph.setEdge(i, j, i);
            //            assert(graph.getEdge(i, j) == i);
            //                assert(graph.getEdge(j, i) == i);
        }
    }

    std::cout << graph.toString() << std::endl;

    return 0;
}
