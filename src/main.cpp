#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>

#include "fh.hpp"
#include "graph.hpp"

int main(void)
{
    int width, height, channels;
    unsigned char *img =
        stbi_load("./imgs/test.png", &width, &height, &channels, 3);

    FH fh = FH();
    fh.getChannels(img, width, height);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < width * height; j++)
        {
            std::cout << (int)fh.channels[i][j] << " ";
        }
        std::cout << std::endl;
    }

    stbi_image_free(img);

    return 0;
}
