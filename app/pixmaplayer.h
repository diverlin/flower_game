#ifndef PIXMAPLAYER_H
#define PIXMAPLAYER_H

namespace core {

enum class PixmapLayer: int {
    GROUND_LAYER=0,
    GRASS_LAYER=1<<0,
    ROCK_LAYER=1<<1,
    WOOD_LAYER=1<<2,
    FLOWER_LAYER=1<<3,
    SNAKE_LAYER=1<<4,
    TREE_LAYER=1<<5,
    OVERLAY_LAYER=1<<6,
    HUD_LAYER=1<<7
};

} // namespace core

#endif // PIXMAPLAYER_H

