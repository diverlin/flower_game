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
    TREE_BOTTOM_LAYER=1<<6,
    TREE_TOP_LAYER=1<<7,
    OVERLAY_LAYER=1<<8,
    HUD_LAYER=1<<9
};

} // namespace core

#endif // PIXMAPLAYER_H

