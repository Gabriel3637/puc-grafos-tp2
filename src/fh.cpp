#include "fh.hpp"
#include <algorithm>
#include <cstdlib>
#include <map>
#include <random>
#include <tuple>
#include <vector>

inline size_t idx(size_t i, int c) { return i * 3 + c; }
inline uint8_t dif(uint8_t a, uint8_t b) { return abs(a - b); }

void FH::getChannels(std::vector<channel_t> &channels, unsigned char *bmp,
                     int w, int h)
{
    channels = std::vector<channel_t>(3);

    for (int i = 0; i < 3; i++)
    {
        std::vector<Edge> &c = channels[i];
        c.reserve(w * h * 4);

        int x = 0, y = 0;
        for (int j = 0; j < w * h; j++)
        {
            if (x < w - 1)
            {
                int k = j + 1;
                c.emplace_back(j, k, dif(bmp[idx(j, i)], bmp[idx(k, i)]));
            }

            if (y < h - 1)
            {
                int k = j + w;
                c.emplace_back(j, k, dif(bmp[idx(j, i)], bmp[idx(k, i)]));
            }

            x++;
            if (x == w)
            {
                x = 0;
                y++;
            }
        }
    }
}

void FH::mergeChannels(componentSet_t &merged,
                       std::vector<componentSet_t> &channels)
{
    merged.assign(w * h, 0);

    int unionId = 0;
    std::map<std::tuple<size_t, size_t, size_t>, size_t> intersections;

    for (int i = 0; i < w * h; i++)
    {
        auto componentSet =
            std::make_tuple(channels[0][i], channels[1][i], channels[2][i]);

        if (intersections.find(componentSet) == intersections.end())
        {
            intersections.insert({componentSet, ++unionId});
        }

        merged[i] = unionId;
    }
}

void FH::drawImage(componentSet_t &merged, size_t unionCount)
{
    std::vector<std::optional<std::tuple<uint8_t, uint8_t, uint8_t>>> colors(
        unionCount);

    for (int i = 0; i < w * h; i++)
    {
        if (!colors[merged[i]].has_value())
        {
            colors[merged[i]] = std::make_tuple(
                std::rand() % 0xFF, std::rand() % 0xFF, std::rand() % 0xFF);
        }
    }
}
