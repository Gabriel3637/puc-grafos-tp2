#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "fh.hpp"

int main(int argc, char **argv)
{
    FH fh;
    fh.segment(argv[1], atoi(argv[2]));
    return 0;
}
