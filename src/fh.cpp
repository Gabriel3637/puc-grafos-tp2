#include "fh.hpp"

std::vector<std::vector<unsigned char>> *getChannels(unsigned char *bmp, int w,
                                                     int h)
{
    auto channels = new std::vector<std::vector<unsigned char>>(3);
    channels[0].reserve(w * h);
    channels[1].reserve(w * h);
    channels[2].reserve(w * h);
    for (size_t i = 0; i < w * h; i++)
    {
        size_t pixel = i * 3;
        channels[0][i] = bmp[i];
        channels[1][i] = bmp[i + 1];
        channels[2][i] = bmp[i + 2];
    }
}
