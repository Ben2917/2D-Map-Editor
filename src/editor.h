

#ifndef EDITOR_H_
#define EDITOR_H_


#include <SDL.h>
#include <SDL_image.h>


#include <memory>
#include <map>


#include "dirhandler.h"


// Handles all of the map editors events and functionality.
class Editor
{


    public:


        Editor();


        Editor(const Editor &e);


        Editor(std::string dir_name, SDL_Renderer *ren,
            int level_w, int level_h);


        ~Editor();


        void HandleEvents(SDL_Event e, SDL_Renderer *ren);


        void Update(SDL_Renderer *ren, SDL_Rect camera);


    private:


        DirectoryHandler dir_handler;

        
        // The visual representation of the map that the user is creating
        std::shared_ptr<SDL_Texture> map_tex;


        std::map<std::string, SDL_Texture*>::iterator tile_itr;


        SDL_Texture* test;


        // Stores all of the available tiles.
        std::map<std::string, SDL_Texture*> tiles;


        std::vector<SDL_Texture*> test_tiles;


        int current_tile;


        // stores the name of the tile relative to it's location within the map
        // should also contain a letter c at the end of the name if the
        // tile is supposed to be collidable.
        //std::string map_arr[50][50];

  
        std::array<std::array<std::string, 50>, 50> map_arr;


        bool collidable; // switch to allow the player 
        // to change between placing collidable and non-collidable tiles.


        void LoadTiles(SDL_Renderer *ren, std::string dir_name);
        // Loads the image files from the directory given.


        void NextTile();


        void PrevTile();


        void PlaceTile(SDL_Renderer* ren); 
        // Calculate grid location, add to array etc.


        SDL_Rect GetGridSquare(int x, int y);


        SDL_Texture* GetCurrentTile(std::string &tile_name);


        void WriteMapToFile(); // Writes all of the map info to a txt file  


};


#endif // EDITOR_H_
