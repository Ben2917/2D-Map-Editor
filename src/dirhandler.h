

#ifndef DIRHANDLER_H_
#define DIRHANDLER_H_


// C Headers
#include <sys/types.h>
#include <dirent.h>


#include <vector>
#include <fstream>


#include "errorprinter.h"


class DirectoryHandler
{

    
    public:


        DirectoryHandler();


        int ReadDirectory(std::string dir_name, 
            std::vector<std::string> &filenames);


        int ReadFile(std::string file_directory, 
            std::string filename, std::string &content);


    private:


        int ReadLinuxDirectory(std::string dir_name,
            std::vector<std::string> &filenames);


        int ReadWindowsDirectory(std::string dir_name,
            std::vector<std::string> &filenames);


};


#endif //DIRHANDLER_H_

