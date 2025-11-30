#include "fh.hpp"
#include <cstdint>
#include <cstdlib>
#include <map>
#include <tuple>
#include <vector>

#include "mst.hpp"
#include "stb_image.h"
#include "stb_image_write.h"

inline size_t idx(size_t i, int c) { return i * 3 + c; }
inline uint8_t dif(uint8_t a, uint8_t b) { return abs(a - b); }

typedef struct SegmentColor
{
    uint64_t r;
    uint64_t g;
    uint64_t b;
    size_t count;

    SegmentColor(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b), count(0)
    {
    }
} SegmentColor;

void FH::segment(std::string image, int k)
{
    this->k = k;
    int channels;
    bmp = stbi_load(image.c_str(), &w, &h, &channels, 3);
    getChannels();
    getComponents();
    mergeChannels();
    drawImage(DrawingMode::color);
}

void FH::getChannels()
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

void FH::getComponents()
{
    components.reserve(3);
    Mst mst;
    for (int i = 0; i < 3; i++)
    {
        components.push_back(mst.generateMST(channels[i], w * h, k));
    }
}

void FH::mergeChannels()
{
    merged.assign(w * h, 0);

    int unionId = 0;
    std::map<std::tuple<size_t, size_t, size_t>, size_t> intersections;

    for (int i = 0; i < w * h; i++)
    {
        auto componentSet = std::make_tuple(components[0][i], components[1][i],
                                            components[2][i]);

        if (intersections.find(componentSet) == intersections.end())
        {
            intersections.insert({componentSet, ++unionId});
        }

        merged[i] = intersections[componentSet];
    }
}

void FH::drawImage(DrawingMode mode)
{
    unsigned char *data =
        (unsigned char *)malloc(w * h * 3 * sizeof(unsigned char));

    std::vector<std::optional<SegmentColor>> colors;

    colors.assign(w * h, {});

    if (mode == DrawingMode::segment)
    {
        for (int i = 0; i < w * h; i++)
        {
            if (!colors[merged[i]].has_value())
            {
                colors[merged[i]] =
                    SegmentColor(std::rand() % 0x100, std::rand() % 0x100,
                                 std::rand() % 0x100);
            }
            auto &c = colors[merged[i]].value();
            data[i * 3] = c.r;
            data[(i * 3) + 1] = c.g;
            data[(i * 3) + 2] = c.b;
        }
    }
    else
    {
        for (int i = 0; i < w * h; i++)
        {
            int id = merged[i];
            if (!colors[id].has_value())
            {
                colors[id] = SegmentColor(0, 0, 0);
            }

            auto &c = colors[id].value();
            c.r += bmp[idx(i, 0)];
            c.g += bmp[idx(i, 1)];
            c.b += bmp[idx(i, 2)];
            c.count++;
        }

        for (int i = 0; i < w * h; i++)
        {
            int id = merged[i];

            auto &c = colors[id].value();
            data[i * 3] = c.r / c.count;
            data[i * 3 + 1] = c.g / c.count;
            data[i * 3 + 2] = c.b / c.count;
        }
    }

    stbi_write_bmp("out.bmp", w, h, 3, data);

    free(data);
}

FH::~FH() { stbi_image_free(bmp); }
