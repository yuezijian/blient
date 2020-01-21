#include "Client.hpp"


extern "C" BLIENT_CLIENT__EXPORT Program* CreateProgram()
{
    return new Client;
}
