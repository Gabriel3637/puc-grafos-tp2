#pragma once

#include <string>
#include <vector>

#include "graph.hpp"

typedef std::vector<Edge> channel_t;
typedef std::vector<size_t> componentSet_t;

enum DrawingMode
{
    segment,
    color
};

class FH
{
  private:
    int w;
    int h;
    int k;
    unsigned char *bmp;
    std::vector<channel_t> channels;
    std::vector<componentSet_t> components;
    componentSet_t merged;

    void getChannels();

    void getComponents();

    void mergeChannels();

    void drawImage(DrawingMode mode);

  public:
    void segment(std::string image, int k);

    ~FH();
};
