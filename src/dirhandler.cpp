

#include "dirhandler.h"


UnsupportedOS::UnsupportedOS()
{

    message = "This operating system is unsupported.";

}


const char* UnsupportedOS::what()
{

    return message.c_str();

}


DirectoryError::DirectoryError(std::string dir_name)
{

    message = std::string("Error opening directory ") + dir_name;

}


const char* DirectoryError::what()
{

    return message.c_str();

}


FileReadError::FileReadError(std::string filename)
{

    message = std::string("Error reading file: ") + filename;

}


const char* FileReadError::what()
{

    return message.c_str();

}


FileWriteError::FileWriteError(std::string filename)
{

    message = std::string("Error writing to file ") + filename;

}


const char* FileWriteError::what()
{

    return message.c_str();

}


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

        throw UnsupportedOS();

    #endif // OS check

}


int DirectoryHandler::ReadFile(std::string file_directory, 
    std::string filename, std::string &content)
{

    std::ifstream file(file_directory + "/" + filename);

    if(!file.is_open())
    {

        throw FileReadError(filename);

    }
    else
    {

        std::string temp = "";

        while(file >> temp)
        {

            content += temp + " ";

        }

    }

    // may want to perform a checksum.

    return 0;

}


void DirectoryHandler::Write2DIntArrayToFile(std::array<std::array
    <int, 50>, 50> arr, std::string file_name, std::string directory)
{

    std::ofstream map_file(std::string(directory + "/" + file_name));    

    if(!map_file.is_open())
    {

        throw FileWriteError(file_name);

    }
    
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

    if(!file.is_open())
    {

        throw FileWriteError(file_name);

    }

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

        throw DirectoryError(dir_name);

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
