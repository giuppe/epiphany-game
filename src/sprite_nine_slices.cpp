#include "sprite_nine_slices.h"
#include "screen.h"

SDL_Surface* create_nine_slices(SDL_Surface* src, Uint32 width, Uint32 height, Uint32 border)
{
    SDL_Surface* surface_final = SDL_CreateRGBSurface(0, width, height, Screen::instance()->get_bpp(), 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);



    const int sw = src->w;
    const int sh = src->h;

    // Source rectangles
    SDL_Rect src_tl{0, 0, border, border};
    SDL_Rect src_tc{border, 0, sw - 2*border, border };
    SDL_Rect src_tr{sw-border, 0, border, border};

    SDL_Rect src_l {0, border, border, sh-2*border};
    SDL_Rect src_c {border, border, sw-2*border, sh-2*border};
    SDL_Rect src_r {sw-border, border, border, sh-2*border};

    SDL_Rect src_bl{0, sh-border, border, border};
    SDL_Rect src_bc{border, sh-border, sw-2*border, border};
    SDL_Rect src_br{sw-border, sh-border, border, border};

    // Destination rectangles
    SDL_Rect dst_tl{0, 0, border, border};
    SDL_Rect dst_tc{border, 0, width-2*border, border};
    SDL_Rect dst_tr{width-border, 0, border, border};

    SDL_Rect dst_l {0, border, border, height-2*border};
    SDL_Rect dst_c {border, border, width-2*border, height-2*border};
    SDL_Rect dst_r {width-border, border, border, height-2*border};

    SDL_Rect dst_bl{0, height-border, border, border};
    SDL_Rect dst_bc{border, height-border, width-2*border, border};
    SDL_Rect dst_br{width-border, height-border, border, border};

    SDL_BlitScaled(src, &src_tl, surface_final, &dst_tl);
    SDL_BlitScaled(src, &src_tc, surface_final, &dst_tc);
    SDL_BlitScaled(src, &src_tr, surface_final, &dst_tr);

    SDL_BlitScaled(src, &src_l, surface_final, &dst_l);
    SDL_BlitScaled(src, &src_c, surface_final, &dst_c);
    SDL_BlitScaled(src, &src_r, surface_final, &dst_r);

    SDL_BlitScaled(src, &src_bl, surface_final, &dst_bl);
    SDL_BlitScaled(src, &src_bc, surface_final, &dst_bc);
    SDL_BlitScaled(src, &src_br, surface_final, &dst_br);

    return surface_final;


}

void Sprite_Nine_Slice::init(Surface* surf, Uint32 width, Uint32 height)
{
    m_sliced_surface = new Surface();
    SDL_Surface* final_sdl_surface = create_nine_slices(surf->get_surface(0), width, height, 8);

    m_sliced_surface->init(Screen::instance()->get_renderer(),final_sdl_surface , width, height);
    Sprite::init(m_sliced_surface);
}

Sprite_Nine_Slice::~Sprite_Nine_Slice()
{
    if(m_sliced_surface != NULL)
    {
        delete m_sliced_surface;
    }
}