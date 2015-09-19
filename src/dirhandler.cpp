

#include "dirhandler.h"


DirectoryHandler::DirectoryHandler(){}


int DirectoryHandler::ReadDirectory(std::string dir_name,
    std::vector<std::string> &filenames)
{
    // builds but needs testing.
    #ifdef __WIN64__

        ReadWindowsDirectory(dir_name, filenames);

    #elif __WIN32__

        ReadWindowsDirectory(dir_name, filenames);

    #elif __linux__

        ReadLinuxDirectory(dir_name, filenames);

    #elif __unix__

        ReadLinuxDirectory(dir_name, filenames);

    #else

        ErrorPrinter::PrintError(
            "This operating system is not supported\n");

    #endif // OS check

}


int DirectoryHandler::ReadFile(std::string file_directory, 
    std::string filename, std::string &content)
{

    std::ifstream file(file_directory + "/" + filename);

    if(!file.is_open())
    {

        ErrorPrinter::PrintError("Problem opening file in directory "
            + file_directory + " with the name " + filename); 
        return -1;

    }
    else
    {

        std::string temp = "";

        while(file >> temp)
        {

            content += temp + " ";

        }

    }

    return 0;

}


void DirectoryHandler::Write2DIntArrayToFile(std::array<std::array
    <int, 50>, 50> arr, std::string file_name, std::string directory)
{

    std::ofstream map_file(std::string(directory + "/" + file_name));    
    
    for (int i = 0; i < 50; ++i)
    {

        std::string temp = "";

        for (int x = 0; x < 50; ++x)
        {

            temp += std::to_string(arr[i][x]);

        }

        temp += "\n";

        map_file << temp;

    }

    map_file.close();

    // Add "File written successfully." to print list. 
    // Should appear for two seconds.

}


void DirectoryHandler::WriteStringVectorToFile(std::vector<std::string> key,
    std::string file_name, std::string dir_name)
{

    std::ofstream file(std::string(file_name + "/" + dir_name));

    // check for bad file opening etc.

    for(unsigned int i = 0; i < key.size(); ++i)
    {

        file << std::string(key[i]) + "\n";        

    }

    file.close();

} 


int DirectoryHandler::ReadLinuxDirectory(std::string dir_name,
    std::vector<std::string> &filenames)
{

    DIR *dp;

    struct dirent *dirp;

    if((dp = opendir(dir_name.c_str())) == NULL)
    {

        ErrorPrinter::PrintError("Error opening directory " + dir_name);
        // throw exception
        return -1;

    }

    while((dirp = readdir(dp)) != NULL)
    {

        std::string temp = dirp->d_name;

        if(temp != "." && temp != "..")
        {

            filenames.push_back(temp);

        }

    }

    closedir(dp);

    return 0;

}


int DirectoryHandler::ReadWindowsDirectory(std::string dir_name,
    std::vector<std::string> &filenames)
{

    // To be written.

    return 0;

}


void DirectoryHandler::CreateLinuxDirectory(std::string name, 
    std::string location)
{

    // To be written

}


void DirectoryHandler::CreateWindowsDirectory(std::string name,
    std::string location)
{

    // To be written

}
