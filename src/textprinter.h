

#ifndef TEXTPRINTER_H_
#define TEXTPRINTER_H_


#include <SDL.h>
#include <SDL_ttf.h>


#include <memory>
#include <string>


class TextPrinter
{


    public:


        TextPrinter(std::string font_filename, int text_size);


        void PrintText(SDL_Renderer *ren, SDL_Color colour, 
            std::string text, int x, int y); 


    private:


        std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> text_tex;


        std::unique_ptr<TTF_Font, void(*)(TTF_Font*)> font;


        void LoadFont(std::string font_filename, int size);


};


#endif // TEXTPRINTER_H_






