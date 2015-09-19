

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


        void HandleEvents(SDL_Event e, SDL_Renderer *ren, SDL_Rect camera);


        void Update(SDL_Renderer *ren, SDL_Rect camera);


    private:


        DirectoryHandler dir_handler;


        std::unique_ptr<TextPrinter> t_printer;

        
        // The visual representation of the map that the user is creating
        // may replace and use seperate tiles because then they could
        // be easily removed. This would need to be coupled with a 
        // culling function so that drawing all of the tiles can be
        // avoided
        std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> map_tex;


        std::vector<SDL_Texture*> tiles;


        // This is a key that shows which tile names 
        // are mapped to which numbers
        
        // 0 MUST be reserved for empty space.
        std::vector<std::string> tile_map;


        int current_tile;


        bool collidable;

  
        std::array<std::array<int, 50>, 50> map_arr;


        void HandleMouseButtons(SDL_Event e, 
            SDL_Renderer* ren, SDL_Rect camera);


        void HandleKeys(SDL_Event e);

      
        void ClearMap();


        void LoadTiles(SDL_Renderer *ren, std::string dir_name);
        

        void NextTile();


        void PrevTile();


        void PlaceTile(SDL_Renderer* ren, SDL_Rect camera); 
        

        SDL_Rect GetGridSquare(int x, int y, SDL_Rect camera);


        void WriteMapToFile();


};


#endif // EDITOR_H_
