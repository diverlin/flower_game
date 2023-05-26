#ifndef PIXMAPLAYER_H
#define PIXMAPLAYER_H

namespace core {

enum class PixmapLayer: int {
    GROUND_LAYER=1<<0,
    GRASS_LAYER=1<<1,
    ROCK_LAYER=1<<2,
    WOOD_LAYER=1<<3,
    FLOWER_LAYER=1<<4,
    SNAKE_LAYER=1<<5,
    TREE_LAYER=1<<6,
    OVERLAY_LAYER=1<<7,
    HUD_LAYER=1<<8,
    DEBUG_LAYER=1<<9
};

} // namespace core

#endif // PIXMAPLAYER_H

