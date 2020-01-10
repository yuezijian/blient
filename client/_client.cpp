#include "Client.hpp"


extern "C" Program* CreateProgram()
{
    return new Client;
}
