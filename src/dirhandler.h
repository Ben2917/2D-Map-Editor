

#ifndef DIRHANDLER_H_
#define DIRHANDLER_H_


// C Headers
#include <sys/types.h>
#include <dirent.h>


#include <vector>
#include <fstream>
#include <array>


#include "errorprinter.h"


class DirectoryHandler
{

    
    public:


        DirectoryHandler();


        int ReadDirectory(std::string dir_name, 
            std::vector<std::string> &filenames);


        int ReadFile(std::string file_directory, 
            std::string filename, std::string &content);


        void Write2DIntArrayToFile(std::array<std::array<int, 50>, 50>
            arr, std::string file_name, std::string directory);


        void WriteStringVectorToFile(std::vector<std::string> key,
            std::string file_name, std::string directory);


        void WriteStringToFile(std::string content, std::string file_name,
            std::string directory);


    private:


        int ReadLinuxDirectory(std::string dir_name,
            std::vector<std::string> &filenames);


        int ReadWindowsDirectory(std::string dir_name,
            std::vector<std::string> &filenames);


        void CreateLinuxDirectory(std::string name, 
            std::string location);


        void CreateWindowsDirectory(std::string name, 
            std::string location);


};


#endif //DIRHANDLER_H_

