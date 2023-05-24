#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

enum class ObjectLayer: int {
    GROUND_LAYER=0,
    GRASS_LAYER=1<<0,
    ROCK_LAYER=1<<1,
    WOOD_LAYER=1<<2,
    FLOWER_LAYER=1<<3,
    SNAKE_LAYER=1<<4,
    TREE_LAYER=1<<5
};

#endif // OBJECTLAYER_H

