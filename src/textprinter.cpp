

#include "textprinter.h"


TextPrinter::TextPrinter(std::string font_filename, int text_size)
    : text_tex(nullptr, SDL_DestroyTexture),
    font(nullptr, TTF_CloseFont)
{

    LoadFont(font_filename, text_size);

}


void TextPrinter::PrintText(SDL_Renderer* ren, 
    SDL_Color colour, std::string text, int x, int y)
{

    std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)>
        text_surface(TTF_RenderText_Solid(font.get(), text.c_str(), colour),
        SDL_FreeSurface);

    if(text_surface.get() == nullptr)
    {

        // throw surface creation exception

    }

    text_tex.reset(SDL_CreateTextureFromSurface(ren, text_surface.get()));
    if(text_tex.get() == nullptr)
    {

        // throw texture creation error

    }

    SDL_Rect dest;

    dest.x = x;

    dest.y = y;

    dest.w = text_surface.get()->w;

    dest.h = text_surface.get()->h;

    SDL_RenderCopy(ren, text_tex.get(), NULL, &dest);

}


void TextPrinter::LoadFont(std::string font_filename, int size)
{

    font.reset(TTF_OpenFont(font_filename.c_str(), size));
    if(font.get() == nullptr)
    {

        // throw font load error

    }

}
