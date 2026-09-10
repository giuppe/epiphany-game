#ifndef SPRITE_NINE_SLICES_H
#define SPRITE_NINE_SLICES_H
#include "dephine.h"
#include "surface.h"
#include "sprite.h"

class Sprite_Nine_Slice : public Sprite
{
    private:
    Surface* m_sliced_surface = NULL;

    public:
    void init(Surface* surf, Uint32 width, Uint32 height);
    ~Sprite_Nine_Slice();
};

#endif // SPRITE_NINE_SLICES_H