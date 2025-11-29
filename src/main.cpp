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

    Graph graph = Graph(3);
    assert(graph.vertexCount() == 3);
    graph.setEdge(0, 1, 1);
    assert(graph.getEdge(0, 1) == 1);

    return 0;
}
