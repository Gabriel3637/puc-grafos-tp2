#pragma once

#include <string>
#include <vector>

#include "graph.hpp"

typedef std::vector<Edge> channel_t;
typedef std::vector<size_t> componentSet_t;

class FH
{
  private:
    size_t w;
    size_t h;

  public:
    bool includeDiagonal = true;

    void segment(std::string image);

    void getChannels(std::vector<channel_t> &channels, unsigned char *bmp);

    void getComponents(componentSet_t &components, channel_t &channel);

    void mergeChannels(componentSet_t &merged,
                       std::vector<componentSet_t> &components);

    void drawImage(componentSet_t &merged, size_t unionCount);
};
