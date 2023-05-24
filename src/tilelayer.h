#ifndef TILELAYER_H
#define TILELAYER_H

enum class TileLayer: int {
    GROUND_LAYER=0,
    GRASS_LAYER=1<<0,
    ROCK_LAYER=1<<1,
    WOOD_LAYER=1<<2,
    FLOWER_LAYER=1<<3,
    SNAKE_LAYER=1<<4,
    TREE_LAYER=1<<5
};

#endif // TILELAYER_H

