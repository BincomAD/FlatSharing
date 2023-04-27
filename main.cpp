#include "Server_class/Server.h"
#include "Flat/Flat.h"
#include "DBHelper/DBHelper.h"
#include <iostream>


int main()
{
    try
    {
        Server server{8080};
        server.run();
        
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
