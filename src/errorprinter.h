

#ifndef ERROR_PRINTER_H_
#define ERROR_PRINTER_H_


#include <string>
#include <iostream>


class ErrorPrinter
{


    public:

        
        // modify to accept any kind of stream.
        static void PrintError(std::string message)
        {

            std::cout << "The following error has occured: \n"
                << message << "\n";

        }


};


#endif // ERROR_PRINTER_H_
