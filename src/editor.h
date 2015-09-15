

#ifndef EDITOR_H_
#define EDITOR_H_


#include <SDL.h>
#include <SDL_image.h>


#include <memory>
#include <map>


#include "dirhandler.h"
#include "textprinter.h"


// Handles all of the map editors events and functionality.
class Editor
{


    public:


        Editor();


        Editor(std::string font_name, int text_size, 
            std::string dir_name, SDL_Renderer *ren, int level_w, int level_h);


        ~Editor();


        void HandleEvents(SDL_Event e, SDL_Renderer *ren);


        void Update(SDL_Renderer *ren, SDL_Rect camera);


    private:


        DirectoryHandler dir_handler;


        std::unique_ptr<TextPrinter> t_printer;

        
        // The visual representation of the map that the user is creating
        std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> map_tex;


        std::map<std::string, SDL_Texture*>::iterator tile_itr;


        SDL_Texture* test;


        // Stores all of the available tiles.
        std::map<std::string, SDL_Texture*> tiles;


        int current_tile;

  
        std::array<std::array<std::string, 50>, 50> map_arr;


        bool collidable;


        void LoadTiles(SDL_Renderer *ren, std::string dir_name);
        

        void NextTile(SDL_Renderer* ren);


        void PrevTile(SDL_Renderer* ren);


        void PlaceTile(SDL_Renderer* ren); 
        

        SDL_Rect GetGridSquare(int x, int y);


        void WriteMapToFile();  


};


#endif // EDITOR_H_
